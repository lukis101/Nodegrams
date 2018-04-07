
#pragma once
#ifndef NDGM_TESTNODE_H
#define NDGM_TESTNODE_H

#include "Nodegrams/nodes/StaticNode.h"
#include "Nodegrams/inoutlets/SinglewayInlet.h"
#include "Nodegrams/inoutlets/MultiwayInlet.h"
#include "Nodegrams/datatypes/Float.h"
#include "Nodegrams/datatypes/Int64.h"
#include "Nodegrams/datatypes/Event.h"

namespace Nodegrams {
namespace Nodes
{

class NDGM_EXPORT TestNode : public StaticNode
{
public:
    TestNode(Nodegrams*);
    ~TestNode();

	void DoLogic();

protected:
	std::shared_ptr<spdlog::logger> m_logger;

    Data::Float din_f;
    Data::Int64 din_s64;
    Data::Event din_e;
    SinglewayInlet in_f;
    SinglewayInlet in_s64;
    MultiwayInlet in_e;

    NodeBase* CreateInstance(Nodegrams*);
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_TESTNODE_H
