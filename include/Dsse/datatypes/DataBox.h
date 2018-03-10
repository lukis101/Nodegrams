
#pragma once
#ifndef DSSE_DT_DATABOX_H
#define DSSE_DT_DATABOX_H

#include "Dsse/Config.h"
#include "Dsse/DataTypes.h"
#include "Dsse/datatypes/DataWriteFunc.h"

namespace dsse
{
class Dsse;
class DataHolder;

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

    void SetHolder(DataHolder* holder) { m_holder = holder; }
    void ValueChanged();

	virtual String ToString() = 0;
    virtual DataWriteFunc GetConversionFunc(String tname) = 0;

protected:
    Dsse* m_engine;
	DataType m_datatype;
    DataHolder* m_holder;

    String m_name;
    String m_descr;
    String m_module;
};

}
#endif // ifndef DSSE_DT_DATABOX_H
