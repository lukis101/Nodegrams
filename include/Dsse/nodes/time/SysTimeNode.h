
#pragma once
#ifndef DSSE_SYSCLOCKNODE_H
#define DSSE_SYSCLOCKNODE_H

#include "Dsse/nodes/StaticNode.h"
#include "Dsse/inoutlets/SimpleOutlet.h"

namespace dsse
{
class Int32;
class Int64;

class DSSE_EXPORT SysTimeNode : public StaticNode
{
public:
    SysTimeNode(Dsse*, ContainerNode*);
    ~SysTimeNode();

	void DoLogic();

protected:
    Int64* dout_ms;
    Int32* dout_sec;
    SimpleOutlet* out_ms;
    SimpleOutlet* out_sec;

    NodeBase* CreateInstance(Dsse* engine, ContainerNode* parent);
};

}
#endif // ifndef DSSE_SYSCLOCKNODE_H
