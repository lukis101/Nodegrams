
#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/SimpleOutlet.h"
#include "Dsse/inoutlets/SimpleInlet.h"
#include "Dsse/DssEngine.h"
#include "Dsse/TypeRegistry.h"
#include "Dsse/nodes/ContainerNode.h"

namespace dsse
{

SimpleOutlet::SimpleOutlet(NodeBase* node, DataBox* data, String name, String desc)
	: OutletBase(node, data, name, desc)
{
}
SimpleOutlet::~SimpleOutlet()
{
}

bool SimpleOutlet::CanConnectTo(InletBase* inlet)
{
    if (!inlet->CanConnect())
        return false;

    return m_node->m_engine->typereg->WriteSupported(m_data, inlet->GetData());
}
bool SimpleOutlet::ConnectTo(InletBase* inlet)
{
    auto logger = spdlog::get("iolet");
    if (!inlet->CanConnect())
	{
		logger->error("Can't connect {}->{}, refused by inlet",
            GetFullName(), inlet->GetFullName());
		return false;
	}
    if (!m_node->m_engine->typereg->WriteSupported(m_data, inlet->GetData()))
	{
	    logger->error("Failed to connect {}->{}, type conversion unsupported",
			GetFullName(), inlet->GetFullName());
	    return false;
	}
    inlet->Connect(this);
    connections.push_back(inlet);
    m_data->ValueChanged(); // Force send on next logic cycle

    logger->info("Connected {}->{}",
        GetFullName(), inlet->GetFullName());

    m_node->m_parent->RebuildUpdateSequence();
    return true;
}

void SimpleOutlet::SendData()
{
    for (auto inlet : connections)
    {
        m_node->m_engine->typereg->WriteData(m_data, inlet->GetData());
    }
}

} // namespace dsse
