
#pragma once
#ifndef NDGM_MULTIWAYINLET_H
#define NDGM_MULTIWAYINLET_H

#include <vector>
#include "Nodegrams/inoutlets/InletBase.h"

namespace Nodegrams
{
class NodeBase;
class DataBox;
class OutletBase;

class NDGM_EXPORT MultiwayInlet : public InletBase
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

} // namespace Nodegrams
#endif // ifndef NDGM_MULTIWAYINLET_H
