
//#include <iostream>

#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/SimpleInlet.h"

namespace dsse
{

SimpleInlet::SimpleInlet(NodeBase* node, DataBox* databox, String name, String desc)
	: InletBase(node, name, desc)
{
	m_data = databox;

	spdlog::get("iolet")->debug("Float \"{}\" constr()", GetFullName());
}
SimpleInlet::~SimpleInlet()
{
	spdlog::get("iolet")->debug("Float \"{}\" destr()", GetFullName());
}

bool SimpleInlet::Connect(OutletBase* outlet)
{
	if( IsConnected() /*&& PARAMS["InletOverrideConnection"] == false*/ ) // TODO
	{
		spdlog::get("iolet")->error("{} Already connected!", GetFullName());
		return false;
	}

    if (SimpleOutlet* so = dynamic_cast<SimpleOutlet*>(outlet))
    {
	    m_connection = outlet;
		spdlog::get("iolet")->info("Connected {} to {}", GetFullName(), outlet->GetFullName());
	    return true;
    }
    else
    {
		spdlog::get("iolet")->error("Failed to connect {} to {}", GetFullName(), outlet->GetFullName());
    }

	return false;
}
void SimpleInlet::ReceiveData(DataBox* data)
{
    // TODO
    m_dataChanged = true;
	m_dataReady = true;
    spdlog::get("iolet")->error("{} received {}", GetFullName(), data->ToString());
}

} // namespace dsse
