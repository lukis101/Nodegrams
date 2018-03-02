
#include "Dsse/nodes/TestNode.h"

namespace dsse
{

TestNode::TestNode()
	: StaticNode(2, 2)
{
	name = "TestNode";
	category = "TESTS";

	spdlog::get("dsse")->info("TestNode[{}] constr()", this->m_id);
}
TestNode::~TestNode()
{
	spdlog::get("dsse")->info("TestNode[{}] destr()", this->m_id);
}

void TestNode::DoLogic()
{
	spdlog::get("dsse")->info("TestNode[{}].DoLogic()", this->m_id);
}

}
