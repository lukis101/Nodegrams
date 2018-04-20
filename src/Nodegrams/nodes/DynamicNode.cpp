
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/DynamicNode.h"
#include "Nodegrams/inoutlets/InletBase.h"
#include "Nodegrams/inoutlets/OutletBase.h"
#include "Nodegrams/datatypes/DataBox.h"
#include "Nodegrams/Nodegrams.h"

namespace Nodegrams {
namespace Nodes
{

DynamicNode::DynamicNode(Nodegrams* engine)
	: NodeBase(engine)
{
}
DynamicNode::~DynamicNode()
{
}

// Main logic
void DynamicNode::Update()
{
    // TODO only when all inlets are ready
    DoLogic();
	for (int i=0; i<GetOutletCount(); i++)
	{
        OutletBase* outl = m_outlets[i];
        if (outl->HasDataChanged())
        {
            outl->SendData();
            outl->DataChangeHandled();
        }
    }
}

// In/Outlet management
InletBase* DynamicNode::GetInlet(String inletname)
{
	for (int i=0; i<GetInletCount(); i++)
	{
		if (inletname == m_inlets[i]->name)
			return m_inlets[i];
	}
	m_engine->m_logger->error("{}.GetInlet({}) not found", this->name, inletname);
	return nullptr;
}
InletBase* DynamicNode::GetInlet(int index)
{
	if (index<0 || index>GetInletCount())
	{
		m_engine->m_logger->error("{}.GetInlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_inlets[index];
}
bool DynamicNode::HasConnectedInlets()
{
    for (auto& inl : m_inlets)
        if (inl->GetNumConnections())
            return true;
    return false;
}

OutletBase* DynamicNode::GetOutlet(String outletname)
{
	for (int i=0; i<GetOutletCount(); i++)
	{
		if (outletname == m_outlets[i]->name)
			return m_outlets[i];
	}
	m_engine->m_logger->error("{}.GetOutlet({}) not found", this->name, outletname);
	return nullptr;
}
OutletBase* DynamicNode::GetOutlet(int index)
{
	if (index<0 || index>GetOutletCount())
	{
		m_engine->m_logger->error("{}.GetOutlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_outlets[index];
}

void DynamicNode::SerializeInoutlets(Serializer& serer)
{
    if (m_inlets.size())
    {
        serer.SetKey("Inlets");
        serer.StartArray();
        for (auto& inlet : m_inlets)
        {
            serer.StartObject();
            serer.SetKey("Name");
            serer.AddString(inlet->name);

            serer.SetKey("Data");
            inlet->GetData()->Serialize(serer);
            serer.EndObject();
        }
        serer.EndArray();
    }

    if (m_outlets.size())
    {
        serer.SetKey("Outlets");
        serer.StartArray();
        for (auto& outlet : m_outlets)
        {
            if (outlet->connections.size())
            {
                serer.StartObject();
                serer.SetKey("Name");
                serer.AddString(outlet->name);

                serer.SetKey("Connections");
                serer.StartArray();
                for (auto& inlet : outlet->connections)
                {
                    serer.AddString(inlet->GetFullName());
                }
                serer.EndArray();
                serer.EndObject();
            }
        }
        serer.EndArray();
    }
}

}
} // namespace Nodegrams
