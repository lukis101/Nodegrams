
#pragma once
#ifndef NDGM_SINGLEWAYINLET_H
#define NDGM_SINGLEWAYINLET_H

#include "Nodegrams/inoutlets/InletBase.h"

namespace Nodegrams
{
class DataBox;

namespace Nodes
{
class NodeBase;
class OutletBase;

class NDGM_EXPORT SinglewayInlet : public InletBase
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
} // namespace Nodegrams
#endif // ifndef NDGM_SINGLEWAYINLET_H
