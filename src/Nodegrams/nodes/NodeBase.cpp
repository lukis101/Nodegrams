
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/NodeBase.h"
#include "Nodegrams/Nodegrams.h"

namespace Nodegrams
{

NodeBase::NodeBase(Nodegrams* engine)
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
}

NodeBase::~NodeBase()
{
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

} // namespace Nodegrams
