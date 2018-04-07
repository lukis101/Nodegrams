
#pragma once
#ifndef NDGM_NODE_GATE_AND_H
#define NDGM_NODE_GATE_AND_H

#include "Nodegrams/nodes/logic/gates/Gate2i1o.h"

namespace Nodegrams {
namespace Nodes {
namespace Logic
{

class NDGM_EXPORT ANDGate : public Gate2i1o
{
public:
    ANDGate(Nodegrams* engine) : Gate2i1o(engine)
    {
        name = "AND gate";
        category = "LOGIC:GATES";
        description = "Logical conjunction: Q = A AND B";
    }
    ~ANDGate() {}

	void DoLogic() { dout_q.SetValue(din_a.GetValue() && din_b.GetValue()); }

protected:
    NodeBase* CreateInstance(Nodegrams* engine) { return new ANDGate(engine); }
};

} // namespace Logic
} // namespace Nodes
} // namespace Nodegrams
#endif // ifndef NDGM_NODE_GATE_AND_H
