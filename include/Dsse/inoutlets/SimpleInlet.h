
#pragma once
#ifndef DSSE_FLOATINLET_H
#define DSSE_FLOATINLET_H

#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
class NodeBase;
class DataBox;
class OutletBase;

class DSSE_EXPORT SimpleInlet : public InletBase
{
public:
	SimpleInlet(NodeBase* node, DataBox* data, String name, String desc);
	~SimpleInlet();

	bool Connect(OutletBase* outlet); // only called by Outlet
	//void ReceiveData(DataBox* data);
protected:
};

}
#endif // ifndef DSSE_FLOATINLET_H
