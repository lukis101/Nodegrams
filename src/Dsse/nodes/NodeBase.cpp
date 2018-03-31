
#include "spdlog/spdlog.h"

#include "Dsse/nodes/NodeBase.h"

namespace dsse
{

NodeBase::NodeBase(Dsse* engine, ContainerNode* parent)
{
    m_engine = engine;
    m_parent = parent;
    m_id = 0;

	name = "UnnamedNode";
	category = "NONE";
	custname = "";
	custnamed = false;
	processed = false;

	spdlog::get("dsse")->debug("NodeBase() \"{}\" constr()", name);
}

NodeBase::~NodeBase()
{
	spdlog::get("dsse")->debug("NodeBase() \"{}\" destr()", name);
}

void NodeBase::setCustomName(String thename)
{
	if (thename.empty() )
	{
		custnamed = false;
		return;
	}
	custname = thename;
	custnamed = true;
}

String NodeBase::GetName()
{
	if (custnamed)
	{
		return custname;
	}
    return name;
}

}
