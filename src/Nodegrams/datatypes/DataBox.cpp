
#include "spdlog/spdlog.h"

#include "Nodegrams/datatypes/DataBox.h"
#include "Nodegrams/Nodegrams.h"
#include "Nodegrams/TypeRegistry.h"
#include "Nodegrams/inoutlets/DataHolder.h"

namespace Nodegrams {
namespace Data
{

DataBox::DataBox(Nodegrams* engine, String name, String descr, String module)
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
        spdlog::get("Ndgm.data")->debug("Dbox.ValueChanged @ \"{}\"",
            m_holder->GetFullName());
        m_holder->DataChanged();
    }
}

}
} // namespace Nodegrams
