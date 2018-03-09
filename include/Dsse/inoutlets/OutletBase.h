
#pragma once
#ifndef DSSE_OUTLETBASE_H
#define DSSE_OUTLETBASE_H

#include <vector>

#include "Dsse/DssEngine.h"

namespace dsse
{
class NodeBase;
class InletBase;

class DSSE_EXPORT OutletBase
{
public:
	String name;
	String description;
	std::vector<InletBase*> connections;
	//DataType outdata;

	OutletBase(NodeBase* node, String name, String desc);
	virtual ~OutletBase();

	NodeBase* GetNode() { return m_node; }
	bool IsDataReady() { return m_dataReady; }
	String GetFullName();
	virtual String GetDataString() = 0;
	virtual void SendData() = 0; // Send data to all connected inlets

	virtual bool CanConnectTo(InletBase* inlet) = 0;
	virtual bool ConnectTo(InletBase* inlet) = 0;
	virtual bool Disconnect(InletBase* inlet);
	bool IsConnectedTo(InletBase* inlet);
	int GetNumConnections();
	//void WriteData(data_type data); // Syntax for child classes
protected:
	NodeBase* m_node;
    bool m_dataChanged;
	bool m_dataReady;
	bool m_dataSent;
};

} // namespace dsse
#endif // ifndef DSSE_OUTLETBASE_H
