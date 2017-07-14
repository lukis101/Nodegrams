
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
	NodeBase* getNode(int id);
};

}
#endif // ifndef DSSE_CONTAINERNODE_H