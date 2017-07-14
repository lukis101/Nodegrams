
#pragma once
#ifndef DSSE_TESTNODE_H
#define DSSE_TESTNODE_H

//#include <memory>

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/NodeBase.h"

namespace dsse
{

class DSSE_EXPORT StaticNode : public NodeBase
{
public:
    StaticNode(int numinlets, int numoutlets);
    virtual ~StaticNode();

	bool IsStatic() { return true };
    int GetInletCount()  { return m_numinlets; };
	InletBase* GetInlet(String name);
	InletBase* GetInlet(int index);

    int GetOutletCount() { return m_numoutlets; };
	OutletBase* GetOutlet(String name);
	OutletBase* GetOutlet(int index);
//protected:
};
class DSSE_EXPORT DynamicNode : public NodeBase
{
public:
    DynamicNode();
    virtual ~DynamicNode();
	
	bool IsStatic() { return false };
	virtual int GetInletCount() = 0;
	InletBase* GetInlet(String name);
	InletBase* GetInlet(int index);
	
	virtual int GetOutletCount() = 0;
	OutletBase* GetOutlet(String name);
	OutletBase* GetOutlet(int index);
//protected:
};

}
#endif // ifndef DSSE_TESTNODE_H