
#include "spdlog/spdlog.h"

#include "Dsse/nodes/TestNode.h"
#include "Dsse/inoutlets/SimpleInlet.h"
#include "Dsse/datatypes/Float.h"
#include "Dsse/datatypes/Int64.h"

namespace dsse
{

TestNode::TestNode(Dsse* engine, ContainerNode* parent)
	: StaticNode(engine, parent, 2, 0)
{
	name = "TestNode";
	category = "TESTS";

    din_f = new Float(m_engine);
    din_s64 = new Int64(m_engine);
    m_inlets[0] = in_f = new SimpleInlet(this, din_f, "in_float", "");
    m_inlets[1] = in_s64 = new SimpleInlet(this, din_s64, "in_int64", "");

	spdlog::get("dsse")->debug("TestNode[{}] constr()", this->m_id);
}
TestNode::~TestNode()
{
	spdlog::get("dsse")->debug("TestNode[{}] destr()", this->m_id);
    delete din_f;
    delete din_s64;
    delete in_f;
    delete in_s64;
}

void TestNode::DoLogic()
{
	/*spdlog::get("dsse")->info("[{}:TestNode].DoLogic()", this->m_id);
    if (m_inlets[0]->HasDataChanged())
	    spdlog::get("dsse")->info("[{}:TestNode] got float: {}",
            this->m_id, din_f->GetValue());
    if (m_inlets[1]->HasDataChanged())
	    spdlog::get("dsse")->info("[{}:TestNode] got int64: {}",
            this->m_id, din_s64->GetValue());*/
}

NodeBase* TestNode::CreateInstance(Dsse* engine, ContainerNode* parent)
{
    return new TestNode(engine, parent);
}

}
