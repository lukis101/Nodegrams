
#pragma once
#ifndef DSSE_SYSCLOCKNODE_H
#define DSSE_SYSCLOCKNODE_H

#include "Dsse/nodes/StaticNode.h"
#include "Dsse/inoutlets/SimpleOutlet.h"

namespace dsse
{

class DSSE_EXPORT SysTimeNode : public StaticNode
{
public:
    SysTimeNode();
    ~SysTimeNode();

	void DoLogic();
protected:
    DataBox* dout_ms;
    DataBox* dout_sec;
    SimpleOutlet* out_ms;
    SimpleOutlet* out_sec;
};

}
#endif // ifndef DSSE_SYSCLOCKNODE_H
