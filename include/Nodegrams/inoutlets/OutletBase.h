
#pragma once
#ifndef NDGM_OUTLETBASE_H
#define NDGM_OUTLETBASE_H

#include <vector>
#include "Nodegrams/Config.h"
#include "Nodegrams/DataTypes.h"
#include "Nodegrams/inoutlets/DataHolder.h"

namespace Nodegrams {
namespace Nodes
{
class NodeBase;
class InletBase;

class NDGM_EXPORT OutletBase : public DataHolder
{
    //friend class Nodegrams;

public:
	String name;
	String description;
	std::vector<InletBase*> connections;

	NodeBase* GetNode() { return m_node; }
	String GetFullName();
	virtual void SendData() = 0; // Send data to all connected inlets

	virtual bool CanConnectTo(InletBase* inlet) = 0;
	bool IsConnectedTo(InletBase* inlet);

	// TODO Iterator of connections
	int GetNumConnections() { return static_cast<int>(connections.size()); }

	virtual bool ConnectTo(InletBase* inlet) = 0;
	virtual bool Disconnect(InletBase* inlet);
    virtual void DisconnectAll();

protected:
	NodeBase* m_node;

	OutletBase(NodeBase* node, DataBox* data, String name, String desc);
	virtual ~OutletBase();
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_OUTLETBASE_H
