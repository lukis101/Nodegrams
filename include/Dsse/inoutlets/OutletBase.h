
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
    friend class Dsse; // TEMP to access connections

public:
	String name;
	String description;

	OutletBase(NodeBase* node, DataBox* data, String name, String desc);
	virtual ~OutletBase();

	NodeBase* GetNode() { return m_node; }
	String GetFullName();
	virtual void SendData() = 0; // Send data to all connected inlets

	virtual bool CanConnectTo(InletBase* inlet) = 0;
	virtual bool ConnectTo(InletBase* inlet) = 0;
	virtual bool Disconnect(InletBase* inlet);
	bool IsConnectedTo(InletBase* inlet);

	// TODO Iterator of connection
	int GetNumConnections();

protected:
	NodeBase* m_node;
	std::vector<InletBase*> connections;
	//bool m_dataReady;
	//bool m_dataSent;
};

}
#endif // ifndef DSSE_OUTLETBASE_H
