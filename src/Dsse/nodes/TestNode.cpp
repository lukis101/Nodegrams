
#include "spdlog/spdlog.h"

#include "Dsse/nodes/TestNode.h"
#include "Dsse/nodes/NodeContainer.h"

namespace dsse
{

TestNode::TestNode()
	: StaticNode(2, 2)
{
	name = "UnnamedNode";
	classname = "Unknown";
	category = "Unknown";
	
	spdlog::get("iolet")->info("TestNode({}) constr()", this->m_id);
}
TestNode::~TestNode()
{
	spdlog::get("iolet")->info("TestNode({}) destr()", this->m_id);
}


}