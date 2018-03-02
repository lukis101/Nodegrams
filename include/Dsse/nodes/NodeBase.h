
#pragma once
#ifndef DSSE_NODEBASE_H
#define DSSE_NODEBASE_H

//#include <memory>

#include "Dsse/DssEngine.h"
#include "Dsse/inoutlets/InletBase.h"
#include "Dsse/inoutlets/OutletBase.h"

namespace dsse
{
class ContainerNode;

class DSSE_EXPORT NodeBase
{
	friend class Dsse;
public:
	String name;
	String category;
	String custname; // custom(user defined) name
	bool custnamed;
	bool processed; // inner logic and data exchange complete
	//shared_ptr<ContainerNode> m_parent;

	NodeBase();
    virtual ~NodeBase();

	virtual bool IsStatic() = 0;
	virtual bool IsContainer() = 0;
	virtual void DoLogic() = 0;
	int GetID() { return m_id; }

	virtual int GetInletCount() = 0;
	virtual InletBase* GetInlet(String name) = 0;
	virtual InletBase* GetInlet(int index) = 0;

	virtual int GetOutletCount() = 0;
	virtual OutletBase* GetOutlet(String name) = 0;
	virtual OutletBase* GetOutlet(int index) = 0;

	void setCustomName(String name);
	String GetName();

protected:
	ContainerNode* m_parent;
	int m_id;
};

}
#endif // ifndef DSSE_NODEBASE_H
