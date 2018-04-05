
#include "spdlog/spdlog.h"

#include "Dsse/nodes/TestNode.h"
#include "Dsse/inoutlets/SinglewayInlet.h"
#include "Dsse/inoutlets/MultiwayInlet.h"
#include "Dsse/datatypes/Float.h"
#include "Dsse/datatypes/Int64.h"
#include "Dsse/datatypes/Event.h"

namespace dsse
{

TestNode::TestNode(Dsse* engine)
	: StaticNode(engine, 3, 0)
{
	name = "TestNode";
	category = "TESTS";

    din_f = new Float(m_engine);
    din_s64 = new Int64(m_engine);
    din_e = new Event(m_engine);
    m_inlets[0] = in_f = new SinglewayInlet(this, din_f, "in_float", "");
    m_inlets[1] = in_s64 = new SinglewayInlet(this, din_s64, "in_int64", "");
    m_inlets[2] = in_e = new MultiwayInlet(this, din_e, "in_event", "");

	spdlog::get("dsse")->debug("TestNode[{}] constr()", this->m_id);
}
TestNode::~TestNode()
{
	spdlog::get("dsse")->debug("TestNode[{}] destr()", this->m_id);
    delete din_f;
    delete din_s64;
    delete din_e;
    delete in_f;
    delete in_s64;
    delete in_e;
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
    int events = din_e->GetCount();
    if (events != 0)
    {
        din_e->Handle(events);
	    spdlog::get("dsse")->info("[{}:TestNode] got {} event(s)",
            this->m_id, events);
    }
}

NodeBase* TestNode::CreateInstance(Dsse* engine)
{
    return new TestNode(engine);
}

}
