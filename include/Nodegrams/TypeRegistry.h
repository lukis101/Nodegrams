
#pragma once
#ifndef NDGM_TYPEREGISTRY_H
#define NDGM_TYPEREGISTRY_H

#include "spdlog/spdlog.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include "Nodegrams/Config.h"
#include "Nodegrams/DataTypes.h"
#include "Nodegrams/SparseArray.h"
#include "Nodegrams/datatypes/DataWriteFunc.h"

namespace Nodegrams
{
namespace Data
{
class DataBox;
}
using Data::DataBox;

class NDGM_EXPORT TypeRegistry
{
public:
	TypeRegistry(std::shared_ptr<spdlog::logger> logger);
    ~TypeRegistry();

    String GetName(DataType dtype);
    String GetDescription(DataType dtype);
    String GetModule(DataType dtype);

    DataType RegisterDataType(DataBox*&& dtype);
    bool DeregisterDataType(DataType dtype);
    DataType GetDataType(String name);

    bool WriteSupported(DataBox* from, DataBox* to);
    void WriteData(DataBox* from, DataBox* to);

	const static int TYPECAP = 20;
    SparseArray<DataBox*, TYPECAP> m_dtypes;
protected:
    //Nodegrams m_engine;
	std::shared_ptr<spdlog::logger> m_logger;

    std::unordered_map<String, DataType> m_typeids;

    // Type conversion function mappings
    std::unordered_map<DataType, std::unordered_map<DataType, Data::DataWriteFunc>*> m_conversions;
};

} // namespace Nodegrams
#endif // ifndef NDGM_TYPEREGISTRY_H
