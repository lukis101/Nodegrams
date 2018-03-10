
#include "Dsse/TypeRegistry.h"
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{

TypeRegistry::TypeRegistry(std::shared_ptr<spdlog::logger> logger)
    : m_dtypes(10), m_typeids(10)
{
    m_logger = logger;
    m_freeid = 0;
}
TypeRegistry::~TypeRegistry()
{
    for (auto dt : m_dtypes)
        if (dt != nullptr)
            delete dt;
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
        assert(newdtname == m_dtypes[idt->second]->GetName());
        delete newdtype;
	    return 0;
    }

    DataType newid = m_freeid;
    newdtype->m_datatype = newid+1; // External indexing starts at '1'
    // find next free slot
    m_freeid = static_cast<DataType>(m_dtypes.size());
    for (int i=newid+1; i<m_dtypes.size(); i++)
    {
        if (m_dtypes[i] == nullptr)
        {
            m_freeid = i;
            break;
        }
    }
    m_logger->info("RegisterDataType \"{}\" -> {}",
        newdtname, newdtype->m_datatype);

    // Update type conversion function mappings
    auto newfmap = new std::unordered_map<DataType, DataWriteFunc>(m_typeids.size());
    DataWriteFunc fconv;
    for (auto dtype : m_dtypes)
    {
        if (dtype == nullptr)
            continue;
        DataType tid = dtype->GetTypeID()-1;
        String tname = dtype->GetName();
        // Existing -> New
        fconv = dtype->GetConversionFunc(newdtname);
        if (fconv != nullptr)
        {
            (*m_conversions[tid])[newid] = fconv;
            m_logger->info("Adding type map: \"{}\"({}) -> \"{}\"({})",
                tname, tid+1, newdtname, newdtype->m_datatype);
        }
        // New -> Existing
        fconv = newdtype->GetConversionFunc(tname);
        if (fconv != nullptr)
        {
            (*newfmap)[tid] = fconv;
            m_logger->info("Adding type map: \"{}\"({}) -> \"{}\"({})",
                newdtname, newdtype->m_datatype, tname, tid+1);
        }
    }
    fconv = newdtype->GetConversionFunc(newdtname); // Same-type transfer
    (*newfmap)[newid] = fconv;
    if (fconv == nullptr)
        assert(false); // Same-type function not provided
    m_conversions[newid] = newfmap;

    // Push to object vector
    if (newid < m_dtypes.size())
        m_dtypes[newid] = newdtype;
    else
        m_dtypes.push_back(newdtype);
    // Add to name<->id map
    m_typeids.emplace(newdtname, newid);

    return newdtype->m_datatype;
}
void TypeRegistry::DeregisterDataType(DataType dtype)
{
    if ((dtype > 0) && (dtype < m_dtypes.size()))
    {
        dtype--;
        if (m_dtypes[dtype] != nullptr)
        {
            DataBox* box = m_dtypes[dtype];
            m_typeids.erase(m_dtypes[dtype]->GetName());
            m_dtypes[dtype] = nullptr;
            // Clear conversion mappings
            for (auto& funcmap : m_conversions) // Remaining -> Target
                funcmap.second->erase(dtype);
            delete m_conversions[dtype]; // Target -> Remaining
            m_conversions.erase(dtype);
            // Release ID
            if (dtype < m_freeid)
                m_freeid = dtype;
            delete box;
            m_logger->info("DeregisterDataType({})", dtype);
            // TODO make engine re-evaluate connections
        }
    }
}

DataType TypeRegistry::GetDataType(String name)
{
    for (auto& dt : m_dtypes)
        if (dt != nullptr)
            if (dt->GetName() == name)
                return dt->GetTypeID();
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
            m_logger->info("WriteSupported({} -> {}) = true",
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
