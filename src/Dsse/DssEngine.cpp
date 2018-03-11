
#include <iterator>
#include <sstream>
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
	m_nodecount = 1;
	m_maxid = 1;
	m_minfreeid = 2;

    typereg = new TypeRegistry(spdlog::stdout_logger_mt(logger->name() + ".treg"));
    rootcontainer = new ContainerNode(this);
	rootcontainer->m_id = 1;
	rootcontainer->m_parent = rootcontainer;
    rootcontainer->name = "root";
	m_nodereg[0] = rootcontainer;
	for (int i=1; i < NODECAP; i++)
        m_nodereg[i] = nullptr;
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
void Dsse::Update()
{
	m_logger->info("Dsse.Update()");

    // Mark all the vertices as not visited
    bool* visited = new bool[m_maxid+1];
    for (int i=0; i <= m_maxid; i++)
        visited[i] = false;
    // Create a queue for BFS
    std::list<int> queue;

    // Mark source nodes as visited and enqueue them
	for (int n=1; n <= m_maxid; n++)
        if (m_nodereg[n] != nullptr)
        if (!m_nodereg[n]->HasConnectedInlets())
        {
	        m_logger->info("UPD: Found source: {}", n+1);
            visited[n] = true;
            queue.push_back(n);
            //m_nodereg[n]->Update();
        }
    // TODO Enqueue from detached looping graphs

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        int n = queue.front();
        queue.pop_front();
        m_logger->info("UPD: Processing {}", n+1);

        // Get all adjacent vertices of the dequeued
        // vertex n. If an adjacent has not been visited,
        // then mark it visited and enqueue it
        for (int ol = m_nodereg[n]->GetOutletCount()-1; 0 <= ol; ol--)
        {
            // TODO use outlet iterators
            std::vector<InletBase*> conns = m_nodereg[n]->GetOutlet(ol)->connections;
            for (auto& inl : conns)
            {
                int adjid = inl->m_node->GetID()-1;
                if (!visited[adjid])
                {
	                m_logger->info("UPD: Found branch: {}", adjid+1);
                    visited[adjid] = true;
                    queue.push_back(adjid);
                }
            }
        }
    }
}

bool Dsse::CheckID(int id)
{
	if ((id > 0) && (id <= m_maxid))
		return (m_nodereg[id-1] != nullptr);
	return false;
}

int Dsse::AddNode(NodeBase* node, int id)
{
	// TODO null check?
	if (node->m_id != 0) // TODO compare pointers
    {
		m_logger->error("Node re-register attempt! Current id = {}", node->m_id);
		return 0;
    }
    if (m_minfreeid == NODECAP)
    {
        m_logger->error("RegisterNode(): capacity reached");
        return 0;
    }

    if (id == 0)
    {
        id = m_minfreeid;
    }
    else
    {
        if (id >= NODECAP)
        {
            m_logger->error("RegisterNode(): requested index {} is out of range", id);
            return 0;
        }
    }

	// Check if vacant
	if (m_nodereg[id-1] != nullptr)
		return 0;

	m_nodereg[id-1] = node;
	m_nodecount++;

	// Update counters/indices
	if (id == m_minfreeid)
    {
        if (m_minfreeid == (m_maxid+1)) // Pushed to end
        {
            m_minfreeid++;
        }
        else // middle, find next free slot
        {
            m_minfreeid = m_maxid+1;
            for (int i=id+1; i<NODECAP; i++)
            {
                if (m_nodereg[i-1] == nullptr)
                {
                    m_minfreeid = i;
                    break;
                }
            }
        }
    }
    if (id >= m_maxid) // == covers "first node" case
    {
        m_maxid = id;
    }
	// Init node
	node->m_id = id;
	//node->m_parent = &rootcontainer;
	m_logger->info("Registered node \"{}\" to id {}", node->name, id);
	return id;
}

NodeBase* Dsse::ReleaseNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("Dsse.ReleaseNode: invalid id {}", nodeid);
		return nullptr;
	}
	NodeBase* node = m_nodereg[nodeid-1];
	node->m_id = 0;
	m_nodereg[nodeid-1] = nullptr;

    // Update helper vars
	m_nodecount--;
    if (nodeid < m_minfreeid)
        m_minfreeid = nodeid;
    if (nodeid == m_maxid)
        while (m_maxid > 0)
            if (m_nodereg[--m_maxid] != nullptr)
                break; // found new end

	m_logger->info("Released node \"{}\" from id {}", node->GetName(), nodeid);
	return node;
}
// For unsafe allocated memory
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
	return m_nodereg[nodeid-1];
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

void Dsse::PrintNodes(std::ostream& stream, bool recursive)
{
	// Manually print root node and start from second to prevent infinite recursion
	stream << "> [" << rootcontainer->m_id << "] " << rootcontainer->GetName() << std::endl;

    int level = 1;
	for (int i=2; i<=m_maxid; i++)
	{
		NodeBase* node = m_nodereg[i-1];
		if (node == nullptr)
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
