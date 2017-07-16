
#pragma once
#ifndef DSSE_CONTAINERNODE_H
#define DSSE_CONTAINERNODE_H


#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/DynamicNode.h"

namespace dsse
{
	
class ContainerNode : public DynamicNode
{
public:
	ContainerNode();
	~ContainerNode();
	
	bool IsContainer() { return true };
	NodeBase* getNode(int id);
	void AssignNode(int id);
	//void AssignNode(NodeBase* node);
protected:
	std::vector<NodeBase*> m_nodes;
};

}
#endif // ifndef DSSE_CONTAINERNODE_H