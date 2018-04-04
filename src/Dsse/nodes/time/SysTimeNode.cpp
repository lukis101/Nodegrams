
#include "spdlog/spdlog.h"

#include <chrono>
#include "Dsse/nodes/time/SysTimeNode.h"
#include "Dsse/datatypes/Int32.h"
#include "Dsse/datatypes/Int64.h"

namespace dsse
{

SysTimeNode::SysTimeNode(Dsse* engine)
	: StaticNode(engine, 0, 2)
{
	spdlog::get("dsse")->debug("SysTimeNode[{}] constr()", this->m_id);

	name = "SysTimeNode";
	category = "TIME";
    description = "Provides host system RTC time";

    dout_ms = new Int64(m_engine);
    dout_sec = new Int32(m_engine);
    m_outlets[0] = out_ms = new SimpleOutlet(this, dout_ms, "Milliseconds", "UNIX time in milliseconds");
    m_outlets[1] = out_sec = new SimpleOutlet(this, dout_sec, "Seconds", "UNIX time in seconds");
}
SysTimeNode::~SysTimeNode()
{
	spdlog::get("dsse")->debug("SysTimeNode[{}] destr()", this->m_id);
    delete out_ms;
    delete out_sec;
    delete dout_ms;
    delete dout_sec;
}

void SysTimeNode::DoLogic()
{
    using namespace std::chrono;

    int64_t ms = duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
    uint32_t sec = static_cast<uint32_t>(ms/1000);

    dout_ms->SetValue(ms);
    dout_sec->SetValue(sec);
}

NodeBase* SysTimeNode::CreateInstance(Dsse* engine)
{
    return new SysTimeNode(engine);
}

}
