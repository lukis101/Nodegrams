
#pragma once
#ifndef NDGM_FLOATOUTLET_H
#define NDGM_FLOATOUTLET_H

#include "Nodegrams/inoutlets/OutletBase.h"

namespace Nodegrams
{
class DataBox;

namespace Nodes
{
class NodeBase;
class InletBase;

class NDGM_EXPORT SimpleOutlet : public OutletBase
{
    friend class Nodegrams;

public:
	SimpleOutlet(NodeBase* node, DataBox* databox, String name, String desc);
	~SimpleOutlet();
	NodeBase* getNode();

    void SendData();

	bool CanConnectTo(InletBase* inlet);

protected:
	bool ConnectTo(InletBase* inlet);
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_FLOATOUTLET_H
