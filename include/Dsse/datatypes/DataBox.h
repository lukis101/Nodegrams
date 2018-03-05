
#pragma once
#ifndef DSSE_DT_DATABOX_H
#define DSSE_DT_DATABOX_H

#include "Dsse/DssEngine.h"
//#include "Dsse/TypeRegistry.h"

namespace dsse
{
class Dsse;

class DSSE_EXPORT DataBox
{
    friend class TypeRegistry;
public:
	DataBox(Dsse* engine, String name, String descr, String module);
    virtual ~DataBox();

	DataType GetTypeID() { return m_datatype; }
	virtual bool IsComposite() = 0;
    String GetName() { return m_name; }
    String GetDescription() { return m_descr; }
    String GetModule() { return m_module; }

	virtual String ToString() = 0;
    virtual DataBox* ConvertTo(DataType datatype) = 0;

protected:
    Dsse* m_engine;
	DataType m_datatype;

    String m_name = "UnnamedType";
    String m_descr = "";
    String m_module = "Core";
};

}
#endif // ifndef DSSE_DT_DATABOX_H
