
#include <iterator>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include "Nodegrams/Nodegrams.h"
#include "Nodegrams/TypeRegistry.h"
#include "Nodegrams/Serializing.h"
#include "Nodegrams/nodes/ContainerNode.h"
#include "Nodegrams/inoutlets/OutletBase.h"
#include "Nodegrams/inoutlets/InletBase.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"

namespace Nodegrams
{
using Nodes::NodeBase;
using Nodes::ContainerNode;
using Nodes::InletBase;
using Nodes::OutletBase;

Nodegrams::Nodegrams(std::shared_ptr<spdlog::logger> logger)
    : noderegistry(20)
{
	m_logger = logger;

    typereg = new TypeRegistry(spdlog::stdout_logger_mt(logger->name() + ".treg"));
    rootcontainer = new ContainerNode(this);
	rootcontainer->m_id = 1;
    rootcontainer->SetCustomName("root");
    rootcontainer->m_parent = rootcontainer;
	m_nodes.Set(0, rootcontainer);
}
Nodegrams::Nodegrams()
    : Nodegrams::Nodegrams(spdlog::stdout_logger_mt("Ndgm"))
{
}
Nodegrams::~Nodegrams()
{
    for (auto& node : m_nodes)
        delete node;
    for (auto& node : noderegistry)
        delete node.second;
    delete typereg;
}

int Nodegrams::Init()
{
	m_logger->info("Nodegrams Initialising..");
	return 0;
}
int Nodegrams::Shutdown()
{
	m_logger->info("Nodegrams shutting down..");
	return 0;
}

void Nodegrams::RebuildUpdateSequence()
{
	m_logger->info("RebuildUpdateSequence()");
    updateSequence.clear();

    // Mark all nodes as not visited
    int numnodes = m_nodes.capacity;
    bool* visited = new bool[numnodes];
    for (int i=0; i < numnodes; i++)
        visited[i] = false;

    std::list<int> queue;
    // Start from source nodes
    for (auto& node : m_nodes)
    {
        int id = node->GetID();
        if (!node->HasConnectedInlets())
        {
            m_logger->info("> Found source: {}", id);
            visited[id-1] = true;
            queue.push_back(id);
        }
        else m_logger->info("> Not source: {}", id);
    }
    // TODO Enqueue from detached looping graphs

    while (!queue.empty())
    {
        // Dequeue node and add to sequence
        NodeBase* node = m_nodes.Get(queue.front()-1);
        queue.pop_front();

        updateSequence.push_back(node->GetID());
        m_logger->info("> Processing: {}", node->GetID());

        // Get all adjacent vertices of the dequeued
        // vertex n. If an adjacent has not been visited,
        // then mark it visited and enqueue it
        for (int ol = node->GetOutletCount()-1; 0 <= ol; ol--) // TODO use range loop
        {
            std::vector<InletBase*> conns = node->GetOutlet(ol)->connections;
            for (auto& inl : conns)
            {
                int brid = inl->GetNode()->GetID();
                if (!visited[brid-1])
                {
                    m_logger->info("> Found branch: {}", brid);
                    visited[brid-1] = true;
                    queue.push_back(brid);
                }
            }
        }
    }
    // Print final sequence
    std::stringstream ss;
    ss << "Calculated sequence:";
    for (auto& id : updateSequence)
        ss << ' ' << id;
    m_logger->info(ss.str());
}

void Nodegrams::Update()
{
    for (auto& id : updateSequence)
    {
        NodeBase* node = m_nodes.Get(id-1);
        // TODO only if outputs changed
        node->Update();
    }
}

bool Nodegrams::CheckID(int id)
{
    if ((id < 1) || (id > m_nodes.capacity))
        return false;
	return m_nodes.IsSet(id-1);
}


bool Nodegrams::RegisterNode(NodeBase*&& node)
{
    String registryName = node->GetFullName();

    auto it = noderegistry.find(registryName);
    if (it != noderegistry.end())
    {
        m_logger->error("RegisterNode: \"{}\" already registered", registryName);
        assert(registryName == it->second->registryName);
        delete node;
	    return false;
    }

    if (noderegistry.insert({registryName, node}).second)
    {
        m_logger->info("Registered node \"{}\"", registryName);
        return true;
    }
    else
    {
        m_logger->error("RegisterNode: failed to insert \"{}\"", registryName);
        delete node;
        return false;
    }
}

bool Nodegrams::DeregisterNode(String registryName)
{
    auto it = noderegistry.find(registryName);
    if (it == noderegistry.end())
    {
        m_logger->error("DeregisterNode: \"{}\" not registered", registryName);
	    return false;
    }

    // Invalidate nodes of this type
    for (auto& node : m_nodes)
        if (node->registryName == registryName) // URGENT TODO use fullname
            RemoveNode(node->m_id);

    noderegistry.erase(it);
    m_logger->info("Deregistered node \"{}\"", registryName);
    return true;
}

int Nodegrams::AddNode(String fullname, int parent, int id)
{
    if (m_nodes.count == m_nodes.capacity)
    {
        m_logger->error("AddNode: capacity reached");
        return 0;
    }

    // Verify parent
    ContainerNode* container;
    if (parent == 1)
    {
        container = rootcontainer;
    }
    else
    {
        if (!CheckID(parent))
        {
            m_logger->error("AddNode: ivalid parent id {}", parent);
            return 0;
        }
        auto parnode = m_nodes.Get(parent-1);
        if (!parnode->IsContainer())
        {
            m_logger->error("AddNode: specified parent {} not a container", parent);
            return 0;
        }
        container = static_cast<ContainerNode*>(parnode);
    }
    // Verify/get id
    if (id == 0)
    {
        id = m_nodes.GetFreeSlot() + 1;
    }
    else
    {
        if ((id <= 0) || (id > m_nodes.capacity))
        {
            m_logger->error("AddNode: requested id {} out of range", id);
            return 0;
        }
        if (m_nodes.IsSet(id-1))
        {
            m_logger->error("AddNode: attempt to override existing at {}", id);
            return 0;
        }
    }

    // Lookup name in registry
    auto it = noderegistry.find(fullname);
    if (it == noderegistry.end())
    {
        m_logger->error("AddNode: \"{}\" not found", fullname);
	    return 0;
    }

    // Build and init
    NodeBase* node = it->second->CreateInstance(this);
    m_nodes.Set(id-1, node);
    node->m_id = id;
	container->AssignNode(node);

	m_logger->info("Added node \"{}\" with id {}", node->name, id);
    RebuildUpdateSequence();
	return id;
}

bool Nodegrams::RemoveNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("RemoveNode: invalid id {}", nodeid);
		return false;
	}
	NodeBase* node = m_nodes.Remove(nodeid-1);
    for (int il = 0; il < node->GetInletCount(); ++il)
        node->GetInlet(il)->DisconnectAll();
    for (int ol = 0; ol < node->GetOutletCount(); ++ol)
        node->GetOutlet(ol)->DisconnectAll();
	m_logger->info("Removed node \"{}\" from id {}", node->GetName(), nodeid);
    delete node;

    RebuildUpdateSequence();
	return true;
}

