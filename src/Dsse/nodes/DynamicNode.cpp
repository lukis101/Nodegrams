
#include "spdlog/spdlog.h"

#include "Dsse/nodes/DynamicNode.h"
#include "Dsse/inoutlets/InletBase.h"
#include "Dsse/inoutlets/OutletBase.h"

namespace dsse
{

DynamicNode::DynamicNode(Dsse* engine)
	: NodeBase(engine)
{
	spdlog::get("dsse")->debug("DynamicNode() \"{}\" constr()", name);
}
DynamicNode::~DynamicNode()
{
	spdlog::get("dsse")->debug("DynamicNode() \"{}\" destr()", name);
}

InletBase* DynamicNode::GetInlet(String inletname)
{
	for (int i=0; i<GetInletCount(); i++)
	{
		if (inletname == m_inlets[i]->name)
			return m_inlets[i];
	}
	spdlog::get("dsse")->error("{}.GetInlet({}) not found", this->name, inletname);
	return nullptr;
}
InletBase* DynamicNode::GetInlet(int index)
{
	if (index<0 || index>GetInletCount())
	{
		spdlog::get("dsse")->error("{}.GetInlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_inlets[index];
}

OutletBase* DynamicNode::GetOutlet(String outletname)
{
	for (int i=0; i<GetOutletCount(); i++)
	{
		if (outletname == m_outlets[i]->name)
			return m_outlets[i];
	}
	spdlog::get("dsse")->error("{}.GetOutlet({}) not found", this->name, outletname);
	return nullptr;
}
OutletBase* DynamicNode::GetOutlet(int index)
{
	if (index<0 || index>GetOutletCount())
	{
		spdlog::get("dsse")->error("{}.GetOutlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return m_outlets[index];
}

}
