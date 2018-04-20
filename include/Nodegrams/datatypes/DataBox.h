
#pragma once
#ifndef NDGM_DT_DATABOX_H
#define NDGM_DT_DATABOX_H

#include "Nodegrams/Config.h"
#include "Nodegrams/DataTypes.h"
#include "Nodegrams/datatypes/DataWriteFunc.h"

namespace Nodegrams
{
class Nodegrams;
class Serializer;
class Deserializer;

namespace Nodes
{
class DataHolder;
}

namespace Data
{

class NDGM_EXPORT DataBox
{
    friend class TypeRegistry;

public:
	DataType GetTypeID() { return m_datatype; }
	virtual bool IsComposite() = 0;
    String GetName() { return m_name; }
    String GetDescription() { return m_descr; }
    String GetModule() { return m_module; }

    void SetHolder(Nodes::DataHolder* holder) { m_holder = holder; }
    void ValueChanged();
    virtual void ValueChangeHandled() {}; // For event types

	virtual String ToString() = 0;
    virtual DataWriteFunc GetConversionFunc(String tname) = 0;

    virtual void Serialize(Serializer& serer)     = 0;
    virtual void Deserialize(Deserializer& derer) = 0;

protected:
    Nodegrams* m_engine;
	DataType m_datatype;
    Nodes::DataHolder* m_holder;

    String m_name;
    String m_descr;
    String m_module;

	DataBox(Nodegrams* engine, String name, String descr, String module);
    virtual ~DataBox();
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_DT_DATABOX_H
