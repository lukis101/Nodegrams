
#pragma once
#ifndef DSSE_SYSCLOCKNODE_H
#define DSSE_SYSCLOCKNODE_H

#include "Dsse/nodes/StaticNode.h"
#include "Dsse/inoutlets/FloatOutlet.h"

namespace dsse
{

class DSSE_EXPORT SysTimeNode : public StaticNode
{
public:
    String name = "SysTimeNode__";

    SysTimeNode();
    ~SysTimeNode();

	void DoLogic();
protected:
    FloatOutlet* out_ms;
    FloatOutlet* out_sec;
};

}
#endif // ifndef DSSE_SYSCLOCKNODE_H
