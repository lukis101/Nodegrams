
#pragma once
#ifndef DSSE_TESTNODE_H
#define DSSE_TESTNODE_H

#include "Dsse/nodes/StaticNode.h"

namespace dsse
{
class SinglewayInlet;
class Float;
class Int64;

class DSSE_EXPORT TestNode : public StaticNode
{
public:
    TestNode(Dsse*);
    ~TestNode();

	void DoLogic();

protected:
    Float* din_f;
    Int64* din_s64;
    SinglewayInlet* in_f;
    SinglewayInlet* in_s64;

    NodeBase* CreateInstance(Dsse*);
};

}
#endif // ifndef DSSE_TESTNODE_H
