
#pragma once
#ifndef DSSE_OUTLETBASE_H
#define DSSE_OUTLETBASE_H

#include <vector>

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/NodeBase.h"
#include "Dsse/inoutlets/InletBase.h"

namespace dsse
{
    class DSSE_EXPORT OutletBase
    {
    public:
		String name;
		String description;
		//DataPacket outdata;
		std::vector<InletBase*> connections;
		
		OutletBase(NodeBase node);
        virtual ~OutletBase() = 0;
        NodeBase getNode() { return m_node; }
        bool isDataReady() { return m_dataReady; }
		virtual String getValueString() = 0;
		virtual void sendData() = 0; // Send to all connected inlets
		//virtual int connectTo( InletBase inlet )
		//virtual int disconnectFrom( InletBase inlet )
	protected:
        bool m_dataReady;
		NodeBase m_node;
    };
}
#endif // ifndef DSSE_OUTLETBASE_H