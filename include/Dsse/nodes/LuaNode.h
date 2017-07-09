
#pragma once
#ifndef DSSE_NODECONTAINER_H
#define DSSE_NODECONTAINER_H


#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/NodeBase.h"

namespace dsse
{
    class NodeContainer
    {
    public:
        virtual ~NodeContainer() = 0;
        virtual NodeBase getNode() = 0;
    };
}
#endif // ifndef DSSE_NODECONTAINER_H