void Nodegrams::ClearNodes(void)
{
    for (auto& it = ++m_nodes.begin(); it != m_nodes.end(); ++it) // Skip root
        delete *it; // TODO better release in case of managed resources?
    m_nodes.Clear();
	m_nodes.Set(0, rootcontainer);
	m_logger->info("Removed all nodes");
}

bool Nodegrams::MoveNode(int node, int container)
{
	if (node == container)
	{
		m_logger->error("MoveNode: target == destination");
		return false;
	}
	if (!CheckID(node))
	{
		m_logger->error("MoveNode: invalid target id {}", node);
		return false;
	}
	if (!CheckID(container))
	{
		m_logger->error("MoveNode: invalid destination id {}", container);
		return false;
	}

	NodeBase* cont = m_nodes.Get(container-1);
	if (!cont->IsContainer())
	{
		m_logger->error("MoveNode: destination not a container");
		return false;
	}
    ContainerNode* pcontainer = static_cast<ContainerNode*>(cont);

	NodeBase* pnode = m_nodes.Get(node-1);
    if (pnode->m_parent->m_id == container) // swapping child with parent
    {
        ContainerNode* pparent = static_cast<ContainerNode*>(cont);
	    assert(false); // TODO
		return true;
	}
    pnode->m_parent->RemoveNode(pnode);
    pcontainer->AssignNode(pnode);
    return true;
}

/*NodeBase* Nodegrams::GetNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("GetNode: invalid id {}", nodeid);
		return nullptr;
	}
	return m_nodes.Get(nodeid-1);
}*/

