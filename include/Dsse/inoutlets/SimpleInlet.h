
#pragma once
#ifndef DSSE_FLOATINLET_H
#define DSSE_FLOATINLET_H

#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
class NodeBase;
class DataBox;
class OutletBase;

class DSSE_EXPORT SimpleInlet : public InletBase
{
    friend class Dsse;

public:
	SimpleInlet(NodeBase* node, DataBox* data, String name, String desc);
	~SimpleInlet();

	bool CanConnectTo(OutletBase* outlet);
	bool IsConnectedTo(OutletBase* outlet) { return m_connection == outlet; }

	// TODO Iterator of connections
	int GetNumConnections() { return m_connection != nullptr ? 1 : 0;}

protected:
	OutletBase* m_connection;

	bool Connect(OutletBase* outlet);    // only called by Outlet
	bool Disconnect(OutletBase* outlet); // only called by Outlet
    void DisconnectAll();
};

}
#endif // ifndef DSSE_FLOATINLET_H
