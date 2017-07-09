
//#include <iostream>

#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/OutletBase.h"
#include "Dsse/inoutlets/FloatOutlet.h"
#include "Dsse/nodes/NodeBase.h"

//#include "Dsse/DataTypes.h"
//#include "Dsse/DssEngine.h"

namespace dsse
{

FloatOutlet::FloatOutlet(NodeBase* node, String name, String desc, float defValue)
	: OutletBase(node, name, desc)
{
	m_defValue = defValue;
    m_outValue = m_defValue;
	
	spdlog::get("iolet")->info("Float \"{}\" constr()", GetFullName());
}
FloatOutlet::~FloatOutlet()
{
	spdlog::get("iolet")->info("Float \"{}\" destr()", GetFullName());
}

bool FloatOutlet::ConnectTo(FloatInlet* inlet)
{
	if( IsConnectedTo(inlet) )
	{
		spdlog::get("iolet")->error("Already connected: {}->{}",
				GetFullName(), inlet->GetFullName());
		return false;
	}
    bool status = inlet->Connect(this);
	if(status)
	{
		connections.push_back(inlet);
		// TODO: push current data?
		spdlog::get("iolet")->info( "Connected {}->{}",
            GetFullName(), inlet->GetFullName());
		return true;
	}
	spdlog::get("iolet")->error("Failed to connect {}->{}",
			GetFullName(), inlet->GetFullName());
	return false;
}
void FloatOutlet::WriteData(float data)
{
	if( m_outValue != data )
	{
		m_outValue = data;
		m_dataChanged = true;
	}
	m_dataReady = true;
}
void FloatOutlet::SendData()
{
	if( !m_dataReady )
	{
		spdlog::get("iolet")->critical("{} not ready to send!", GetFullName());
	}
	else
	{
		for(auto iter = connections.begin(); iter != connections.end(); ++iter)
		{
			FloatInlet* inlet = static_cast<FloatInlet*>(*iter);
			inlet->ReceiveData(m_outValue);
		}
		m_dataReady = false;
		m_dataSent = true;
	}
}
String FloatOutlet::GetDataString()
{
	return "TODO";
}
	
} // namespace dsse