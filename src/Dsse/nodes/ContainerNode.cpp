
#include "Dsse/DssEngine.h"

namespace dsse
{

ContainerNode::ContainerNode()
	: DynamicNode()
{
	spdlog::get("dsse")->info("ContainerNode() \"{}\" constr()", name);
}
ContainerNode::~ContainerNode()
{
	spdlog::get("dsse")->info("ContainerNode() \"{}\" destr()", name);
}

void ContainerNode::DoLogic()
{
}

}
