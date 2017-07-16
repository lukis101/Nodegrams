
#include "Dsse/nodes/StaticNode.h"
#include "spdlog/spdlog.h"

namespace dsse
{

StaticNode::StaticNode(int numinlets, int numoutlets)
	: NodeBase()
{
	m_numinlets = numinlets;
	m_numoutletss = numoutlets;
	// Allocate arrays only, objects managed in derived classes
	m_inlets = new InletBase*[numinlets];
	m_outlets = new OutletBase*[numoutlets];
	
	spdlog::get("iolet")->info("StaticNode() \"{}\" constr()", name);
}
StaticNode::~StaticNode()
{
	spdlog::get("iolet")->info("StaticNode() \"{}\" destr()", name);
	delete[] m_inlets;
	delete[] m_outlets;
}

InletBase* StaticNode::GetInlet(String inletname)
{
	for(int i=0; i<GetInletCount(); i++)
	{
		if(m_inlets[i]->name.compare(inletname))
			return m_inlets[i]; 
	}
	spdlog::get("iolet")->error("{}.GetInlet({}) not found", this->name, inletname);
	return nullptr;
}
InletBase* StaticNode::GetInlet(int index)
{
	if( index<0 || index>GetInletCount() )
	{
		spdlog::get("iolet")->error("{}.GetInlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_inlets[index];
}

OutletBase* StaticNode::GetOutlet(String outletname)
{
	for(int i=0; i<GetOutletCount(); i++)
	{
		if(m_outlets[i]->name.compare(outletname))
			return m_outlets[i];
	}
	spdlog::get("iolet")->error("{}.GetOutlet({}) not found", this->name, outletname);
	return nullptr;
}
OutletBase* StaticNode::GetOutlet(int index)
{
	if( index<0 || index>GetOutletCount() )
	{
		spdlog::get("iolet")->error("{}.GetOutlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_outlets[index];
}

	
}