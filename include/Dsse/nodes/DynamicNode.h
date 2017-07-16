
#pragma once
#ifndef DSSE_DYNAMICNODE_H
#define DSSE_DYNAMICNODE_H

//#include <memory>

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/NodeBase.h"

namespace dsse
{

class DSSE_EXPORT DynamicNode : public NodeBase
{
public:
    DynamicNode();
    virtual ~DynamicNode();
	
	bool IsStatic() { return false };
	virtual bool IsContainer() { return false };
	
	int GetInletCount() { return inlets.size() };
	InletBase* GetInlet(String name);
	InletBase* GetInlet(int index);
	void RemoveInlet(String name);
	
	int GetOutletCount() { return inlets.size() };
	OutletBase* GetOutlet(String name);
	OutletBase* GetOutlet(int index);
protected:
	std::vector<InletBase*> inlets;
	std::vector<OutletBase*> outlets;
};

}
#endif // ifndef DSSE_DYNAMICNODE_H