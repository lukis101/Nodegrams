
#pragma once
#ifndef NDGM_NODE_GATE_XOR_H
#define NDGM_NODE_GATE_XOR_H

#include "Nodegrams/nodes/logic/gates/Gate2i1o.h"

namespace Nodegrams {
namespace Nodes {
namespace Logic
{

class NDGM_EXPORT XORGate : public Gate2i1o
{
public:
    XORGate(Nodegrams* engine) : Gate2i1o(engine)
    {
        name = "XOR gate";
        category = "LOGIC:GATES";
        description = "Logical exclusive disjunction: Q = A XOR B";
    }
    ~XORGate() {}

	void DoLogic() { dout_q.SetValue(din_a.GetValue() != din_b.GetValue()); }

protected:
    NodeBase* CreateInstance(Nodegrams* engine) { return new XORGate(engine); }
};

} // namespace Logic
} // namespace Nodes
} // namespace Nodegrams
#endif // ifndef NDGM_NODE_GATE_XOR_H
