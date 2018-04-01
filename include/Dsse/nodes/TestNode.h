
#pragma once
#ifndef DSSE_TESTNODE_H
#define DSSE_TESTNODE_H

#include "Dsse/nodes/StaticNode.h"

namespace dsse
{
class SimpleInlet;
class Float;
class Int64;

class DSSE_EXPORT TestNode : public StaticNode
{
public:
    TestNode(Dsse*, ContainerNode*);
    ~TestNode();

	void DoLogic();

protected:
    Float* din_f;
    Int64* din_s64;
    SimpleInlet* in_f;
    SimpleInlet* in_s64;

    NodeBase* CreateInstance(Dsse*, ContainerNode*);
};

}
#endif // ifndef DSSE_TESTNODE_H
