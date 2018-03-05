
#pragma once
#ifndef DSSE_TYPEREGISTRY_H
#define DSSE_TYPEREGISTRY_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "Dsse/DssEngine.h"
//#include "Dsse/Config.h"
//#include "Dsse/DataTypes.h"
//#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class Dsse;
class DataBox;

class DSSE_EXPORT TypeRegistry
{
public:
	TypeRegistry(Dsse* engine);
    ~TypeRegistry();

    String GetName(DataType dtype);
    String GetDescription(DataType dtype);
    String GetModule(DataType dtype);

    DataType RegisterDataType(DataBox*&& dtype);
    void InitDataBox(DataBox* data);

    //DataBox* ConvertTo(DataBox* source, DataType target);

protected:
    //Dsse m_engine;
    DataType m_freeid;
    std::vector<DataBox*> m_dtypes;
    std::unordered_map<String, DataType> m_typeids;
};

}
#endif // ifndef DSSE_TYPEREGISTRY_H
