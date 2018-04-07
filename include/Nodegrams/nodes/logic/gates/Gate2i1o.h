
#pragma once
#ifndef NDGM_NODE_GATE2I1O_H
#define NDGM_NODE_GATE2I1O_H

#include "Nodegrams/nodes/StaticNode.h"
#include "Nodegrams/datatypes/Boolean.h"
#include "Nodegrams/inoutlets/SinglewayInlet.h"
#include "Nodegrams/inoutlets/SimpleOutlet.h"

namespace Nodegrams {
namespace Nodes {
namespace Logic
{

class NDGM_EXPORT Gate2i1o : public StaticNode
{
public:
    Gate2i1o(Nodegrams*);
    virtual ~Gate2i1o();

	virtual void DoLogic() = 0;

protected:
    Data::Boolean  din_a;
    Data::Boolean  din_b;
    Data::Boolean  dout_q;
    SinglewayInlet in_a;
    SinglewayInlet in_b;
    SimpleOutlet   out_q;

    //virtual NodeBase* CreateInstance(Nodegrams* engine) = 0;
};

} // namespace Logic
} // namespace Nodes
} // namespace Nodegrams
#endif // ifndef NDGM_NODE_GATE2I1O_H
