
#include <algorithm>
#include "spdlog/spdlog.h"

#include "Nodegrams/inoutlets/OutletBase.h"
#include "Nodegrams/inoutlets/InletBase.h"
#include "Nodegrams/nodes/NodeBase.h"

namespace Nodegrams {
namespace Nodes
{

OutletBase::OutletBase(NodeBase* node, DataBox* data, String name, String desc)
    : DataHolder(data)
{
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
    assert(inlet != nullptr);
    auto connit = std::find(std::begin(connections), std::end(connections), inlet);
    if (connit != std::end(connections))
    {
        connections.erase(connit); // TODO swap and pop
        if (inlet->Disconnected(this))
        {
            spdlog::get("iolet")->info("Disconnected {}->{}", GetFullName(), inlet->GetFullName());
            return true;
        }
        spdlog::get("iolet")->critical("Broken connection! {}-><-/-{}", GetFullName(), inlet->GetFullName());
        return false;
    }
	spdlog::get("iolet")->error( "Not connected: {}-/->{}", GetFullName(), inlet->GetFullName());
	return false;
}

void OutletBase::DisconnectAll()
{
    while (!connections.empty())
    {
        auto inlet = connections.back();
        connections.pop_back();
        if (inlet->Disconnected(this))
            spdlog::get("iolet")->info("Disconnected {}->{}", GetFullName(), inlet->GetFullName());
        else
            spdlog::get("iolet")->critical("Broken connection! {}-><-/-{}", GetFullName(), inlet->GetFullName());
    }
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

}
} // namespace Nodegrams
