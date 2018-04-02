
#include "spdlog/spdlog.h"

#include "Dsse/nodes/ContainerNode.h"

namespace dsse
{

ContainerNode::ContainerNode(Dsse* engine)
	: DynamicNode(engine)
{
	spdlog::get("dsse")->debug("ContainerNode() \"{}\" constr()", name);
}
ContainerNode::~ContainerNode()
{
	spdlog::get("dsse")->debug("ContainerNode() \"{}\" destr()", name);
}

void ContainerNode::DoLogic()
{
}

NodeBase* ContainerNode::CreateInstance(Dsse* engine)
{
    return new ContainerNode(engine);
}

}
