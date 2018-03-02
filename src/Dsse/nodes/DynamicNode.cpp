
#include "Dsse/DssEngine.h"

namespace dsse
{

DynamicNode::DynamicNode()
	: NodeBase()
{
	spdlog::get("dsse")->info("DynamicNode() \"{}\" constr()", name);
}
DynamicNode::~DynamicNode()
{
	spdlog::get("dsse")->info("DynamicNode() \"{}\" destr()", name);
}

InletBase* DynamicNode::GetInlet(String inletname)
{
	for(int i=0; i<GetInletCount(); i++)
	{
		if(m_inlets[i]->name.compare(inletname))
			return m_inlets[i];
	}
	spdlog::get("dsse")->error("{}.GetInlet({}) not found", this->name, inletname);
	return nullptr;
}
InletBase* DynamicNode::GetInlet(int index)
{
	if( index<0 || index>GetInletCount() )
	{
		spdlog::get("dsse")->error("{}.GetInlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_inlets[index];
}

OutletBase* DynamicNode::GetOutlet(String outletname)
{
	for(int i=0; i<GetOutletCount(); i++)
	{
		if(m_outlets[i]->name.compare(outletname))
			return m_outlets[i];
	}
	spdlog::get("dsse")->error("{}.GetOutlet({}) not found", this->name, outletname);
	return nullptr;
}
OutletBase* DynamicNode::GetOutlet(int index)
{
	if( index<0 || index>GetOutletCount() )
	{
		spdlog::get("dsse")->error("{}.GetOutlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_outlets[index];
}


}
