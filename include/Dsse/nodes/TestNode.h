
#pragma once
#ifndef DSSE_TESTNODE_H
#define DSSE_TESTNODE_H

#include <memory>

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/nodes/NodeContainer.h"
#include "Dsse/nodes/NodeBase.h"

namespace dsse
{
	
class DSSE_EXPORT TestNode : public StaticNode
{
public:
    TestNode();
    ~TestNode();
//protected:
};

}
#endif // ifndef DSSE_TESTNODE_H