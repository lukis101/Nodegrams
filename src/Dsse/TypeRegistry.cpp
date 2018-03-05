
#include "Dsse/TypeRegistry.h"
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{

TypeRegistry::TypeRegistry(Dsse* engine)
    : m_dtypes(10), m_typeids(10)
{
    m_freeid = 0;
}
TypeRegistry::~TypeRegistry()
{
    for (auto dt : m_dtypes)
        if (dt != nullptr)
            delete dt;
}

// Take ownership and store a "type box" object
DataType TypeRegistry::RegisterDataType(DataBox*&& dtype)
{
    String dtname = dtype->GetName();
    auto idt = m_typeids.find(dtname);
    if (idt == m_typeids.end())
    {
        DataType dtid = m_freeid;
        // find next free slot
        m_freeid = static_cast<DataType>(m_dtypes.size());
        for (int i=dtid+1; i<m_dtypes.size(); i++)
        {
            if (m_dtypes[i] != nullptr)
            {
                m_freeid = i;
                break;
            }
        }
        if (dtid < m_dtypes.size())
            m_dtypes[dtid] = dtype;
        else
            m_dtypes.push_back(dtype);
        m_typeids.emplace(dtname, dtid);
        dtid++;
        dtype->m_datatype = dtid;

        spdlog::get("dsse")->info("TReg.RegisterDataType({} -> {})",
            dtname, dtid);
        return dtid;
    }
    else
    {
        spdlog::get("dsse")->error("TReg.RegisterDataType {} already registered to {}",
            dtname, idt->second);
        assert(dtname == m_dtypes[idt->second]->GetName());
        delete dtype;
	    return 0;
    }
}
void TypeRegistry::InitDataBox(DataBox* dataobj)
{
    spdlog::get("dsse")->info("TReg.RegisterDataType({} -> {})",
        dataobj->GetName(), dataobj->GetTypeID());
}

}
