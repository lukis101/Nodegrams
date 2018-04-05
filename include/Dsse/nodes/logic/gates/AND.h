
#pragma once
#ifndef DSSE_NODE_LGATE_AND_H
#define DSSE_NODE_LGATE_AND_H

#include "Dsse/nodes/StaticNode.h"
#include "Dsse/inoutlets/SinglewayInlet.h"
#include "Dsse/inoutlets/SimpleOutlet.h"

namespace dsse
{
class Boolean;

class DSSE_EXPORT LGateNode_AND : public StaticNode
{
public:
    LGateNode_AND(Dsse*);
    ~LGateNode_AND();

	void DoLogic();

protected:
    Boolean* din_a;
    Boolean* din_b;
    Boolean* dout_q;
    SinglewayInlet* in_a;
    SinglewayInlet* in_b;
    SimpleOutlet* out_q;

    NodeBase* CreateInstance(Dsse* engine);
};

}
#endif // ifndef DSSE_NODE_LGATE_AND_H
