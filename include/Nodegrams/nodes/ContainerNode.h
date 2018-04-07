
#pragma once
#ifndef NDGM_CONTAINERNODE_H
#define NDGM_CONTAINERNODE_H

#include "Nodegrams/nodes/DynamicNode.h"
#include "Nodegrams/Nodegrams.h"

namespace Nodegrams
{

class NDGM_EXPORT ContainerNode : public DynamicNode
{
public:
    ContainerNode(Nodegrams*);
	~ContainerNode();

    void DoLogic(void);
	bool IsContainer() { return true; };

	NodeBase* getNode(int id);
	void AssignNode(int id);
	//void AssignNode(NodeBase* node); // TODO

protected:
	std::vector<NodeBase*> m_nodes;

    virtual NodeBase* CreateInstance(Nodegrams*);
};

} // namespace Nodegrams
#endif // ifndef NDGM_CONTAINERNODE_H
