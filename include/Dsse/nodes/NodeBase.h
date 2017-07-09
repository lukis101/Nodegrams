
#pragma once
#ifndef DSSE_NODEBASE_H
#define DSSE_NODEBASE_H

//#include <memory>
//#include <vector>
#include <array>

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/NodeContainer.h"
#include "Dsse/inoutlets/InletBase.h"
#include "Dsse/inoutlets/OutletBase.h"

namespace dsse
{
class InletBase;
class OutletBase;
class NodeContainer;
	
class DSSE_EXPORT NodeBase
{
public:
	String name;
	String classname;
	String category;
	String custname;
	bool custnamed;
	//shared_ptr<NodeContainer> parent;
	bool processed; // Logic and data exchange complete
	
	NodeBase(NodeContainer* parent, int id);
    ~NodeBase();
	virtual void DoLogic() = 0;
	int GetID() { return m_id; }
	
	virtual int GetInletCount() = 0;
	InletBase* GetInlet(String name);
	InletBase* GetInlet(int index);
	
	virtual int GetOutletCount() = 0;
	OutletBase* GetOutlet(String name);
	OutletBase* GetOutlet(int index);
	
	void setCustomName(String name);

protected:
	NodeContainer* m_parent;
	int m_id;
	//const int inletCount;
	std::array<InletBase*,2> inlets;
	std::array<OutletBase*,2> outlets;
};

}
#endif // ifndef DSSE_NODEBASE_H