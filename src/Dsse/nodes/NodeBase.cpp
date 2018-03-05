
#include "Dsse/DssEngine.h"

namespace dsse
{

NodeBase::NodeBase()
{
    m_id = 0;
	m_parent = 0;

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
