
#pragma once
#ifndef NDGM_TESTNODE_H
#define NDGM_TESTNODE_H

#include "Nodegrams/nodes/StaticNode.h"

namespace Nodegrams
{
namespace Data
{
class Float;
class Int64;
class Event;
}

namespace Nodes
{
class SinglewayInlet;
class MultiwayInlet;

class NDGM_EXPORT TestNode : public StaticNode
{
public:
    TestNode(Nodegrams*);
    ~TestNode();

	void DoLogic();

protected:
	std::shared_ptr<spdlog::logger> m_logger;

    Data::Float* din_f;
    Data::Int64* din_s64;
    Data::Event* din_e;
    SinglewayInlet* in_f;
    SinglewayInlet* in_s64;
    MultiwayInlet* in_e;

    NodeBase* CreateInstance(Nodegrams*);
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_TESTNODE_H
