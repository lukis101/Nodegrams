
#pragma once
#ifndef NDGM_NODE_GATE_OR_H
#define NDGM_NODE_GATE_OR_H

#include "Nodegrams/nodes/logic/gates/Gate2i1o.h"

namespace Nodegrams {
namespace Nodes {
namespace Logic
{

class NDGM_EXPORT ORGate : public Gate2i1o
{
public:
    ORGate(Nodegrams* engine) : Gate2i1o(engine)
    {
        name = "OR gate";
        category = "LOGIC:GATES";
        description = "Logical disjunction: Q = A OR B";
    }
    ~ORGate() {}

	void DoLogic() { dout_q.SetValue(din_a.GetValue() || din_b.GetValue()); }

protected:
    NodeBase* CreateInstance(Nodegrams* engine) { return new ORGate(engine); }
};

} // namespace Logic
} // namespace Nodes
} // namespace Nodegrams
#endif // ifndef NDGM_NODE_GATE_OR_H
