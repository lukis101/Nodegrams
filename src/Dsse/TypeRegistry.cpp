
#include "Dsse/TypeRegistry.h"
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{

TypeRegistry::TypeRegistry(std::shared_ptr<spdlog::logger> logger)
    : m_typeids(10)
{
    m_logger = logger;
	m_typecount = 0;
	m_maxid = 0;
	m_minfreeid = 0;
	for (int i=0; i < TYPECAP; i++)
        m_dtypes[i] = nullptr;
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
    if (m_minfreeid == TYPECAP)
    {
        m_logger->error("RegisterDataType(): capacity reached");
        delete newdtype;
        return 0;
    }

    DataType newid = m_minfreeid;
    newdtype->m_datatype = newid+1; // External indexing starts at '1'
	m_typecount++;
    // find next free slot
    if (m_minfreeid == (m_maxid+1)) // Pushed to end
    {
        m_maxid = m_minfreeid;
        m_minfreeid++;
    }
    else // middle, find next free slot
    {
        m_minfreeid = m_maxid+1;
        for (int i=newid+1; i<TYPECAP; i++)
        {
            if (m_dtypes[i] == nullptr)
            {
                m_minfreeid = i;
                break;
            }
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
    fconv = newdtype->GetConversionFunc(newdtname); // Same-type transfer
    (*newfmap)[newid] = fconv;
    if (fconv == nullptr)
        assert(false); // Same-type function not provided
    m_conversions[newid] = newfmap;

    // Add to object array
    m_dtypes[newid] = newdtype;
    // Add to name<->id map
    m_typeids.emplace(newdtname, newid);

    return newdtype->m_datatype;
}
void TypeRegistry::DeregisterDataType(DataType dtype)
{
    if ((dtype > 0) && (dtype <= m_maxid))
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

            // Update helper vars
            m_typecount--;
            if (dtype < m_minfreeid)
                m_minfreeid = dtype;
            if (dtype == m_maxid)
                while (m_maxid > 0)
                    if (m_dtypes[--m_maxid] != nullptr)
                        break; // found new end

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
