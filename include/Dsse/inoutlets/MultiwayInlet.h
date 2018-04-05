
#pragma once
#ifndef DSSE_MULTIWAYINLET_H
#define DSSE_MULTIWAYINLET_H

#include <vector>
#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
class NodeBase;
class DataBox;
class OutletBase;

class DSSE_EXPORT MultiwayInlet : public InletBase
{
public:
	std::vector<OutletBase*> connections;

	MultiwayInlet(NodeBase* node, DataBox* data, String name, String desc);
	~MultiwayInlet();

	bool IsMultiway() { return true; }
	bool IsConnectedTo(OutletBase* outlet);

	// TODO Iterator of connections
	int GetNumConnections() { return static_cast<int>(connections.size()); }

    void DisconnectAll();

	bool Connected(OutletBase* outlet);    // only called by Outlet
	bool Disconnected(OutletBase* outlet); // only called by Outlet

protected:
};

}
#endif // ifndef DSSE_MULTIWAYINLET_H
