
#include "Dsse/nodes/time/SysTimeNode.h"
#include <chrono>

namespace dsse
{

SysTimeNode::SysTimeNode()
	: StaticNode(0, 2)
{
	spdlog::get("dsse")->info("SysTimeNode[{}] constr()", this->m_id);

	name = "SysTimeNode";
	category = "TIME";

    m_outlets[0] = out_ms = new FloatOutlet(this, "Milliseconds", "UNIX time in milliseconds", 0.0);
    m_outlets[1] = out_sec = new FloatOutlet(this, "Seconds", "UNIX time in seconds", 0.0);
}
SysTimeNode::~SysTimeNode()
{
	spdlog::get("dsse")->info("SysTimeNode[{}] destr()", this->m_id);
    delete out_ms;
    delete out_sec;
}

void SysTimeNode::DoLogic()
{
    using namespace std::chrono;

    int64_t ms = duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
    uint32_t sec = static_cast<uint32_t>(ms/1000);

    // TODO use proper outlet data types
    out_ms->WriteData(static_cast<float>(sec));
    out_sec->WriteData(static_cast<float>(sec));
}

}
