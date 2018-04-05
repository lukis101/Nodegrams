
#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/SimpleOutlet.h"
#include "Dsse/inoutlets/InletBase.h"
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
    if (!inlet->IsMultiway() && inlet->GetNumConnections())
        return false;
    return m_node->m_engine->typereg->WriteSupported(m_data, inlet->GetData());
}

bool SimpleOutlet::ConnectTo(InletBase* inlet)
{
    auto logger = spdlog::get("iolet");
    if (!inlet->IsMultiway() && inlet->GetNumConnections())
    {
        logger->error("Can't connect {}->{}, single-way inlet already connected",
            GetFullName(), inlet->GetFullName());
        return false;
    }
    if (!m_node->m_engine->typereg->WriteSupported(m_data, inlet->GetData()))
    {
        logger->error("Can't connect {}->{}, type conversion unsupported",
            GetFullName(), inlet->GetFullName());
        return false;
    }

    if (!inlet->Connected(this))
    {
        logger->critical("Failed to connect {}->{}, error from inlet",
            GetFullName(), inlet->GetFullName());
        return false;
    }
    connections.push_back(inlet);
    m_data->ValueChanged(); // Force send on next logic cycle

    logger->info("Connected {}->{}",
        GetFullName(), inlet->GetFullName());
    return true;
}

void SimpleOutlet::SendData()
{
    for (auto& inlet : connections)
    {
        m_node->m_engine->typereg->WriteData(m_data, inlet->GetData());
    }
}

} // namespace dsse
