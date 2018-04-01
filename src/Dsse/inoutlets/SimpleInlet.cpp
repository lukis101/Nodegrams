
#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/SimpleInlet.h"
#include "Dsse/inoutlets/SimpleOutlet.h"

namespace dsse
{

SimpleInlet::SimpleInlet(NodeBase* node, DataBox* data, String name, String desc)
	: InletBase(node, data, name, desc)
{
	m_connection = nullptr;
}
SimpleInlet::~SimpleInlet()
{
}

bool SimpleInlet::Connect(OutletBase* outlet)
{
    if (m_connection != nullptr)
	{
		spdlog::get("iolet")->error("{} Already connected!", GetFullName());
		return false;
	}
	if (!CanConnectTo(outlet))
	{
		spdlog::get("iolet")->error("{} Invalid connection!", GetFullName());
		return false;
	}

    m_connection = outlet;
    spdlog::get("iolet")->info("Connected {}<-{}", GetFullName(), outlet->GetFullName());
    return true;
}

bool SimpleInlet::Disconnect(OutletBase* outlet)
{
	if (outlet != m_connection)
	{
		if (m_connection == nullptr)
			spdlog::get("iolet")->error("Can't disconnect {}: not connected", GetFullName());
		else
			spdlog::get("iolet")->error("Can't disconnect {}: wrong outlet", GetFullName());
		return false;
	}
	m_connection = nullptr;
    spdlog::get("iolet")->info("Disconnected {}<-{}", GetFullName(), outlet->GetFullName());
	return true;
}

void SimpleInlet::DisconnectAll()
{
    if (m_connection != nullptr)
    {
        spdlog::get("iolet")->info("Disconnected {}<-{}", GetFullName(), m_connection->GetFullName());
        m_connection = nullptr;
    }
}

bool SimpleInlet::CanConnectTo(OutletBase* outlet)
{
    return (dynamic_cast<SimpleOutlet*>(outlet) != nullptr) && (m_connection == nullptr);
}

/*void SimpleInlet::ReceiveData(DataBox* data)
{
    // TODO
    m_dataChanged = true;
	m_dataReady = true;
    spdlog::get("iolet")->critical("{} received {}", GetFullName(), data->ToString());
}*/

} // namespace dsse
