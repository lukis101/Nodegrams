
#include "spdlog/spdlog.h"

#include "Dsse/nodes/StaticNode.h"
#include "Dsse/inoutlets/InletBase.h"
#include "Dsse/inoutlets/OutletBase.h"

namespace dsse
{

StaticNode::StaticNode(Dsse* engine, int numinlets, int numoutlets)
	: NodeBase(engine)
{
	m_numinlets = numinlets;
	m_numoutlets = numoutlets;
	// Allocate arrays only, objects managed in derived classes
	m_inlets = new InletBase*[numinlets];
	m_outlets = new OutletBase*[numoutlets];

	spdlog::get("dsse")->debug("StaticNode() \"{}\" constr()", name);
}
StaticNode::~StaticNode()
{
	spdlog::get("dsse")->debug("StaticNode() \"{}\" destr()", name);
	delete[] m_inlets;
	delete[] m_outlets;
}

InletBase* StaticNode::GetInlet(String inletname)
{
	for(int i=0; i<GetInletCount(); i++)
	{
		if (inletname == m_inlets[i]->name)
			return m_inlets[i];
	}
	spdlog::get("dsse")->error("{}.GetInlet({}) not found", this->name, inletname);
	return nullptr;
}
InletBase* StaticNode::GetInlet(int index)
{
	if( index<0 || index>GetInletCount() )
	{
		spdlog::get("dsse")->error("{}.GetInlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_inlets[index];
}

OutletBase* StaticNode::GetOutlet(String outletname)
{
	for(int i=0; i<GetOutletCount(); i++)
	{
		if (outletname == m_outlets[i]->name)
			return m_outlets[i];
	}
	spdlog::get("dsse")->error("{}.GetOutlet({}) not found", this->name, outletname);
	return nullptr;
}
OutletBase* StaticNode::GetOutlet(int index)
{
	if( index<0 || index>GetOutletCount() )
	{
		spdlog::get("dsse")->error("{}.GetOutlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_outlets[index];
}

}
