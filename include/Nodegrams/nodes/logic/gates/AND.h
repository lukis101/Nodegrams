
#pragma once
#ifndef NDGM_NODE_LGATE_AND_H
#define NDGM_NODE_LGATE_AND_H

#include "Nodegrams/nodes/StaticNode.h"
#include "Nodegrams/inoutlets/SinglewayInlet.h"
#include "Nodegrams/inoutlets/SimpleOutlet.h"

namespace Nodegrams
{
class Boolean;

class NDGM_EXPORT LGateNode_AND : public StaticNode
{
public:
    LGateNode_AND(Nodegrams*);
    ~LGateNode_AND();

	void DoLogic();

protected:
    Boolean* din_a;
    Boolean* din_b;
    Boolean* dout_q;
    SinglewayInlet* in_a;
    SinglewayInlet* in_b;
    SimpleOutlet* out_q;

    NodeBase* CreateInstance(Nodegrams* engine);
};

} // namespace Nodegrams
#endif // ifndef NDGM_NODE_LGATE_AND_H
