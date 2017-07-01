
#pragma once
#ifndef DSSE_FLOATINLET_H
#define DSSE_FLOATINLET_H

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/NodeBase.h"
#include "Dsse/inoutlets/FloatInlet.h"
#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
    class DSSE_EXPORT FloatInlet : public InletBase
    {
    public:
		//DataType inbuffer;
		
        FloatInlet(NodeBase node);
        ~FloatInlet();
        NodeBase getNode();
        void WriteData(float data);
		float GetValue();
	protected:
		float m_inValue;
    };
}
#endif // ifndef DSSE_FLOATINLET_H