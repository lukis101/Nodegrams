
#pragma once
#ifndef NDGM_INLETBASE_H
#define NDGM_INLETBASE_H

#include "Nodegrams/Config.h"
#include "Nodegrams/DataTypes.h"
#include "Nodegrams/inoutlets/DataHolder.h"

namespace Nodegrams
{
class NodeBase;
class OutletBase;
//class DataBox;

class NDGM_EXPORT InletBase : public DataHolder
{
    //friend class Nodegrams;

public:
	String name;
	String description;

	NodeBase* GetNode() { return m_node; }
	String GetFullName();

	virtual bool IsMultiway() = 0;
	virtual bool IsConnectedTo(OutletBase* outlet) = 0;

	// TODO Iterator of connections
	virtual int GetNumConnections() = 0;

    virtual void DisconnectAll() = 0;

	virtual bool Connected(OutletBase* outlet)    = 0; // only called by outlet
	virtual bool Disconnected(OutletBase* outlet) = 0; // only called by outlet

protected:
	NodeBase* m_node;

	InletBase(NodeBase* node, DataBox* data, String name, String desc);
	virtual ~InletBase() = 0;
};

} // namespace Nodegrams
#endif // ifndef NDGM_INLETBASE_H
