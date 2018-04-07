
#include "spdlog/spdlog.h"

#include <chrono>
#include "Nodegrams/nodes/time/SysTimeNode.h"
#include "Nodegrams/datatypes/Int32.h"
#include "Nodegrams/datatypes/Int64.h"
#include "Nodegrams/datatypes/Event.h"

namespace Nodegrams
{

SysTimeNode::SysTimeNode(Nodegrams* engine)
	: StaticNode(engine, 0, 3)
{
	name = "SysTimeNode";
	category = "TIME";
    description = "Provides host system RTC time";

    dout_ms   = new Int64(m_engine);
    dout_sec  = new Int32(m_engine);
    dout_tick = new Event(m_engine);
    m_outlets[0] = out_ms   = new SimpleOutlet(this, dout_ms, "Milliseconds", "UNIX time in milliseconds");
    m_outlets[1] = out_sec  = new SimpleOutlet(this, dout_sec, "Seconds", "UNIX time in seconds");
    m_outlets[2] = out_tick = new SimpleOutlet(this, dout_tick, "Tick", "Events with 1 second period");
}
SysTimeNode::~SysTimeNode()
{
    delete out_ms;
    delete out_sec;
    delete out_tick;
    delete dout_ms;
    delete dout_sec;
    delete dout_tick;
}

void SysTimeNode::DoLogic()
{
    static uint32_t lastsecond = 0;
    using namespace std::chrono;

    int64_t ms = duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
    uint32_t sec = static_cast<uint32_t>(ms/1000);

    dout_ms->SetValue(ms);
    dout_sec->SetValue(sec);
    if (sec != lastsecond)
    {
        lastsecond = sec;
        dout_tick->Fire();
    }
}

NodeBase* SysTimeNode::CreateInstance(Nodegrams* engine)
{
    return new SysTimeNode(engine);
}

} // namespace Nodegrams
