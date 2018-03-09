
#pragma once
#ifndef DSSE_TESTNODE_H
#define DSSE_TESTNODE_H

#include "Dsse/nodes/StaticNode.h"
#include "Dsse/inoutlets/SimpleInlet.h"
#include "Dsse/datatypes/Float.h"

namespace dsse
{

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
