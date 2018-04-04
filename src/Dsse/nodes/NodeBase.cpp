
#include "spdlog/spdlog.h"

#include "Dsse/nodes/NodeBase.h"
#include "Dsse/DssEngine.h"

namespace dsse
{

NodeBase::NodeBase(Dsse* engine)
{
    m_engine = engine;
    m_parent = engine->rootcontainer;
    m_id = 0;

	name = "UnnamedNode";
	category = "NONE";
    description = "No description";
	custname = "";
	custnamed = false;
	//processed = false;

	spdlog::get("dsse")->debug("NodeBase() \"{}\" constr()", name);
}

NodeBase::~NodeBase()
{
	spdlog::get("dsse")->debug("NodeBase() \"{}\" destr()", name);
}

void NodeBase::SetCustomName(String thename)
{
	if (thename.empty() )
	{
		custnamed = false;
		return;
	}
	custname = thename;
	custnamed = true;
}

}
