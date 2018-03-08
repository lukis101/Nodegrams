
#include "Dsse/nodes/TestNode.h"

namespace dsse
{

TestNode::TestNode(Dsse* engine)
	: StaticNode(engine, 2, 2)
{
	name = "TestNode";
	category = "TESTS";

	spdlog::get("dsse")->debug("TestNode[{}] constr()", this->m_id);
}
TestNode::~TestNode()
{
	spdlog::get("dsse")->debug("TestNode[{}] destr()", this->m_id);
}

void TestNode::DoLogic()
{
	spdlog::get("dsse")->info("[{}:TestNode].DoLogic()", this->m_id);
}

}
