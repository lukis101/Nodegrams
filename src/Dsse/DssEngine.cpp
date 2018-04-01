
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
{
	m_logger = logger;

    typereg = new TypeRegistry(spdlog::stdout_logger_mt(logger->name() + ".treg"));
    rootcontainer = new ContainerNode(this, nullptr);
	rootcontainer->m_parent = rootcontainer;
	rootcontainer->m_id = 1;
    rootcontainer->name = "root";
	m_nodes.Add(rootcontainer);
}
Dsse::Dsse()
    : Dsse::Dsse(spdlog::stdout_logger_mt("dsse"))
{
}
Dsse::~Dsse()
{
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

int Dsse::AddNode(NodeBase* node, int id)
{
	// TODO null check?
	if (node->m_id != 0) // TODO compare pointers
    {
		m_logger->error("Node re-register attempt! Current id = {}", node->m_id);
		return 0;
    }

    if (id == 0)
    {
        if (m_nodes.count == m_nodes.capacity)
        {
            m_logger->error("RegisterNode(): capacity reached");
            return 0;
        }
        id = m_nodes.Add(node) + 1;
    }
    else
    {
        int zid = id - 1;
        if (zid >= m_nodes.capacity)
        {
            m_logger->error("RegisterNode(): requested index {} is out of range", id);
            return 0;
        }
        if (m_nodes.IsSet(zid))
        {
            m_logger->error("RegisterNode(): attempt to override existing at {}", id);
            return 0;
        }
        m_nodes.Set(zid, node);
    }

	// Init node
	node->m_id = id;
	//node->m_parent = &rootcontainer;
	m_logger->info("Registered node \"{}\" to id {}", node->name, id);
    RebuildUpdateSequence();
	return id;
}

NodeBase* Dsse::ReleaseNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("Dsse.ReleaseNode: invalid id {}", nodeid);
		return nullptr;
	}
    int zid = nodeid-1;
	NodeBase* node = m_nodes.Remove(zid);
	node->m_id = 0;

	m_logger->info("Released node \"{}\" from id {}", node->GetName(), nodeid);
    RebuildUpdateSequence();
	return node;
}
// For allocated memory
void Dsse::DeleteNode(int nodeid)
{
    NodeBase* node = ReleaseNode(nodeid);
	if (node != nullptr)
	{
	    delete node;
	    m_logger->info("Deleted node {}", nodeid);
	}
}
NodeBase* Dsse::GetNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("Dsse.GetNode: invalid id {}", nodeid);
		return nullptr;
	}
	return m_nodes.Get(nodeid-1);
}
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