bool Nodegrams::ConnectInoutlets(int source, int outlet, int sink, int inlet)
{
	if (!CheckID(source))
	{
		m_logger->error("ConnectInoutlets: invalid source node id {}", source);
		return false;
	}
	if (!CheckID(sink))
	{
		m_logger->error("ConnectInoutlets: invalid sink node id {}", sink);
		return false;
	}

    OutletBase* olet = m_nodes.Get(source-1)->GetOutlet(outlet);
	if (olet == nullptr)
	{
		m_logger->error("ConnectInoutlets: invalid outlet index {}", outlet);
		return false;
	}
    InletBase*  ilet = m_nodes.Get(sink-1)->GetInlet(inlet);
	if (ilet == nullptr)
	{
		m_logger->error("ConnectInoutlets: invalid inlet index {}", inlet);
		return false;
	}

    if (olet->ConnectTo(ilet))
    {
        RebuildUpdateSequence();
        return true;
    }
    return false;
}
bool Nodegrams::DisconnectInoutlets(int source, int outlet, int sink, int inlet)
{
	if (!CheckID(source))
	{
		m_logger->error("DisconnectInoutlets: invalid source node id {}", source);
		return false;
	}
	if (!CheckID(sink))
	{
		m_logger->error("DisconnectInoutlets: invalid sink node id {}", sink);
		return false;
	}

    OutletBase* olet = m_nodes.Get(source-1)->GetOutlet(outlet);
	if (olet == nullptr)
	{
		m_logger->error("ConnectInoutlets: invalid outlet index {}", outlet);
		return false;
	}
    InletBase*  ilet = m_nodes.Get(sink-1)->GetInlet(inlet);
	if (ilet == nullptr)
	{
		m_logger->error("ConnectInoutlets: invalid inlet index {}", inlet);
		return false;
	}

    if (olet->Disconnect(ilet))
    {
        RebuildUpdateSequence();
        return true;
    }
    return false;
}

bool Nodegrams::ClearInletConnections(int node, int inlet)
{
	if (!CheckID(node))
	{
		m_logger->error("ClearInletConnections: invalid node id {}", node);
		return false;
	}
    NodeBase* nd = m_nodes.Get(node-1);
    InletBase* inl = nd->GetInlet(inlet);
    if (inl == nullptr)
	{
		m_logger->error("ClearInletConnections: invalid inlet index {}", inlet);
		return false;
	}
    if (inl->GetNumConnections())
    {
        inl->DisconnectAll();
        RebuildUpdateSequence();
    }
    return true;
}
bool Nodegrams::ClearOutletConnections(int node, int outlet)
{
	if (!CheckID(node))
	{
		m_logger->error("ClearOutletConnections: invalid node id {}", node);
		return false;
	}
    NodeBase* nd = m_nodes.Get(node-1);
    OutletBase* outl = nd->GetOutlet(outlet);
    if (outl == nullptr)
	{
		m_logger->error("ClearInletConnections: invalid outlet index {}", outlet);
		return false;
	}
    if (outl->GetNumConnections())
    {
        outl->DisconnectAll();
        RebuildUpdateSequence();
    }
    return true;
}

void Nodegrams::PrintNodes(std::ostream& stream, bool recursive)
{
	// Manually print root node and start from second to prevent infinite recursion
	stream << "> [" << rootcontainer->m_id << "] " << rootcontainer->GetName() << std::endl;

    int level = 1;
    for (auto& node : m_nodes)
	{
        if (node == rootcontainer)
            continue;

        for (int j=level; j>0; j--) // depth arrow
            stream << '-';
		stream << "> [" << node->m_id << "] \""; // ID
		if (node->custnamed) // orig name in parentheses
			stream << node->custname << "\" (" << node->name << ')';
		else
			stream << node->name << '\"';
		if (node->IsContainer())
		{
		    if (recursive)
            {
                stream << " {" << std::endl;
			    stream << "> TODO: recursive contents here" << std::endl;
            }
            else
            {
                stream << "{}" << std::endl;
            }
		}
        else stream << std::endl;
	}
}
String Nodegrams::PrintNodes(bool recursive)
{
    std::ostringstream oss;
    PrintNodes(oss, recursive);
    return oss.str();
}

