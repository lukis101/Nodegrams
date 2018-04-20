
#include "spdlog/spdlog.h"

#include "Nodegrams/nodes/NodeBase.h"
#include "Nodegrams/nodes/ContainerNode.h"
#include "Nodegrams/inoutlets/InletBase.h"
#include "Nodegrams/Nodegrams.h"
#include "Nodegrams/Serializer.h"
#include "Nodegrams/Deserializer.h"

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
    serer.SetKey("Category");
    serer.AddString(category);
    serer.SetKey("Name");
    serer.AddString(name);
    if (custnamed)
    {
        serer.SetKey("Custom name");
        serer.AddString(custname);
    }
    serer.SetKey("Parent");
    serer.AddInt(m_parent->m_id);
    SerializeInoutlets(serer);
    SerializeState(serer);
    serer.EndObject();
}

void NodeBase::Deserialize(Deserializer& derer)
{
    derer.SelectMember("ID");
        int idint = derer.GetInt();
        derer.Pop();
    derer.SelectMember("Category");
        String catstr = derer.GetString();
        derer.Pop();
    derer.SelectMember("Name");
        String namestr = derer.GetString();
        derer.Pop();

    if (derer.SelectMember("Custom name"))
    {
        String cname = derer.GetString();
        SetCustomName(cname);
    }
    if (derer.SelectMember("Inlets"))
    {
        DeserializeInlets(derer);
        derer.Pop();
    }
    DeserializeState(derer);
}

void NodeBase::DeserializeInlets(Deserializer& derer)
{
    for (unsigned i=0; i<derer.ArraySize(); i++)
    {
        derer.SelectIndex(i);
        if (derer.SelectMember("Name"))
        {
            String ilet = derer.GetString();
            derer.Pop();
            InletBase* inlet = GetInlet(ilet);
            if (inlet != nullptr)
            {
                if (derer.SelectMember("Data"))
                {
                    inlet->GetData()->Deserialize(derer);
                    derer.Pop();
                }
            }
        }
        derer.Pop();
    }
}

}
} // namespace Nodegrams
