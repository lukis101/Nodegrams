
#pragma once
#ifndef DSSE_OUTLETBASE_H
#define DSSE_OUTLETBASE_H

#include <vector>
#include "Dsse/Config.h"
#include "Dsse/DataTypes.h"
#include "Dsse/inoutlets/DataHolder.h"

namespace dsse
{
class NodeBase;
class InletBase;

class DSSE_EXPORT OutletBase : public DataHolder
{
public:
	String name;
	String description;
	std::vector<InletBase*> connections;

	OutletBase(NodeBase* node, DataBox* data, String name, String desc);
	virtual ~OutletBase();

	NodeBase* GetNode() { return m_node; }
	String GetFullName();
	//bool IsDataReady() { return m_dataReady; }
	//virtual void SendData() = 0; // Send data to all connected inlets

	virtual bool CanConnectTo(InletBase* inlet) = 0;
	virtual bool ConnectTo(InletBase* inlet) = 0;
	virtual bool Disconnect(InletBase* inlet);
	bool IsConnectedTo(InletBase* inlet);
	int GetNumConnections();
	//void WriteData(data_type data); // Syntax for child classes
protected:
	NodeBase* m_node;
	//bool m_dataReady;
	//bool m_dataSent;
};

} // namespace dsse
#endif // ifndef DSSE_OUTLETBASE_H
