
#pragma once
#ifndef DSSE_TYPEREGISTRY_H
#define DSSE_TYPEREGISTRY_H

#include "spdlog/spdlog.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include "Dsse/Config.h"
#include "Dsse/DataTypes.h"
#include "Dsse/datatypes/DataWriteFunc.h"

namespace dsse
{
//class DataBox;

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

    // TODO use proper storage model
	const static int TYPECAP = 20;
	DataBox* m_dtypes[TYPECAP];
	int m_typecount;
	DataType m_maxid; // highest registry index
	DataType m_minfreeid; // first(lowest) free index

    std::unordered_map<String, DataType> m_typeids;
    // Type conversion function mappings
    std::unordered_map<DataType, std::unordered_map<DataType, DataWriteFunc>*> m_conversions;
};

}
#endif // ifndef DSSE_TYPEREGISTRY_H
