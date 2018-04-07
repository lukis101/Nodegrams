
#pragma once
#ifndef NDGM_DYNAMICNODE_H
#define NDGM_DYNAMICNODE_H

#include <vector>
#include "Nodegrams/nodes/NodeBase.h"

namespace Nodegrams
{

class NDGM_EXPORT DynamicNode : public NodeBase
{
public:
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

    DynamicNode(Nodegrams*);
    virtual ~DynamicNode();

    virtual NodeBase* CreateInstance(Nodegrams*) = 0;
};

} // namespace Nodegrams
#endif // ifndef NDGM_DYNAMICNODE_H
