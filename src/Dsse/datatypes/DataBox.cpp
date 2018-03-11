
#include "spdlog/spdlog.h"

#include "Dsse/datatypes/DataBox.h"
#include "Dsse/DssEngine.h"
#include "Dsse/TypeRegistry.h"
#include "Dsse/inoutlets/DataHolder.h"

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

void DataBox::ValueChanged()
{
    if (m_holder != nullptr)
    {
        spdlog::get("dsse.data")->debug("Dbox.ValueChanged @ \"{}\"",
            m_holder->GetFullName());
        m_holder->DataChanged();
    }
}

}
