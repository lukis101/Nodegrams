
#include <algorithm>
#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/MultiwayInlet.h"
#include "Dsse/inoutlets/SimpleOutlet.h"

namespace dsse
{

MultiwayInlet::MultiwayInlet(NodeBase* node, DataBox* data, String name, String desc)
	: InletBase(node, data, name, desc)
{
}
MultiwayInlet::~MultiwayInlet()
{
    assert(connections.size() == 0);
}

bool MultiwayInlet::IsConnectedTo(OutletBase* outlet)
{
    auto connit = std::find(std::begin(connections), std::end(connections), outlet);
    return connit != std::end(connections);
}

bool MultiwayInlet::Connected(OutletBase* outlet)
{
    auto connit = std::find(std::begin(connections), std::end(connections), outlet);
    if (connit != std::end(connections))
	{
		spdlog::get("iolet")->critical("Already connected {}<-{}", GetFullName(), outlet->GetFullName());
		return false;
	}
    connections.push_back(outlet);
    spdlog::get("iolet")->info("Connected {}<-{}", GetFullName(), outlet->GetFullName());
    return true;
}

bool MultiwayInlet::Disconnected(OutletBase* outlet) // Called by outlet
{
    auto connit = std::find(std::begin(connections), std::end(connections), outlet);
    if (connit == std::end(connections))
	{
        spdlog::get("iolet")->critical("Invalid disconnection {}<-{}: not connected",
            GetFullName(), outlet->GetFullName());
		return false;
	}
	connections.erase(connit);
    spdlog::get("iolet")->info("Disconnected {}<-{}", GetFullName(), outlet->GetFullName());
	return true;
}

void MultiwayInlet::DisconnectAll()
{
    while (!connections.empty())
    {
        auto outlet = connections.back();
        if (!outlet->Disconnect(this))
            spdlog::get("iolet")->critical("Broken connection! {}-><-/-{}", GetFullName(), outlet->GetFullName());
    }
}

} // namespace dsse
