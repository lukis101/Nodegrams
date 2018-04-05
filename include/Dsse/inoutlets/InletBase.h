
#pragma once
#ifndef DSSE_INLETBASE_H
#define DSSE_INLETBASE_H

#include "Dsse/Config.h"
#include "Dsse/DataTypes.h"
#include "Dsse/inoutlets/DataHolder.h"

namespace dsse
{
class NodeBase;
class OutletBase;
//class DataBox;

class DSSE_EXPORT InletBase : public DataHolder
{
    //friend class Dsse;

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

}
#endif // ifndef DSSE_INLETBASE_H
