
#pragma once
#ifndef DSSE_INLETBASE_H
#define DSSE_INLETBASE_H

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/NodeBase.h"
#include "Dsse/inoutlets/OutletBase.h"

namespace dsse
{
    class DSSE_EXPORT InletBase
    {
    public:
		InletBase(NodeBase node);
		String name;
		String description;
		//DataType indata;
		OutletBase* connection;

    public:
        virtual ~InletBase() = 0;
        NodeBase getNode() { return m_node; }
        void setDataReady(bool ready) { m_dataReady = ready; }
        bool dataReady() { return m_dataReady; }
        bool dataChanged() { return m_dataChanged; }
		virtual String getValueString() = 0;
		//virtual void WriteData( DataType data )
		//virtual int disconnect()

    protected:
        bool m_dataReady;
        bool m_dataChanged;
        NodeBase m_node;

    };
}
#endif // ifndef DSSE_INLETBASE_H