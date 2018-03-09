
#pragma once
#ifndef DSSE_TYPEREGISTRY_H
#define DSSE_TYPEREGISTRY_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "Dsse/DssEngine.h"
//#include "Dsse/Config.h"
//#include "Dsse/DataTypes.h"
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
//class Dsse;
class DataBox;
typedef void (*DataWriteFunc)(DataBox*, DataBox*);

class DSSE_EXPORT TypeRegistry
{
public:
	TypeRegistry(std::shared_ptr<spdlog::logger> logger);
    ~TypeRegistry();

    String GetName(DataType dtype);
    String GetDescription(DataType dtype);
    String GetModule(DataType dtype);

    DataType RegisterDataType(DataBox*&& dtype);
    void DeregisterDataType(DataType dtype);
    DataType GetDataType(String name);

    bool WriteSupported(DataBox* from, DataBox* to);
    void WriteData(DataBox* from, DataBox* to);

protected:
    //Dsse m_engine;
	std::shared_ptr<spdlog::logger> m_logger;
    DataType m_freeid;
    std::vector<DataBox*> m_dtypes;
    std::unordered_map<String, DataType> m_typeids;

    // Type conversion function mappings
    std::unordered_map<DataType, std::unordered_map<DataType, DataWriteFunc>*> m_conversions;
};

}
#endif // ifndef DSSE_TYPEREGISTRY_H
