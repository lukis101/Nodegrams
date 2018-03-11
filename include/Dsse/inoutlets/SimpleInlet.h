
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
public:
	SimpleInlet(NodeBase* node, DataBox* data, String name, String desc);
	~SimpleInlet();

	bool Connect(OutletBase* outlet);    // only called by Outlet
	bool Disconnect(OutletBase* outlet); // only called by Outlet
	bool IsConnected() { return m_connection != nullptr; }
    bool CanConnect() { return m_connection == nullptr; }

protected:
	OutletBase* m_connection;
};

}
#endif // ifndef DSSE_FLOATINLET_H
