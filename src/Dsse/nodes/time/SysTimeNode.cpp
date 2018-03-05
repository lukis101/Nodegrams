
#include <chrono>
#include "Dsse/nodes/time/SysTimeNode.h"

namespace dsse
{
static const String NODE_NAME = "SysTimeNode";
static const String NODE_CATEGORY = "TIME";
static const String NODE_DESCR = "";

SysTimeNode::SysTimeNode()
	: StaticNode(0, 2)
{
	spdlog::get("dsse")->debug("SysTimeNode[{}] constr()", this->m_id);

	name = NODE_NAME;
	category = NODE_CATEGORY;

    //dout_ms = new DataBox
    m_outlets[0] = out_ms = new SimpleOutlet(this, dout_ms, "Milliseconds", "UNIX time in milliseconds");
    m_outlets[1] = out_sec = new SimpleOutlet(this, dout_sec, "Seconds", "UNIX time in seconds");
}
SysTimeNode::~SysTimeNode()
{
	spdlog::get("dsse")->debug("SysTimeNode[{}] destr()", this->m_id);
    delete out_ms;
    delete out_sec;
}

void SysTimeNode::DoLogic()
{
	spdlog::get("dsse")->info("[{}:SysTimeNode].DoLogic()", this->m_id);
    using namespace std::chrono;

    int64_t ms = duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
    uint32_t sec = static_cast<uint32_t>(ms/1000);

    // TODO use proper outlet data types
    //out_ms->WriteData(static_cast<float>(sec));
    //out_sec->WriteData(static_cast<float>(sec));
}

}
