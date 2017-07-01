
#pragma once
#ifndef DSSE_NODEBASE_H
#define DSSE_NODEBASE_H

#include <memory>

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/NodeContainer.h"

namespace dsse
{
    class DSSE_EXPORT NodeBase
    {
    public:
        String name;
        String classname;
        String category;
    shared_ptr<NodeContainer> parent;
    //protected:
    };
}
#endif // ifndef DSSE_NODEBASE_H