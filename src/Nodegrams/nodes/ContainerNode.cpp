
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

void ContainerNode::AssignNode(NodeBase* node)
{
    for (auto& child : m_nodes)
        if (child == node)
            return;
    m_nodes.push_back(node);
    node->m_parent = this;
}
void ContainerNode::RemoveNode(NodeBase* node)
{
    auto child = std::find(m_nodes.begin(), m_nodes.end(), node);
    if (child != m_nodes.end())
        m_nodes.erase(child);
}

bool ContainerNode::Contains(int node)
{
    for (auto& child : m_nodes)
        if (child->m_id == node)
            return true;
    return false;
}

NodeBase* ContainerNode::CreateInstance(Nodegrams* engine)
{
    return new ContainerNode(engine);
}

}
} // namespace Nodegrams
