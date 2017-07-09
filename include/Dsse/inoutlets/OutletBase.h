
#pragma once
#ifndef DSSE_OUTLETBASE_H
#define DSSE_OUTLETBASE_H

#include <vector>

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/NodeBase.h"
#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
class InletBase;
class NodeBase;
	
class DSSE_EXPORT OutletBase
{
public:
	String name;
	String description;
	std::vector< InletBase* > connections;
	//DataType outdata;
	
	OutletBase(NodeBase* node, String name, String desc);
	virtual ~OutletBase();

	NodeBase* GetNode() { return m_node; }
	bool IsDataReady() { return m_dataReady; }
	String GetFullName();
	virtual String GetDataString() = 0;
	virtual void SendData() = 0; // Send data to all connected inlets
	//virtual bool ConnectTo( InletBase* inlet )
	virtual bool Disconnect(InletBase* inlet);
	bool IsConnectedTo(InletBase* inlet);
	int GetNumConnections();
protected:
	NodeBase* m_node;
    bool m_dataChanged;
	bool m_dataReady;
	bool m_dataSent;
};

} // namespace dsse
#endif // ifndef DSSE_OUTLETBASE_H