
#include "spdlog/spdlog.h"

#include "Dsse/DataTypes.h"
#include "Dsse/DssEngine.h"
//#include <iostream>

namespace dsse
{
	Dsse::Dsse(std::shared_ptr<spdlog::logger> logger)
		: rootcontainer()
	{
		m_logger = logger;
		rootcontainer.id = 0;
		m_nodereg.push_back(rootcontainer);
		rootcontainer.parent = &rootcontainer;
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
		return !((nodeid < 0) || (nodeid >= m_nodereg.size()));
	}
	int Dsse::RegisterNode(Nodebase* node)
	{
		// TODO null check?
		if (node->id != -1) // TODO what else?
			return -1;
		m_nodereg.push_back(node);
		int id = static_cast<int>(m_nodereg.size())-1;
		m_logger->info("Registered node \"{}\" under id {}", node, id);
		return id;
	}
	NodeBase* Dsse::ReleaseNode(int nodeid)
	{
		if (!CheckID(nodeid))
		{
			m_logger->error("Dsse.ReleaseNode invalid id {}", nodeid);
			return nullptr;
		}
		NodeBase* node = m_nodereg.at(nodeid);
		m_nodereg.erase(nodeid);
		m_logger->info("Released node {}", id);
		return node;
	}
	void Dsse::DeleteNode(int nodeid)
	{
		if (!CheckID(nodeid))
		{
			m_logger->error("Dsse.DeleteNode invalid id {}", nodeid);
			return;
		}
		NodeBase* node = m_nodereg.at(nodeid);
		m_nodereg.erase(nodeid);
		delete node;
		m_logger->info("Deleted node {}", id);
	}
	NodeBase* Dsse::GetNode(int nodeid)
	{
		if (!CheckID(nodeid))
		{
			m_logger->error("Dsse.GetNode invalid id {}", nodeid);
			return nullptr;
		}
		return m_nodereg.at(nodeid);
	}
	void Dsse::MoveNode(int targetid, int destid);
	{
		if (!CheckID(nodeid) || (targetid == 0))
		{
			m_logger->error("Dsse.MoveNode invalid target id {}", nodeid);
			return;
		}
		if (!CheckID(destid))
		{
			m_logger->error("Dsse.MoveNode invalid destination id {}", destid);
			return;
		}
		if(targetid == dest)
		{
			m_logger->error("Dsse.MoveNode target == destination", destid);
			return;
		}
		NodeBase* target = m_nodereg.at(nodeid);
		NodeBase* dest = m_nodereg.at(destid);
		// TODO parent to child swap case
		//target.parent = dest; // TODO
	}
	
} // namespace Dsse