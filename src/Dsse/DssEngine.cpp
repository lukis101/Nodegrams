
#include "Dsse/DssEngine.h"

#include <iterator>
#include "spdlog/spdlog.h"

#include "Dsse/DataTypes.h"

namespace dsse
{
Dsse::Dsse(std::shared_ptr<spdlog::logger> logger)
	: rootcontainer()
{
	m_logger = logger;
	rootcontainer.id = 0;
	rootcontainer.parent = &rootcontainer;
	m_nodereg[0] = &rootcontainer;
	m_nodecount = 1;
	m_maxid = 0;
	m_minfreeid = 1;
}
/*::Dsse() : Dsse::Dsse(spdlog::stdout_logger_mt("dsse"))
{
}*/
Dsse::~Dsse()
{
	spdlog::drop(m_logger->name());
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

static bool CheckID(int id)
{
	if ((nodeid >= 0) && (nodeid <= m_maxid))
		return (m_nodereg[id] == nullptr);
	return false;
}
int Dsse::RegisterNode(Nodebase* node)
{
	// TODO null check?
	if (node->id != -1) // already registered!
		return -1;
	if (m_minfreeid == NODECAP-1) // Cap reached
		return -1;
	// Assign to slot
	int id = m_minfreeid;
	m_nodereg[m_minfreeid] = node;
	m_nodecount++;
	// Update counters/indices
	if (m_minfreeid == m_maxid+1) // Pushed to end
	{
		m_minfreeid++;
		m_maxid++;
	}
	else // find next free slot
	{
		for(int i=m_minfreeid+1; i<NODECAP; i++)
			if (m_nodereg[i] != nullptr)
				m_minfreeid = i;
	}
	// Init node
	node->id = id;
	node->parent = &rootcontainer;
	m_logger->info("Registered node \"{}\" with id {}", node->name, id);
	return id;
}
NodeBase* Dsse::ReleaseNode(int nodeid)
{
	if (!CheckID(nodeid) || (nodeid == 0))
	{
		m_logger->error("Dsse.ReleaseNode: invalid id {}", nodeid);
		return nullptr;
	}
	NodeBase* node = m_nodereg[nodeid];
	node.id = -1;
	node.parent = nullptr;

	m_nodereg[nodeid] = nullptr;
	m_nodecount--;
	if (nodeid == m_maxid) // Popped from end
		m_maxid--;
	if (nodeid < m_minfreeid)
		m_minfreeid = nodeid;

	m_logger->info("Released node {}", nodeid);
	return node;
}
void Dsse::DeleteNode(int nodeid)
{
	if (!CheckID(nodeid) || (nodeid == 0))
	{
		m_logger->error("Dsse.DeleteNode: invalid id {}", nodeid);
		return;
	}
	delete m_nodereg[nodeid];

	m_nodereg[nodeid] = nullptr;
	m_nodecount--;
	if (nodeid == m_maxid) // Popped from end
		m_maxid--;
	if (nodeid < m_minfreeid)
		m_minfreeid = nodeid;
	m_logger->info("Deleted node {}", nodeid);
}
NodeBase* Dsse::GetNode(int nodeid)
{
	if (!CheckID(nodeid))
	{
		m_logger->error("Dsse.GetNode: invalid id {}", nodeid);
		return nullptr;
	}
	return m_nodereg[nodeid];
}
void Dsse::MoveNode(int targetid, int destid);
{
	if (!CheckID(targetid) || (targetid == 0))
	{
		m_logger->error("Dsse.MoveNode: invalid target id {}", nodeid);
		return;
	}
	if (!CheckID(destid))
	{
		m_logger->error("Dsse.MoveNode: invalid destination id {}", destid);
		return;
	}
	if(targetid == dest)
	{
		m_logger->error("Dsse.MoveNode: target == destination", destid);
		return;
	}
	NodeBase* target = m_nodereg[nodeid];
	NodeBase* dest = m_nodereg[destid];
	// TODO parent-child swap case
	//target.parent = dest; // TODO
}

void Dsse::PrintNodes(std::ostream stream, bool recursive=false);
{
	// Manually print root node and start from second node (prevents infinite recursion)
	stream << "> " << rootcontainer.id << " = " << rootcontainer.GetName() << std::endl;
	for (int i=1; i<m_maxid; i++)
	{
		NodeBase* node = m_nodereg[i];
		if (node == nullptr)
			continue;
		stream << "-> (" << node->id << ") "; // ID
		if (node->custnamed) // orig name in parentheses
			stream << '\"' << node->custname << "\" (" << node->name << ')' <<std::endl;
		else
			stream << '\"' << node->name << '\"' <<std::endl;
		if (recursive && node->iscontainer)
		{
			stream << "--> TODO: recursive contents here" <<std::endl;
		}
	}
}

} // namespace Dsse