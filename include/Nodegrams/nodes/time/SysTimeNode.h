
#pragma once
#ifndef NDGM_SYSCLOCKNODE_H
#define NDGM_SYSCLOCKNODE_H

#include "Nodegrams/nodes/StaticNode.h"
#include "Nodegrams/inoutlets/SimpleOutlet.h"

namespace Nodegrams
{
class Int32;
class Int64;
class Event;

class NDGM_EXPORT SysTimeNode : public StaticNode
{
public:
    SysTimeNode(Nodegrams*);
    ~SysTimeNode();

	void DoLogic();

protected:
    Int64* dout_ms;
    Int32* dout_sec;
    Event* dout_tick;
    SimpleOutlet* out_ms;
    SimpleOutlet* out_sec;
    SimpleOutlet* out_tick;

    NodeBase* CreateInstance(Nodegrams* engine);
};

} // namespace Nodegrams
#endif // ifndef NDGM_SYSCLOCKNODE_H
