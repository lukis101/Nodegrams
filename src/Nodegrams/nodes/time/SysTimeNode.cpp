
#include "spdlog/spdlog.h"

#include <chrono>
#include "Nodegrams/nodes/time/SysTimeNode.h"

namespace Nodegrams {
namespace Nodes
{

SysTimeNode::SysTimeNode(Nodegrams* engine)
	: StaticNode(engine, 0, 3),
    dout_ms(engine), dout_sec(engine), dout_tick(engine),
    out_ms(this, &dout_ms, "Milliseconds", "UNIX time in milliseconds"),
    out_sec(this, &dout_sec, "Seconds", "UNIX time in seconds"),
    out_tick(this, &dout_tick, "Tick", "Events with 1 second period")
{
	name = "SysTimeNode";
	category = "TIME";
    description = "Provides host system RTC time";

    m_outlets[0] = &out_ms;
    m_outlets[1] = &out_sec;
    m_outlets[2] = &out_tick;
}
SysTimeNode::~SysTimeNode()
{
}

void SysTimeNode::DoLogic()
{
    static uint32_t lastsecond = 0;
    using namespace std::chrono;

    int64_t ms = duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
    uint32_t sec = static_cast<uint32_t>(ms/1000);

    dout_ms.SetValue(ms);
    dout_sec.SetValue(sec);
    if (sec != lastsecond)
    {
        lastsecond = sec;
        dout_tick.Fire();
    }
}

NodeBase* SysTimeNode::CreateInstance(Nodegrams* engine)
{
    return new SysTimeNode(engine);
}

}
} // namespace Nodegrams
