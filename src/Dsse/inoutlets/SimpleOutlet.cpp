
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
}
SimpleOutlet::~SimpleOutlet()
{
}

bool SimpleOutlet::CanConnectTo(InletBase* inlet)
{
    if (inlet->IsConnected())
        return false;

    return m_node->m_engine->typereg->WriteSupported(m_data, inlet->GetData());
}
bool SimpleOutlet::ConnectTo(InletBase* inlet)
{
    auto logger = spdlog::get("iolet");
	if (!CanConnectTo(inlet))
	{
		logger->error("Can't connect {}->{}",
            GetFullName(), inlet->GetFullName());
		return false;
	}
    bool status = inlet->Connect(this);
	if (!status)
	{
	    logger->error("Failed to connect {}->{}",
			GetFullName(), inlet->GetFullName());
	    return false;
	}
    connections.push_back(inlet);
    // TODO: push current data
    logger->info("Connected {}->{}",
        GetFullName(), inlet->GetFullName());
    return true;
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
