
#pragma once
#ifndef DSSE_FLOATOUTLET_H
#define DSSE_FLOATOUTLET_H

#include "Dsse/DssEngine.h"
//#include "Dsse/nodes/NodeBase.h"
#include "Dsse/datatypes/DataBox.h"
#include "Dsse/inoutlets/SimpleInlet.h"

namespace dsse
{

class DSSE_EXPORT SimpleOutlet : public OutletBase
{
public:
	SimpleOutlet(NodeBase* node, DataBox* databox, String name, String desc);
	~SimpleOutlet();
	NodeBase* getNode();
	bool ConnectTo(InletBase* inlet);
	//void WriteData(float data);
    void DataChanged() { m_dataChanged = true; }
    void SendData();
    String GetDataString() { return m_data->ToString(); }
protected:
	DataBox* m_data;
};

}
#endif // ifndef DSSE_FLOATOUTLET_H
