
//#include <iostream>

#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/InletBase.h"
#include "Dsse/nodes/NodeBase.h"

//#include "Dsse/DataTypes.h"
//#include "Dsse/DssEngine.h"

namespace dsse
{
	
InletBase::InletBase(NodeBase* node, String name, String desc)
{
	m_dataReady = false;
	m_dataChanged = false;
	m_connection = nullptr;
	m_node = node;
	this->name = name;
	this->description = desc;
	
	auto m_logger = spdlog::stdout_logger_mt("inlet");
	m_logger->info("InletBase \"{}\" constr()", name);
}
InletBase::~InletBase()
{
	auto m_logger = spdlog::stdout_logger_mt("inlet");
	m_logger->info("InletBase \"{}\" destr()", name);
}

String InletBase::GetFullName()
{
	const String prefix = "(i)";
	String fname;
	fname.reserve(prefix.size() + m_node->name.size() + 1 + name.size());
	fname += prefix;
	fname += m_node->name;
	fname += '.';
	fname += name;
	return fname;
}
bool InletBase::Disconnect(OutletBase* outlet)
{
	if( outlet != m_connection )
	{
		if( IsConnected() )
			spdlog::get("iolet")->error("Can't disconnect {}: wrong outlet", GetFullName());
		else
			spdlog::get("iolet")->error("Can't disconnect {}: not connected", GetFullName());
		return false;
	}
	m_connection = nullptr;
	return true;
}
bool InletBase::IsConnected()
{
	return m_connection != nullptr;
}

} // namespace dsse