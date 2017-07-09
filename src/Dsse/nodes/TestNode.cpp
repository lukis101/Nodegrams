
#include "spdlog/spdlog.h"

#include "Dsse/nodes/TestNode.h"
#include "Dsse/nodes/NodeContainer.h"

namespace dsse
{

TestNode::TestNode(NodeContainer* parent, int id)
	: NodeBase(parent, id)
{
	name = "UnnamedNode";
	classname = "Unknown";
	category = "Unknown";
	
	spdlog::get("iolet")->info("TestNode({}) constr()", this->m_id);
}
TestNode::~TestNode()
{
	spdlog::get("iolet")->info("TestNode({}) destr()", this->m_id);
}

int TestNode::GetInletCount()
{
	return 2;
}
int TestNode::GetOutletCount()
{
	return 2;
}

}