
#include <iterator>
#include <sstream>
#include <utility>
#include "Nodegrams/Nodegrams.h"
#include "Nodegrams/TypeRegistry.h"
#include "Nodegrams/Serializing.h"
#include "Nodegrams/nodes/ContainerNode.h"
#include "Nodegrams/inoutlets/OutletBase.h"
#include "Nodegrams/inoutlets/InletBase.h"

#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

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
    //node->m_parent = container; // TODO
	//container->AssignNode(node); // TODO

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
/*NodeBase* Nodegrams::GetNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("GetNode: invalid id {}", nodeid);
		return nullptr;
	}
	return m_nodes.Get(nodeid-1);
}*/
/*void Nodegrams::MoveNode(int targetid, int destid)
{
	if (!CheckID(targetid) || (targetid == 0))
	{
		m_logger->error("MoveNode: invalid target id {}", targetid);
		return;
	}
	if (!CheckID(destid))
	{
		m_logger->error("MoveNode: invalid destination id {}", destid);
		return;
	}
	if(targetid == destid)
	{
		m_logger->error("MoveNode: target == destination", destid);
		return;
	}
	NodeBase* target = m_nodereg[targetid-1];
	NodeBase* dest = m_nodereg[destid-1];
	// TODO parent-child swap case
	//target.parent = dest; // TODO
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

void Nodegrams::LoadProject()
{
    using namespace rapidjson;

    const char json[] = "{ \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] }";
    m_logger->info("Original JSON:\n {}", json);

    Document document; // Default template parameter uses UTF8 and MemoryPoolAllocator.
    if (document.Parse(json).HasParseError())
        return;

    assert(document.IsObject()); // Document is a JSON value represents the root of DOM. Root can be either an object or array.
    assert(document.HasMember("hello"));
    assert(document["hello"].IsString());
    m_logger->info("hello = {}", document["hello"].GetString());

    document["hello"] = "nodegrams"; // This will invoke strlen()

    // Stringify
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    document.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    m_logger->info("Modified JSON with reformatting:\n {}", sb.GetString());
}

void Nodegrams::SaveProject()
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

    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    // Stringify
    serer.doc.Accept(writer); // Accept() traverses the DOM and generates Handler events.
    m_logger->info("Saving to JSON:\n {}", sb.GetString());
}

} // namespace Nodegrams
