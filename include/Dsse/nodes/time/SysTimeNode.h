
#pragma once
#ifndef DSSE_SYSCLOCKNODE_H
#define DSSE_SYSCLOCKNODE_H

#include "Dsse/nodes/StaticNode.h"
#include "Dsse/inoutlets/SimpleOutlet.h"
#include "Dsse/datatypes/Float.h"
#include "Dsse/datatypes/Double.h"

namespace dsse
{

class DSSE_EXPORT SysTimeNode : public StaticNode
{
public:
    SysTimeNode(Dsse*);
    ~SysTimeNode();

	void DoLogic();
protected:
    // TODO use proper outlet data types
    Double* dout_ms;
    Float* dout_sec;
    SimpleOutlet* out_ms;
    SimpleOutlet* out_sec;
};

}
#endif // ifndef DSSE_SYSCLOCKNODE_H
