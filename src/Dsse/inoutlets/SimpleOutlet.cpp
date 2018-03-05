
//#include <iostream>

#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/SimpleOutlet.h"

//#include "Dsse/DataTypes.h"
//#include "Dsse/DssEngine.h"

namespace dsse
{

SimpleOutlet::SimpleOutlet(NodeBase* node, DataBox* databox, String name, String desc)
	: OutletBase(node, name, desc)
{
    m_data = databox;

	spdlog::get("iolet")->debug("SimpleOutlet \"{}\" constr()", GetFullName());
}
SimpleOutlet::~SimpleOutlet()
{
	spdlog::get("iolet")->debug("SimpleOutlet \"{}\" destr()", GetFullName());
}

bool SimpleOutlet::ConnectTo(InletBase* inlet)
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
void SimpleOutlet::SendData()
{
	if( !m_dataReady )
	{
		spdlog::get("iolet")->critical("{} not ready to send!", GetFullName());
	}
	else
	{
		for(auto iter = connections.begin(); iter != connections.end(); ++iter)
		{
			(*iter)->ReceiveData(m_data);
		}
		m_dataReady = false;
		m_dataSent = true;
	}
}

} // namespace dsse
