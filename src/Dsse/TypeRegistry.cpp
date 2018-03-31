
#include "Dsse/TypeRegistry.h"
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{

TypeRegistry::TypeRegistry(std::shared_ptr<spdlog::logger> logger)
    : m_typeids(10), m_conversions()
{
    m_logger = logger;
}
TypeRegistry::~TypeRegistry()
{
    for (auto& dtbox : m_dtypes)
        delete dtbox;
    for (auto& funcmap : m_conversions)
        delete funcmap.second;
}

// Take "type box" object for building conversion mappings
DataType TypeRegistry::RegisterDataType(DataBox*&& newdtype)
{
    String newdtname = newdtype->GetName();
    auto idt = m_typeids.find(newdtname);
    if (idt != m_typeids.end())
    {
        m_logger->error("RegisterDataType({}) already registered to {}",
            newdtname, idt->second);
        assert(newdtname == m_dtypes.Get(idt->second)->GetName());
        delete newdtype;
	    return 0;
    }
    if (m_dtypes.count == m_dtypes.capacity)
    {
        m_logger->error("RegisterDataType({}): capacity reached", newdtname);
        delete newdtype;
        return 0;
    }

    DataType newid = m_dtypes.Add(newdtype);
    newdtype->m_datatype = newid+1; // External indexing starts at '1'
    m_logger->info("RegisterDataType \"{}\" -> {}",
        newdtname, newdtype->m_datatype);

    // Update type conversion function mappings
    auto newfmap = new std::unordered_map<DataType, DataWriteFunc>(m_typeids.size());
    for (auto& dtype : m_dtypes)
    {
        if (dtype == newdtype)
            continue;

        DataType tid = dtype->GetTypeID()-1;
        String tname = dtype->GetName();
        // Existing -> New
        DataWriteFunc fconv = dtype->GetConversionFunc(newdtname);
        if (fconv != nullptr)
        {
            auto tmapp = m_conversions[tid];
            (*tmapp)[newid] = fconv;
            m_logger->debug("Adding type map: \"{}\"({}) -> \"{}\"({})",
                tname, tid+1, newdtname, newdtype->m_datatype);
        }
        // New -> Existing
        fconv = newdtype->GetConversionFunc(tname);
        if (fconv != nullptr)
        {
            (*newfmap)[tid] = fconv;
            m_logger->debug("Adding type map: \"{}\"({}) -> \"{}\"({})",
                newdtname, newdtype->m_datatype, tname, tid+1);
        }
    }
    DataWriteFunc fconv = newdtype->GetConversionFunc(newdtname); // Same-type transfer
    (*newfmap)[newid] = fconv;
    if (fconv == nullptr)
        assert(false); // Same-type function not provided
    m_conversions[newid] = newfmap;

    // Add to name<->id map
    m_typeids.emplace(newdtname, newid);

    return newdtype->m_datatype;
}
void TypeRegistry::DeregisterDataType(DataType dtype)
{
    if (m_dtypes.IsSet(dtype-1))
    {
        DataBox* box = m_dtypes.Remove(dtype-1);
        // Clear conversion mappings
        for (auto& funcmap : m_conversions) // Remaining -> Target
            funcmap.second->erase(dtype);
        delete m_conversions[dtype]; // Target -> Remaining
        m_conversions.erase(dtype);
        delete box;

        m_logger->info("Deregistered data type {}", dtype);
        // TODO make engine re-evaluate connections
    }
    else
        m_logger->info("Attempt to deregister ivalid data type {}",
            dtype);
}

DataType TypeRegistry::GetDataType(String name)
{
    for (auto& dt : m_dtypes)
    {
        if (dt->GetName() == name)
            return dt->GetTypeID();
    }
    return 0; // Not registered yet
}

bool TypeRegistry::WriteSupported(DataBox* from, DataBox* to)
{
    auto it1 = m_conversions.find(from->GetTypeID()-1);
    if (it1 != m_conversions.end()) // type is registered
    {
        auto mp = it1->second;
        auto it2 = mp->find(to->GetTypeID()-1);
        if (it2 != mp->end()) // conversion supported
        {
            m_logger->debug("WriteSupported({} -> {}) = true",
                from->GetTypeID(), to->GetTypeID());
            return true;
        }
    }
    m_logger->info("WriteSupported({} -> {}) = false",
        from->GetTypeID(), to->GetTypeID());
    return false;
}

void TypeRegistry::WriteData(DataBox* from, DataBox* to)
{
    // TODO check ids
    DataWriteFunc pwritefunc = (*m_conversions[from->GetTypeID()-1])[to->GetTypeID()-1];
    pwritefunc(from, to);
}

}
