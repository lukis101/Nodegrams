
#include "spdlog/spdlog.h"

#include "Nodegrams/inoutlets/SinglewayInlet.h"
#include "Nodegrams/inoutlets/OutletBase.h"

namespace Nodegrams
{

SinglewayInlet::SinglewayInlet(NodeBase* node, DataBox* data, String name, String desc)
	: InletBase(node, data, name, desc)
{
	m_connection = nullptr;
}
SinglewayInlet::~SinglewayInlet()
{
}

bool SinglewayInlet::Connected(OutletBase* outlet) // Called by outlet
{
    if (m_connection != nullptr)
	{
		spdlog::get("iolet")->critical("{} Already connected!", GetFullName());
		return false;
	}
    m_connection = outlet;
    spdlog::get("iolet")->info("Connected {}<-{}", GetFullName(), outlet->GetFullName());
    return true;
}

bool SinglewayInlet::Disconnected(OutletBase* outlet) // Called by outlet
{
	if (outlet != m_connection)
	{
		if (m_connection == nullptr)
			spdlog::get("iolet")->critical("Invalid disconnection {}<-{}: not connected",
                GetFullName(), outlet->GetFullName());
		else
			spdlog::get("iolet")->critical("Invalid disconnection {}<-{}: wrong outlet",
                GetFullName(), outlet->GetFullName());
		return false;
	}
	m_connection = nullptr;
    spdlog::get("iolet")->info("Disconnected {}<-{}", GetFullName(), outlet->GetFullName());
	return true;
}

void SinglewayInlet::DisconnectAll()
{
    if (m_connection != nullptr)
    {
        if (!m_connection->Disconnect(this))
            spdlog::get("iolet")->critical("Broken connection! {}-><-/-{}", GetFullName(), m_connection->GetFullName());
    }
}

} // namespace Nodegrams
