
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{

DataBox::DataBox(Dsse* engine, String name, String descr, String module)
{
    m_engine = engine;
    m_datatype = 0;
    m_name = name;
    m_descr = descr;
    m_module = module;
}

DataBox::~DataBox()
{
}

}
