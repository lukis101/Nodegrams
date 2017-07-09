
#pragma once
#ifndef DSSE_FLOATOUTLET_H
#define DSSE_FLOATOUTLET_H

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/NodeBase.h"
#include "Dsse/inoutlets/OutletBase.h"
#include "Dsse/inoutlets/FloatInlet.h"

namespace dsse
{
class FloatInlet;
	
class DSSE_EXPORT FloatOutlet : public OutletBase
{
public:
	//DataType inbuffer;
	
	FloatOutlet(NodeBase* node, String name, String desc, float defValue);
	~FloatOutlet();
	NodeBase* getNode();
	void WriteData(float data);
	bool ConnectTo(FloatInlet* inlet);
    void SendData();
    String GetDataString();
protected:
	float m_outValue;
	float m_defValue;
};

}
#endif // ifndef DSSE_FLOATOUTLET_H