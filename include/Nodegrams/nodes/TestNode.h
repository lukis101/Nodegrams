
#pragma once
#ifndef NDGM_TESTNODE_H
#define NDGM_TESTNODE_H

#include "Nodegrams/nodes/StaticNode.h"

namespace Nodegrams
{
class SinglewayInlet;
class MultiwayInlet;
class Float;
class Int64;
class Event;

class NDGM_EXPORT TestNode : public StaticNode
{
public:
    TestNode(Nodegrams*);
    ~TestNode();

	void DoLogic();

protected:
	std::shared_ptr<spdlog::logger> m_logger;

    Float* din_f;
    Int64* din_s64;
    Event* din_e;
    SinglewayInlet* in_f;
    SinglewayInlet* in_s64;
    MultiwayInlet* in_e;

    NodeBase* CreateInstance(Nodegrams*);
};

} // namespace Nodegrams
#endif // ifndef NDGM_TESTNODE_H
