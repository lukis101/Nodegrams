
#pragma once
#ifndef DSSE_INLETBASE_H
#define DSSE_INLETBASE_H

#include "Dsse/DssEngine.h"
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class NodeBase;
class OutletBase;

class DSSE_EXPORT InletBase
{
	//friend class OutletBase;
public:
	InletBase(NodeBase* node, String name, String desc);
	String name;
	String description;
	//DataType indata;

public:
	virtual ~InletBase() = 0;
	NodeBase* GetNode() { return m_node; }
	virtual bool Connect(OutletBase* outlet) = 0; // only called by Outlet
	void SetDataReady(bool ready) { m_dataReady = ready; }
	bool DataReady() { return m_dataReady; }
	bool DataChanged() { return m_dataChanged; }
	String GetFullName();
	virtual String GetDataString() = 0;
	virtual void ReceiveData(DataBox* data) = 0;
	virtual bool Disconnect(OutletBase* outlet); // only called by Outlet
	bool IsConnected();

protected:
	NodeBase* m_node;
	OutletBase* m_connection;
	bool m_dataReady;
	bool m_dataChanged;

};

}
#endif // ifndef DSSE_INLETBASE_H
