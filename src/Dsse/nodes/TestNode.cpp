
#include "Dsse/nodes/TestNode.h"

namespace dsse
{

TestNode::TestNode(Dsse* engine)
	: StaticNode(engine, 1, 0)
{
	name = "TestNode";
	category = "TESTS";

    din_f = new Float(m_engine);
    m_inlets[0] = in_f = new SimpleInlet(this, din_f, "in_float", "");

	spdlog::get("dsse")->debug("TestNode[{}] constr()", this->m_id);
}
TestNode::~TestNode()
{
	spdlog::get("dsse")->debug("TestNode[{}] destr()", this->m_id);
    delete din_f;
    delete in_f;
}

void TestNode::DoLogic()
{
	spdlog::get("dsse")->info("[{}:TestNode].DoLogic()", this->m_id);
    if (m_inlets[0]->DataChanged())
	    spdlog::get("dsse")->info("[{}:TestNode].DChange: ", din_f->GetValue());
}

}
