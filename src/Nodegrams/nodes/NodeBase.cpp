
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/NodeBase.h"
#include "Nodegrams/nodes/ContainerNode.h"
#include "Nodegrams/Nodegrams.h"

namespace Nodegrams {
namespace Nodes
{

NodeBase::NodeBase(Nodegrams* engine)
{
    m_engine = engine;
    m_parent = engine->rootcontainer;
    m_id = 0;

	name = "UnnamedNode";
	category = "NONE";
    description = "No description";
	custname = "";
	custnamed = false;
	//processed = false;
}

NodeBase::~NodeBase()
{
}

void NodeBase::SetCustomName(String thename)
{
	if (thename.empty() )
	{
		custnamed = false;
		return;
	}
	custname = thename;
	custnamed = true;
}

void NodeBase::Serialize(Serializer& serer)
{
    serer.StartObject();
    serer.SetKey("ID");
    serer.AddInt(m_id);
    serer.SetKey("Name");
    serer.AddString(GetName());
    serer.SetKey("Parent");
    serer.AddInt(m_parent->m_id);
    SerializeInoutlets(serer);
    SerializeState(serer);
    serer.EndObject();
}

}
} // namespace Nodegrams
