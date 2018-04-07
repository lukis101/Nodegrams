
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/StaticNode.h"
#include "Nodegrams/inoutlets/InletBase.h"
#include "Nodegrams/inoutlets/OutletBase.h"
#include "Nodegrams/Nodegrams.h"

namespace Nodegrams {
namespace Nodes
{

StaticNode::StaticNode(Nodegrams* engine, int numinlets, int numoutlets)
	: NodeBase(engine)
{
	m_numinlets = numinlets;
	m_numoutlets = numoutlets;
	// Allocate arrays only, objects managed in derived classes
	m_inlets = new InletBase*[numinlets];
	m_outlets = new OutletBase*[numoutlets];
}
StaticNode::~StaticNode()
{
	delete[] m_inlets;
	delete[] m_outlets;
}

// Main logic
void StaticNode::Update()
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
InletBase* StaticNode::GetInlet(String inletname)
{
	for (int i=0; i<GetInletCount(); i++)
	{
		if (inletname == m_inlets[i]->name)
			return m_inlets[i];
	}
	m_engine->m_logger->error("{}.GetInlet({}) not found", this->name, inletname);
	return nullptr;
}
InletBase* StaticNode::GetInlet(int index)
{
	if (index<0 || index>GetInletCount())
	{
		m_engine->m_logger->error("{}.GetInlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_inlets[index];
}
bool StaticNode::HasConnectedInlets()
{
    int inls = GetInletCount()-1;
    while (inls >= 0)
    {
        if (m_inlets[inls]->GetNumConnections())
            return true;
        --inls;
    }
    return false;
}

OutletBase* StaticNode::GetOutlet(String outletname)
{
	for (int i=0; i<GetOutletCount(); i++)
	{
		if (outletname == m_outlets[i]->name)
			return m_outlets[i];
	}
	m_engine->m_logger->error("{}.GetOutlet({}) not found", this->name, outletname);
	return nullptr;
}
OutletBase* StaticNode::GetOutlet(int index)
{
	if (index<0 || index>GetOutletCount())
	{
		m_engine->m_logger->error("{}.GetOutlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_outlets[index];
}

}
} // namespace Nodegrams
