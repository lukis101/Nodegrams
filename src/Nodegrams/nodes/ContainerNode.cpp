
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/ContainerNode.h"

namespace Nodegrams {
namespace Nodes
{

ContainerNode::ContainerNode(Nodegrams* engine)
	: DynamicNode(engine)
{
}
ContainerNode::~ContainerNode()
{
}

void ContainerNode::DoLogic()
{
}

NodeBase* ContainerNode::CreateInstance(Nodegrams* engine)
{
    return new ContainerNode(engine);
}

}
} // namespace Nodegrams
