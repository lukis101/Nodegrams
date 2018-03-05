
#include "Dsse/DssEngine.h"

namespace dsse
{

ContainerNode::ContainerNode()
	: DynamicNode()
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
