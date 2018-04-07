
#include "Nodegrams/nodes/logic/gates/Gate2i1o.h"

namespace Nodegrams {
namespace Nodes {
namespace Logic
{

Gate2i1o::Gate2i1o(Nodegrams* engine)
	: StaticNode(engine, 2, 1),
    din_a(m_engine), din_b(m_engine), dout_q(m_engine),
    in_a(this,  &din_a,  "A", "Input A"),
    in_b(this,  &din_b,  "B", "Input B"),
    out_q(this, &dout_q, "Q", "Output")
{
	name = "Unnamed gate";
	category = "LOGIC:GATES";

    m_inlets[0]  = &in_a;
    m_inlets[1]  = &in_b;
    m_outlets[0] = &out_q;
}
Gate2i1o::~Gate2i1o()
{
}

} // namespace Logic
} // namespace Nodes
} // namespace Nodegrams
