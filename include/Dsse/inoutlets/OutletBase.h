
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
    friend class Dsse;

public:
	String name;
	String description;
	std::vector<InletBase*> connections;

	OutletBase(NodeBase* node, DataBox* data, String name, String desc);
	virtual ~OutletBase();

	NodeBase* GetNode() { return m_node; }
	String GetFullName();
	virtual void SendData() = 0; // Send data to all connected inlets

	virtual bool CanConnectTo(InletBase* inlet) = 0;
	bool IsConnectedTo(InletBase* inlet);

	// TODO Iterator of connections
	int GetNumConnections() { return static_cast<int>(connections.size()); }

protected:
	NodeBase* m_node;
	//bool m_dataReady;
	//bool m_dataSent;

	virtual bool ConnectTo(InletBase* inlet) = 0;
	virtual bool Disconnect(InletBase* inlet);
    virtual void DisconnectAll();
};

}
#endif // ifndef DSSE_OUTLETBASE_H
