
#pragma once
#ifndef DSSE_FLOATOUTLET_H
#define DSSE_FLOATOUTLET_H

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/NodeBase.h"
#include "Dsse/inoutlets/OutletBase.h"
#include "Dsse/inoutlets/FloatInlet.h"

namespace dsse
{
    class DSSE_EXPORT FloatOutlet : public OutletBase
    {
    public:
		//DataType inbuffer;
		
        FloatOutlet(NodeBase node);
        ~FloatOutlet();
        NodeBase getNode();
        void WriteData(float data);
        int connectTo(FloatInlet inlet);
	protected:
		float m_outValue;
    };
}
#endif // ifndef DSSE_FLOATOUTLET_H