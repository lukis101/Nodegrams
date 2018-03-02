
#pragma once
#ifndef DSSE_STATICNODE_H
#define DSSE_STATICNODE_H

//#include "Dsse/nodes/NodeBase.h"
#include "Dsse/DssEngine.h"

namespace dsse
{

class DSSE_EXPORT StaticNode : public NodeBase
{
public:
    StaticNode(int numinlets, int numoutlets);
    virtual ~StaticNode();

	bool IsStatic() { return true; };
	bool IsContainer() { return false; }; // can containers be static?
	virtual void DoLogic() = 0;

    int GetInletCount() { return m_numinlets; };
	//int GetInletIndex(String name);
	InletBase* GetInlet(String name);
	InletBase* GetInlet(int index);

    int GetOutletCount() { return m_numoutlets; };
	//int GetOutletIndex(String name);
	OutletBase* GetOutlet(String name);
	OutletBase* GetOutlet(int index);
protected:
	int m_numinlets;
	int m_numoutlets;
	InletBase** m_inlets;
	OutletBase** m_outlets;
};

}
#endif // ifndef DSSE_STATICNODE_H
