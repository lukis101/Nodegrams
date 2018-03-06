
#include "Dsse/datatypes/Float.h"
#include "Dsse/datatypes/Double.h"

namespace dsse
{

Float::Float(Dsse* engine)
    : DataBox(engine, "Float", "32b float", "Core")
{
    m_data = 0.0f;
}
Float::~Float()
{
}

void Float::SetValue(float value)
{
    m_data = value;
}
float Float::GetValue()
{
    return m_data;
}

String Float::ToString()
{
    return std::to_string(m_data);
}

DataBox* Float::ConvertTo(DataType datatype)
{
    return nullptr;
}

void Float::FloatToDouble(DataBox* floatbox, DataBox* doublebox)
{
    Float* fbox = static_cast<Float*>(floatbox);
    Double* dbox = static_cast<Double*>(doublebox);
    dbox->SetValue(static_cast<double>(fbox->GetValue()));
}

}
