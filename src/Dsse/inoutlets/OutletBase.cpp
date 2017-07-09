
//#include <iostream>

#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/OutletBase.h"
#include "Dsse/nodes/NodeBase.h"

//#include "Dsse/DataTypes.h"
//#include "Dsse/DssEngine.h"

namespace dsse
{

OutletBase::OutletBase(NodeBase* node, String name, String desc)
{
	m_dataReady = false;
	m_dataSent = false;
	m_node = node;
	this->name = name;
	this->description = desc;
	
	spdlog::get("iolet")->info("OutletBase \"{}\" constr()", name);
}
OutletBase::~OutletBase()
{
	spdlog::get("iolet")->info("OutletBase \"{}\" destr()", name);
}

String OutletBase::GetFullName()
{
	const String prefix = "(o)";
	String fname;
	fname.reserve(prefix.size() + m_node->name.size() + 1 + name.size());
	fname += prefix;
	fname += m_node->name;
	fname += '.';
	fname += name;
	return fname;
}
bool OutletBase::Disconnect(InletBase* inlet)
{
	for(auto iter = connections.begin(); iter != connections.end(); ++iter)
	{
		if( *iter == inlet )
		{
			connections.erase(iter);
			if( inlet->Disconnect(this) )
			{
				spdlog::get("iolet")->info("Disconnected {}->{}", GetFullName(), inlet->GetFullName());
				return true;
			}
			spdlog::get("iolet")->critical("Broken connection! {} to {}", GetFullName(), inlet->GetFullName());
			return false;
		}
	}
	spdlog::get("iolet")->error( "Can't disconnect: {}-/->{}", GetFullName(), inlet->GetFullName());
	return false;
}
bool OutletBase::IsConnectedTo(InletBase* inlet)
{
	for(auto iter = connections.begin(); iter != connections.end(); ++iter)
	{
		if( *iter == inlet )
			return true;
	}
	return false;
}
int OutletBase::GetNumConnections()
{
	return static_cast<int>(connections.size());
}

} // namespace dsse