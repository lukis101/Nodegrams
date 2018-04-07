
#include "Nodegrams/datatypes/Boolean.h"
#include "Nodegrams/datatypes/Float.h"
#include "Nodegrams/datatypes/Double.h"
#include "Nodegrams/datatypes/Int32.h"
#include "Nodegrams/datatypes/Int64.h"

namespace Nodegrams {
namespace Data
{

Boolean::Boolean(Nodegrams* engine)
    : DataBox(engine, "Boolean", "Logical true/false", "Core")
{
    m_data = false;
}
Boolean::~Boolean()
{
}

void Boolean::SetValue(bool value)
{
    m_data = value;
    ValueChanged();
}
bool Boolean::GetValue()
{
    return m_data;
}

String Boolean::ToString()
{
    return std::to_string(m_data);
}

DataWriteFunc Boolean::GetConversionFunc(String tname)
{
    if (tname == "Boolean")      return &BooleanToBoolean;
    else if (tname == "Float")   return &BooleanToFloat;
    else if (tname == "Double")  return &BooleanToDouble;
    else if (tname == "Int32")   return &BooleanToInt32;
    else if (tname == "Int64")   return &BooleanToInt64;
    else return nullptr;
}

void Boolean::BooleanToBoolean(DataBox* boolbox1, DataBox* boolbox2)
{
    Boolean* bbox1 = static_cast<Boolean*>(boolbox1);
    Boolean* bbox2 = static_cast<Boolean*>(boolbox2);
    bbox2->SetValue(bbox1->GetValue());
}
void Boolean::BooleanToFloat(DataBox* boolbox, DataBox* floatbox)
{
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    Float* fbox = static_cast<Float*>(floatbox);
    fbox->SetValue(bbox->GetValue() ? 1.0f : 0.0f);
}
void Boolean::BooleanToDouble(DataBox* boolbox, DataBox* doublebox)
{
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    Double* dbox = static_cast<Double*>(doublebox);
    dbox->SetValue(bbox->GetValue() ? 1.0 : 0.0);
}
void Boolean::BooleanToInt32(DataBox* boolbox, DataBox* intbox)
{
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    Int32* ibox = static_cast<Int32*>(intbox);
    ibox->SetValue(bbox->GetValue() ? 1 : 0);
}
void Boolean::BooleanToInt64(DataBox* boolbox, DataBox* intbox)
{
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    Int64* ibox = static_cast<Int64*>(intbox);
    ibox->SetValue(bbox->GetValue() ? 1 : 0);
}

}
} // namespace Nodegrams
