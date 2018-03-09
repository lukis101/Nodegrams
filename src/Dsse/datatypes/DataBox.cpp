
#include "Dsse/datatypes/DataBox.h"
//#include "Dsse/DssEngine.h"

namespace dsse
{

DataBox::DataBox(Dsse* engine, String name, String descr, String module)
{
    m_engine = engine;
    m_name = name;
    m_descr = descr;
    m_module = module;
    m_datatype = engine->typereg->GetDataType(name);
}

DataBox::~DataBox()
{
}

}
