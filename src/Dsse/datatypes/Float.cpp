
#include "Dsse/datatypes/Float.h"
#include "Dsse/datatypes/Double.h"
#include "Dsse/datatypes/Boolean.h"

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
    ValueChanged();
}
float Float::GetValue()
{
    return m_data;
}

String Float::ToString()
{
    return std::to_string(m_data);
}

DataWriteFunc Float::GetConversionFunc(String tname)
{
    if (tname == "Float")        return &FloatToFloat;
    else if (tname == "Double")  return &FloatToDouble;
    else if (tname == "Boolean") return &FloatToBoolean;
    //else if (tname == "Int32")   return &FloatToInt32;
    else return nullptr;
}

void Float::FloatToFloat(DataBox* floatbox1, DataBox* floatbox2)
{
    Float* fbox1 = static_cast<Float*>(floatbox1);
    Float* fbox2 = static_cast<Float*>(floatbox2);
    fbox2->SetValue(fbox1->GetValue());
}
void Float::FloatToDouble(DataBox* floatbox, DataBox* doublebox)
{
    Float* fbox = static_cast<Float*>(floatbox);
    Double* dbox = static_cast<Double*>(doublebox);
    dbox->SetValue(static_cast<double>(fbox->GetValue()));
}
void Float::FloatToBoolean(DataBox* floatbox, DataBox* boolbox)
{
    Float* fbox = static_cast<Float*>(floatbox);
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    bbox->SetValue(fbox->GetValue() >= 0.5f);
}
void Float::FloatToInt32(DataBox* floatbox, DataBox* intbox)
{
    Float* fbox = static_cast<Float*>(floatbox);
    //Int32* ibox = static_cast<Int32*>(intbox);
    //ibox->SetValue(static_cast<int>(dbox->GetValue()));
}

}
