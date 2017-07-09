
#pragma once
#ifndef DSSE_FLOATINLET_H
#define DSSE_FLOATINLET_H

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/NodeBase.h"
#include "Dsse/inoutlets/FloatInlet.h"
#include "Dsse/inoutlets/FloatOutlet.h"
#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
class FloatOutlet;

class DSSE_EXPORT FloatInlet : public InletBase
{
public:
	//DataType inbuffer;
	
	FloatInlet(NodeBase*, String, String, float);
	~FloatInlet();
	//NodeBase* getNode();
	bool Connect(FloatOutlet* outlet); // only called by Outlet
	float GetData() { return m_inValue; }
	void ReceiveData(float data);
    String GetDataString();
protected:
	float m_inValue;
	float m_defValue;
};
	
}
#endif // ifndef DSSE_FLOATINLET_H