
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/TestNode.h"
#include "Nodegrams/Nodegrams.h"

namespace Nodegrams {
namespace Nodes
{

TestNode::TestNode(Nodegrams* engine)
	: StaticNode(engine, 3, 0),
    din_f(engine), din_s64(engine), din_e(engine),
    in_f(this,   &din_f,   "in_float", ""),
    in_s64(this, &din_s64, "in_int64", ""),
    in_e(this,   &din_e,   "in_event", "")
{
	name = "TestNode";
	category = "TESTS";

	m_logger = engine->m_logger;
    m_inlets[0] = &in_f;
    m_inlets[1] = &in_s64;
    m_inlets[2] = &in_e;
}
TestNode::~TestNode()
{
}

void TestNode::DoLogic()
{
	m_logger->debug("[{}:TestNode].DoLogic()", this->m_id);
    if (in_f.HasDataChanged())
	    m_logger->debug("[{}:TestNode] got float: {}", this->m_id, din_f.GetValue());
    if (in_s64.HasDataChanged())
	    m_logger->debug("[{}:TestNode] got int64: {}", this->m_id, din_s64.GetValue());
    int events = din_e.GetCount();
    if (events != 0)
    {
        din_e.Handle(events);
	    m_logger->info("[{}:TestNode] got {} event(s)", this->m_id, events);
    }
}

NodeBase* TestNode::CreateInstance(Nodegrams* engine)
{
    return new TestNode(engine);
}

}
} // namespace Nodegrams