bool Nodegrams::LoadProject(String file)
{
    std::ifstream ifs(file);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    if (doc.ParseStream(isw).HasParseError())
        return false;
    if (!doc.IsObject())
        return false;

    rapidjson::Value robj = doc.GetObject();
    Deserializer derer(robj);
    if (derer.SelectMember("FormatVersion"))
    {
        int idint = derer.GetInt();
        derer.Pop();
        // TODO check compatibility?
    }

    ClearNodes(); // Looks OK, can proceed

    String projname;
    if (derer.SelectMember("Name"))
    {
        projname = derer.GetString();
        derer.Pop();
    }
    else
    {
        projname = file; // TODO extract properly
    }
    rootcontainer->SetCustomName(projname);

    std::unordered_map<int, int> idmap; // Saved node ID -> deserialized node ID
    std::vector<int> nodelist; // Saved node array indices

    derer.SelectMember("Nodes");
    unsigned nodecount = derer.ArraySize();
    idmap.reserve(nodecount);
    nodelist.reserve(nodecount);
    // Pass 1: add and init nodes
    for (unsigned i=0; i<nodecount; i++)
    {
        derer.SelectIndex(i);
        derer.SelectMember("ID"); // TODO safety checks
            int sourceid = derer.GetInt();
            derer.Pop();
        derer.SelectMember("Name"); // TODO safety checks
            String name = derer.GetString();
            derer.Pop();
        derer.SelectMember("Category"); // TODO safety checks
            String category = derer.GetString();
            derer.Pop();
        String fullname = category + ':' + name;

        int newid = AddNode(fullname);
        if (newid)
        {
            idmap[sourceid] = newid;
            nodelist.push_back(i);
            m_nodes.Get(newid-1)->Deserialize(derer);
            m_logger->info("Deserialized node \"{}\" {}->{}", fullname, sourceid, newid);
        }
        else
        {
            // TODO use special dummy type for compatibility
            m_logger->error("Unknown node type \"{}\"", fullname);
        }
        derer.Pop();
    }
    // Pass 2: Resolve hierarchy
    for (auto& n : nodelist)
    {
        derer.SelectIndex(n);
        if (derer.SelectMember("Parent"))
        {
            int savedparent = derer.GetInt();
            derer.Pop();
            derer.SelectMember("ID");
                int child = idmap[derer.GetInt()];
                derer.Pop();
            auto itparent = idmap.find(savedparent);
            if (itparent != idmap.end())
                MoveNode(child, (*itparent).second);
        }
        derer.Pop();
    }
    // Pass 3: Connect in/outlets
    for (auto& n : nodelist)
    {
        derer.SelectIndex(n);
        derer.SelectMember("ID");
            int source = idmap[derer.GetInt()];
            derer.Pop();
        if (derer.SelectMember("Outlets"))
        {
            for (unsigned o=0; o<derer.ArraySize(); o++)
            {
                derer.SelectIndex(o);
                derer.SelectMember("Name");
                    String olet = derer.GetString();
                    derer.Pop();
                auto outlet = m_nodes.Get(source-1)->GetOutlet(olet);
                if (outlet == nullptr)
                {
                    m_logger->error("Invalid outlet \"{}\" of \"{}\"",
                        olet, m_nodes.Get(source-1)->GetFullName());
                    derer.Pop();
                    continue;
                }
                if (derer.SelectMember("Connections"))
                {
                    for (unsigned con=0; con<derer.ArraySize(); con++)
                    {
                        derer.SelectIndex(con);
                        derer.SelectMember("Node");
                            int sink = derer.GetInt();
                            derer.Pop();
                        auto it = idmap.find(sink);
                        if (it == idmap.end()) // Invalid sink node
                        {
                            m_logger->error("Invalid connection to node {}", sink);
                            derer.Pop();
                        }
                        sink = (*it).second;

                        derer.SelectMember("Inlet");
                            String ilet = derer.GetString();
                            derer.Pop();
                        auto inlet = m_nodes.Get(sink-1)->GetInlet(ilet);
                        if (inlet == nullptr)
                        {
                            m_logger->error("Invalid connection: \"{}\"->\"{}\"",
                                m_nodes.Get(sink-1)->GetFullName(), ilet);
                        }
                        else
                        {
                            outlet->ConnectTo(inlet);
                        }
                        derer.Pop();
                    }
                    derer.Pop();
                }
                derer.Pop();
            }
            derer.Pop();
        }
        derer.Pop();
    }

    derer.Pop();
    return true;
}

bool Nodegrams::SaveProject(String file)
{
    Serializer serer;

    serer.SetKey("FormatVersion");
    serer.AddUint(1);
    serer.SetKey("Name");
    serer.AddString("TODO: ProjectName"); // TODO project name = root node name
    //TODO globals?
    //TODO dependencies

    serer.SetKey("Nodes");
    serer.StartArray();
    // Serialize all nodes skipping the root one
    for (auto& it = ++m_nodes.begin(); it != m_nodes.end(); ++it)
        it->Serialize(serer);
    serer.EndArray(); // nodes

    // Write to file
    std::ofstream ofs(file);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> fwriter(osw);
    serer.doc.Accept(fwriter);
    m_logger->info("Saved project to \"{}\"", file);

    return true;
}

} // namespace Nodegrams
