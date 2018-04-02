
#pragma once
#ifndef DSSE_CONTAINERNODE_H
#define DSSE_CONTAINERNODE_H

#include "Dsse/nodes/DynamicNode.h"
#include "Dsse/DssEngine.h"

namespace dsse
{

class DSSE_EXPORT ContainerNode : public DynamicNode
{
public:
    ContainerNode(Dsse*);
	~ContainerNode();

    void DoLogic(void);
	bool IsContainer() { return true; };

	NodeBase* getNode(int id);
	void AssignNode(int id);
	//void AssignNode(NodeBase* node); // TODO

protected:
	std::vector<NodeBase*> m_nodes;

    virtual NodeBase* CreateInstance(Dsse*);
};

}
#endif // ifndef DSSE_CONTAINERNODE_H
