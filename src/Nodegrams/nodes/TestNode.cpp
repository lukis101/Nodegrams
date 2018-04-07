
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/TestNode.h"
#include "Nodegrams/inoutlets/SinglewayInlet.h"
#include "Nodegrams/inoutlets/MultiwayInlet.h"
#include "Nodegrams/datatypes/Float.h"
#include "Nodegrams/datatypes/Int64.h"
#include "Nodegrams/datatypes/Event.h"
#include "Nodegrams/Nodegrams.h"

namespace Nodegrams
{

TestNode::TestNode(Nodegrams* engine)
	: StaticNode(engine, 3, 0)
{
	name = "TestNode";
	category = "TESTS";

	m_logger = engine->m_logger;
    din_f = new Float(m_engine);
    din_s64 = new Int64(m_engine);
    din_e = new Event(m_engine);
    m_inlets[0] = in_f = new SinglewayInlet(this, din_f, "in_float", "");
    m_inlets[1] = in_s64 = new SinglewayInlet(this, din_s64, "in_int64", "");
    m_inlets[2] = in_e = new MultiwayInlet(this, din_e, "in_event", "");
}
TestNode::~TestNode()
{
    delete din_f;
    delete din_s64;
    delete din_e;
    delete in_f;
    delete in_s64;
    delete in_e;
}

void TestNode::DoLogic()
{

	m_logger->debug("[{}:TestNode].DoLogic()", this->m_id);
    if (in_f->HasDataChanged())
	    m_logger->debug("[{}:TestNode] got float: {}", this->m_id, din_f->GetValue());
    if (in_s64->HasDataChanged())
	    m_logger->info("[{}:TestNode] got int64: {}", this->m_id, din_s64->GetValue());
    int events = din_e->GetCount();
    if (events != 0)
    {
        din_e->Handle(events);
	    m_logger->info("[{}:TestNode] got {} event(s)", this->m_id, events);
    }
}

NodeBase* TestNode::CreateInstance(Nodegrams* engine)
{
    return new TestNode(engine);
}

} // namespace Nodegrams
