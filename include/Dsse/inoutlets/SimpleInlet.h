
#pragma once
#ifndef DSSE_FLOATINLET_H
#define DSSE_FLOATINLET_H

#include "Dsse/DssEngine.h"
//#include "Dsse/nodes/NodeBase.h"
#include "Dsse/datatypes/DataBox.h"
#include "Dsse/inoutlets/SimpleOutlet.h"

namespace dsse
{

class DSSE_EXPORT SimpleInlet : public InletBase
{
public:

	SimpleInlet(NodeBase* node, DataBox* databox, String name, String desc);
	~SimpleInlet();
	//NodeBase* getNode();
	bool Connect(OutletBase* outlet); // only called by Outlet
	DataBox* GetData() { return m_data; }
	void ReceiveData(DataBox* data);
    String GetDataString() { return m_data->ToString(); }
protected:
	DataBox* m_data;
};

}
#endif // ifndef DSSE_FLOATINLET_H
