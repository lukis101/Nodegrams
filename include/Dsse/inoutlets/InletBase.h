
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
	//friend class OutletBase;
public:
	String name;
	String description;

	InletBase(NodeBase* node, DataBox* data, String name, String desc);
	virtual ~InletBase() = 0;

	NodeBase* GetNode() { return m_node; }
	String GetFullName();
	//void SetDataReady(bool ready) { m_dataReady = ready; }
	//bool DataReady() { return m_dataReady; }

	virtual bool Connect(OutletBase* outlet)    = 0; // only called by Outlet
	virtual bool Disconnect(OutletBase* outlet) = 0; // only called by Outlet
	//bool IsConnected() { return m_connection != nullptr; }
    virtual bool CanConnect() = 0;

protected:
	NodeBase* m_node;
	//bool m_dataReady;
};

}
#endif // ifndef DSSE_INLETBASE_H
