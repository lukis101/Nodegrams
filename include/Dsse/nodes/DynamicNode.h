
#pragma once
#ifndef DSSE_DYNAMICNODE_H
#define DSSE_DYNAMICNODE_H

#include <vector>
#include "Dsse/nodes/NodeBase.h"

namespace dsse
{

class DSSE_EXPORT DynamicNode : public NodeBase
{
public:
    DynamicNode(Dsse*, ContainerNode*);
    virtual ~DynamicNode();

	bool IsStatic() { return false; };
	virtual bool IsContainer() { return false; };

	virtual void DoLogic() = 0; // logic
	virtual void Update(); // logic + io

	int GetInletCount() { return static_cast<int>(m_inlets.size()); };
	InletBase* GetInlet(String name);
	InletBase* GetInlet(int index);
	void RemoveInlet(String name);
    bool HasConnectedInlets();

	int GetOutletCount() { return static_cast<int>(m_outlets.size()); };
	OutletBase* GetOutlet(String name);
	OutletBase* GetOutlet(int index);
protected:
	std::vector<InletBase*> m_inlets;
	std::vector<OutletBase*> m_outlets;
};

}
#endif // ifndef DSSE_DYNAMICNODE_H
