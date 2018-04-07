
#pragma once
#ifndef NDGM_SYSCLOCKNODE_H
#define NDGM_SYSCLOCKNODE_H

#include "Nodegrams/nodes/StaticNode.h"
#include "Nodegrams/inoutlets/SimpleOutlet.h"
#include "Nodegrams/datatypes/Int32.h"
#include "Nodegrams/datatypes/Int64.h"
#include "Nodegrams/datatypes/Event.h"

namespace Nodegrams {
namespace Nodes
{

class NDGM_EXPORT SysTimeNode : public StaticNode
{
public:
    SysTimeNode(Nodegrams*);
    ~SysTimeNode();

	void DoLogic();

protected:
    Data::Int64 dout_ms;
    Data::Int32 dout_sec;
    Data::Event dout_tick;
    SimpleOutlet out_ms;
    SimpleOutlet out_sec;
    SimpleOutlet out_tick;

    NodeBase* CreateInstance(Nodegrams* engine);
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_SYSCLOCKNODE_H
