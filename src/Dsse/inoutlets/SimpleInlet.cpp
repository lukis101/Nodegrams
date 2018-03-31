
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
	if (!CanConnect() /*&& PARAMS["InletOverrideConnection"] == false*/) // TODO
	{
		spdlog::get("iolet")->error("{} Already connected!", GetFullName());
		return false;
	}

    if (SimpleOutlet* so = dynamic_cast<SimpleOutlet*>(outlet))
    {
	    m_connection = outlet;
		spdlog::get("iolet")->info("Connected {}<-{}", GetFullName(), outlet->GetFullName());
	    return true;
    }

	spdlog::get("iolet")->error("Failed to connect {} to {}", GetFullName(), outlet->GetFullName());
	return false;
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
	return true;
}

/*void SimpleInlet::ReceiveData(DataBox* data)
{
    // TODO
    m_dataChanged = true;
	m_dataReady = true;
    spdlog::get("iolet")->critical("{} received {}", GetFullName(), data->ToString());
}*/

} // namespace dsse
