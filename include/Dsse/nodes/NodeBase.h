
#pragma once
#ifndef DSSE_NODEBASE_H
#define DSSE_NODEBASE_H

#include "Dsse/Config.h"
#include "Dsse/DataTypes.h"

namespace dsse
{
class Dsse;
class InletBase;
class OutletBase;
class ContainerNode;

class DSSE_EXPORT NodeBase
{
	friend class Dsse;
    //friend class OutletBase;
    friend class SimpleOutlet;

public:
	String name;
	String category;
	String custname; // custom(user defined) name
	bool custnamed;
	bool processed; // inner logic and data exchange complete

	NodeBase(Dsse*, ContainerNode*);
    virtual ~NodeBase();

	virtual bool IsStatic() = 0;
	virtual bool IsContainer() = 0;
	int GetID() { return m_id; }

	virtual void DoLogic() = 0; // logic
	virtual void Update()  = 0; // logic + io

	virtual int GetInletCount() = 0;
	virtual InletBase* GetInlet(String name) = 0;
	virtual InletBase* GetInlet(int index) = 0;
    virtual bool HasConnectedInlets() = 0;

    // TODO Provide in/outlet iterators

	virtual int GetOutletCount() = 0;
	virtual OutletBase* GetOutlet(String name) = 0;
	virtual OutletBase* GetOutlet(int index) = 0;

	void setCustomName(String name);
	String GetName();

protected:
    Dsse* m_engine;
	ContainerNode* m_parent;
	//shared_ptr<ContainerNode> m_parent;
	int m_id;

    virtual NodeBase* CreateInstance(Dsse*, ContainerNode*) = 0;
};

}
#endif // ifndef DSSE_NODEBASE_H
