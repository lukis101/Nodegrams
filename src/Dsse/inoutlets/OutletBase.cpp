
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
	m_dataChanged = false;
	m_dataReady = false;
	m_dataSent = false;
	m_node = node;
	this->name = name;
	this->description = desc;

	spdlog::get("iolet")->debug("OutletBase \"{}\" constr()", GetFullName());
}
OutletBase::~OutletBase()
{
	spdlog::get("iolet")->debug("OutletBase \"{}\" destr()", GetFullName());
}

String OutletBase::GetFullName()
{
	String fname;
	fname.reserve(m_node->name.size() + 5 + name.size());
	fname += m_node->name;
	fname += ":out:";
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
