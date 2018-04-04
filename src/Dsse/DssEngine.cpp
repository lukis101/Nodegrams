
#include <iterator>
#include <sstream>
#include <utility>
#include "Dsse/DssEngine.h"
#include "Dsse/TypeRegistry.h"
#include "Dsse/nodes/ContainerNode.h"
#include "Dsse/inoutlets/OutletBase.h"
#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{

Dsse::Dsse(std::shared_ptr<spdlog::logger> logger)
    : noderegistry(20)
{
	m_logger = logger;

    typereg = new TypeRegistry(spdlog::stdout_logger_mt(logger->name() + ".treg"));
    rootcontainer = new ContainerNode(this);
	rootcontainer->m_id = 1;
    rootcontainer->SetCustomName("root");
	m_nodes.Set(0, rootcontainer);
}
Dsse::Dsse()
    : Dsse::Dsse(spdlog::stdout_logger_mt("dsse"))
{
}
Dsse::~Dsse()
{
    for (auto& node : m_nodes)
        delete node;
    for (auto& node : noderegistry)
        delete node.second;
    delete typereg;
}

int Dsse::Init()
{
	m_logger->info("Dsse Initialising..");
	return 0;
}
int Dsse::Shutdown()
{
	m_logger->info("Dsse shutting down..");
	return 0;
}

void Dsse::RebuildUpdateSequence()
{
	m_logger->info("Dsse.RebuildQueue()");
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
                int brid = inl->m_node->GetID();
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

void Dsse::Update()
{
    for (auto& id : updateSequence)
    {
        NodeBase* node = m_nodes.Get(id-1);
        // TODO only if outputs changed
        node->Update();
    }
}

bool Dsse::CheckID(int id)
{
    if ((id < 1) || (id > m_nodes.capacity))
        return false;
	return m_nodes.IsSet(id-1);
}


bool Dsse::RegisterNode(NodeBase*&& node)
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

bool Dsse::DeregisterNode(String registryName)
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

int Dsse::AddNode(String fullname, int parent, int id)
{
    if (m_nodes.count == m_nodes.capacity)
    {
        m_logger->error("AddNode(): capacity reached");
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
            m_logger->error("AddNode(): ivalid parent id {}", parent);
            return 0;
        }
        auto parnode = m_nodes.Get(parent-1);
        if (!parnode->IsContainer())
        {
            m_logger->error("AddNode(): specified parent {} not a container", parent);
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
            m_logger->error("AddNode(): requested id {} out of range", id);
            return 0;
        }
        if (m_nodes.IsSet(id-1))
        {
            m_logger->error("AddNode(): attempt to override existing at {}", id);
            return 0;
        }
    }

    // Lookup name in registry
    auto it = noderegistry.find(fullname);
    if (it == noderegistry.end())
    {
        m_logger->error("AddNode(): \"{}\" not found", fullname);
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

bool Dsse::RemoveNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("Dsse.RemoveNode: invalid id {}", nodeid);
		return false;
	}
	NodeBase* node = m_nodes.Remove(nodeid-1);
	m_logger->info("Removed node \"{}\" from id {}", node->GetName(), nodeid);
    delete node;

    RebuildUpdateSequence();
	return true;
}
/*NodeBase* Dsse::GetNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("Dsse.GetNode: invalid id {}", nodeid);
		return nullptr;
	}
	return m_nodes.Get(nodeid-1);
}*/
/*void Dsse::MoveNode(int targetid, int destid)
{
	if (!CheckID(targetid) || (targetid == 0))
	{
		m_logger->error("Dsse.MoveNode: invalid target id {}", targetid);
		return;
	}
	if (!CheckID(destid))
	{
		m_logger->error("Dsse.MoveNode: invalid destination id {}", destid);
		return;
	}
	if(targetid == destid)
	{
		m_logger->error("Dsse.MoveNode: target == destination", destid);
		return;
	}
	NodeBase* target = m_nodereg[targetid-1];
	NodeBase* dest = m_nodereg[destid-1];
	// TODO parent-child swap case
	//target.parent = dest; // TODO
}*/

bool Dsse::ConnectInoutlets(int source, int outlet, int sink, int inlet)
{
	if (!CheckID(source))
	{
		m_logger->error("Dsse.ConnectInoutlets: invalid source node id {}", source);
		return false;
	}
	if (!CheckID(sink))
	{
		m_logger->error("Dsse.ConnectInoutlets: invalid sink node id {}", sink);
		return false;
	}

    OutletBase* olet = m_nodes.Get(source-1)->GetOutlet(outlet);
	if (olet == nullptr)
	{
		m_logger->error("Dsse.ConnectInoutlets: invalid outlet index {}", outlet);
		return false;
	}
    InletBase*  ilet = m_nodes.Get(sink-1)->GetInlet(inlet);
	if (ilet == nullptr)
	{
		m_logger->error("Dsse.ConnectInoutlets: invalid inlet index {}", inlet);
		return false;
	}

    if (olet->ConnectTo(ilet))
    {
        RebuildUpdateSequence();
        return true;
    }
    return false;
}
bool Dsse::DisconnectInoutlets(int source, int outlet, int sink, int inlet)
{
	if (!CheckID(source))
	{
		m_logger->error("Dsse.DisconnectInoutlets: invalid source node id {}", source);
		return false;
	}
	if (!CheckID(sink))
	{
		m_logger->error("Dsse.DisconnectInoutlets: invalid sink node id {}", sink);
		return false;
	}

    OutletBase* olet = m_nodes.Get(source-1)->GetOutlet(outlet);
	if (olet == nullptr)
	{
		m_logger->error("Dsse.ConnectInoutlets: invalid outlet index {}", outlet);
		return false;
	}
    InletBase*  ilet = m_nodes.Get(sink-1)->GetInlet(inlet);
	if (ilet == nullptr)
	{
		m_logger->error("Dsse.ConnectInoutlets: invalid inlet index {}", inlet);
		return false;
	}

    if (olet->Disconnect(ilet))
    {
        RebuildUpdateSequence();
        return true;
    }
    return false;
}

bool Dsse::ClearInletConnections(int node, int inlet)
{
	if (!CheckID(node))
	{
		m_logger->error("Dsse.ClearInletConnections: invalid node id {}", node);
		return false;
	}
    NodeBase* nd = m_nodes.Get(node-1);
    InletBase* inl = nd->GetInlet(inlet);
    if (inl == nullptr)
	{
		m_logger->error("Dsse.ClearInletConnections: invalid inlet index {}", inlet);
		return false;
	}
    if (inl->GetNumConnections())
    {
        inl->DisconnectAll();
        RebuildUpdateSequence();
    }
    return true;
}
bool Dsse::ClearOutletConnections(int node, int outlet)
{
	if (!CheckID(node))
	{
		m_logger->error("Dsse.ClearOutletConnections: invalid node id {}", node);
		return false;
	}
    NodeBase* nd = m_nodes.Get(node-1);
    OutletBase* outl = nd->GetOutlet(outlet);
    if (outl == nullptr)
	{
		m_logger->error("Dsse.ClearInletConnections: invalid outlet index {}", outlet);
		return false;
	}
    if (outl->GetNumConnections())
    {
        outl->DisconnectAll();
        RebuildUpdateSequence();
    }
    return true;
}

void Dsse::PrintNodes(std::ostream& stream, bool recursive)
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
String Dsse::PrintNodes(bool recursive)
{
    std::ostringstream oss;
    PrintNodes(oss, recursive);
    return oss.str();
}

} // namespace Dsse
