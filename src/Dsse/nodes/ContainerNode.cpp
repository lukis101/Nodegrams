
#include "Dsse/DssEngine.h"

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

}
