
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

	spdlog::get("iolet")->debug("InletBase \"{}\" constr()", name);
}
InletBase::~InletBase()
{
	spdlog::get("iolet")->debug("InletBase \"{}\" destr()", name);
}

String InletBase::GetFullName()
{
	String fname;
	fname.reserve(m_node->name.size() + 4 + name.size());
	fname += m_node->name;
	fname += ":in:";
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
