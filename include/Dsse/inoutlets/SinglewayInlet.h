
#pragma once
#ifndef DSSE_SINGLEWAYINLET_H
#define DSSE_SINGLEWAYINLET_H

#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
class NodeBase;
class DataBox;
class OutletBase;

class DSSE_EXPORT SinglewayInlet : public InletBase
{
public:
	SinglewayInlet(NodeBase* node, DataBox* data, String name, String desc);
	~SinglewayInlet();

	bool IsMultiway() { return false; }
	bool IsConnectedTo(OutletBase* outlet) { return m_connection == outlet; }

	// TODO Iterator of connections
	int GetNumConnections() { return m_connection != nullptr ? 1 : 0; }

    void DisconnectAll();

	bool Connected(OutletBase* outlet);    // only called by outlet
	bool Disconnected(OutletBase* outlet); // only called by outlet

protected:
	OutletBase* m_connection;
};

}
#endif // ifndef DSSE_SINGLEWAYINLET_H
