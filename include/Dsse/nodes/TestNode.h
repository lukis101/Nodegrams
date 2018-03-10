
#pragma once
#ifndef DSSE_TESTNODE_H
#define DSSE_TESTNODE_H

#include "Dsse/nodes/StaticNode.h"

namespace dsse
{
class SimpleInlet;
class Float;

class DSSE_EXPORT TestNode : public StaticNode
{
public:
    TestNode(Dsse*);
    ~TestNode();

	void DoLogic();
protected:
    Float* din_f;
    SimpleInlet* in_f;
};

}
#endif // ifndef DSSE_TESTNODE_H
