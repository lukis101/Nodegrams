
#include "spdlog/spdlog.h"
#include "Dsse/nodes/NodeBase.h"

namespace dsse
{

NodeBase::NodeBase()
{
	m_parent = nullptr;
	m_id = -1;
	name = "UnnamedNode";
	classname = "Unknown";
	category = "Unknown";
	custname = name;
	custnamed = false;
	processed = false;
	
	spdlog::get("iolet")->info("NodeBase({}) \"{}\" constr()", m_id, name);
}
NodeBase::~NodeBase()
{
	spdlog::get("iolet")->info("NodeBase({}) \"{}\" destr()", m_id, name);
}

InletBase* NodeBase::GetInlet(String inletname)
{
	for(int i=0; i<GetInletCount(); i++)
	{
		if(inlets[i]->name.compare(inletname))
			return inlets[i]; 
	}
	spdlog::get("iolet")->error("{}.GetInlet({}) not found", this->name, inletname);
	return nullptr;
}
InletBase* NodeBase::GetInlet(int index)
{
	if( index<0 || index>GetInletCount() )
	{
		spdlog::get("iolet")->error("{}.GetInlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return inlets[index];
}

OutletBase* NodeBase::GetOutlet(String outletname)
{
	for(int i=0; i<GetOutletCount(); i++)
	{
		if(outlets[i]->name.compare(outletname))
			return outlets[i];
	}
	spdlog::get("iolet")->error("{}.GetOutlet({}) not found", this->name, outletname);
	return nullptr;
}
OutletBase* NodeBase::GetOutlet(int index)
{
	if( index<0 || index>GetOutletCount() )
	{
		spdlog::get("iolet")->error("{}.GetOutlet({}) index out of range", this->name, index);
		return nullptr;
	}
	return outlets[index];
}

void NodeBase::setCustomName(String thename)
{
	if(thename.empty() )
	{
		custnamed = false;
		return;
	}
	custname = thename;
	custnamed = true;
}
	
}