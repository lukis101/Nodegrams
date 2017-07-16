
#include "Dsse/nodes/NodeBase.h"
#include "spdlog/spdlog.h"

namespace dsse
{

// Protected: self building / remote engine interface
NodeBase::NodeBase(Dsse engine, int id, String name)
{
	engine.RegisterNode(this, id);
	//m_id = id;
	m_parent = parent;

	name = name;//"UnnamedNode";
	category = "NONE";
	custname = name;
	custnamed = false;
	processed = false;
	
	spdlog::get("iolet")->info("NodeBase() \"{}\" constr()", name);
}
// public: users create nodes
NodeBase::NodeBase(String name)
{
	//m_id = -1;
	//m_parent = nullptr;
	//engine.registerNode(this);

	name = name;//"UnnamedNode";
	category = "NONE";
	custname = name;
	custnamed = false;
	processed = false;
	
	spdlog::get("iolet")->info("NodeBase() \"{}\" constr()", name);
}
NodeBase::~NodeBase()
{
	spdlog::get("iolet")->info("NodeBase() \"{}\" destr()", name);
}

void NodeBase::setCustomName(String thename)
{
	if(thename.empty() )
	{
		custnamed = false;
		return;
	}
	custname = thename;
	custnamed = true;
}
	
}