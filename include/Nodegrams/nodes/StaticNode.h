
#pragma once
#ifndef NDGM_STATICNODE_H
#define NDGM_STATICNODE_H

#include "Nodegrams/nodes/NodeBase.h"

namespace Nodegrams
{

class NDGM_EXPORT StaticNode : public NodeBase
{
public:
	bool IsStatic() { return true; };
	bool IsContainer() { return false; }; // can containers be static?

	virtual void DoLogic() = 0; // logic
	virtual void Update(); // logic + io

    int GetInletCount() { return m_numinlets; };
	//int GetInletIndex(String name);
	InletBase* GetInlet(String name);
	InletBase* GetInlet(int index);
    bool HasConnectedInlets();

    int GetOutletCount() { return m_numoutlets; };
	//int GetOutletIndex(String name);
	OutletBase* GetOutlet(String name);
    OutletBase* GetOutlet(int index);

protected:
	int m_numinlets;
	int m_numoutlets;
	InletBase** m_inlets;
	OutletBase** m_outlets;

    StaticNode(Nodegrams*, int numinlets, int numoutlets);
    virtual ~StaticNode();

    virtual NodeBase* CreateInstance(Nodegrams*) = 0;
};

} // namespace Nodegrams
#endif // ifndef NDGM_STATICNODE_H
