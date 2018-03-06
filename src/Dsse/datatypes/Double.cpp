
#include "Dsse/datatypes/Double.h"
#include "Dsse/datatypes/Float.h"

namespace dsse
{

Double::Double(Dsse* engine)
    : DataBox(engine, "Double", "64b float", "Core")
{
    m_data = 0.0;
}
Double::~Double()
{
}

void Double::SetValue(double value)
{
    m_data = value;
}
double Double::GetValue()
{
    return m_data;
}

String Double::ToString()
{
    return std::to_string(m_data);
}

DataBox* Double::ConvertTo(DataType datatype)
{
    return nullptr;
}

void Double::DoubleToFloat(DataBox* doublebox, DataBox* floatbox)
{
    Double* dbox = static_cast<Double*>(doublebox);
    Float* fbox = static_cast<Float*>(floatbox);
    fbox->SetValue(static_cast<float>(dbox->GetValue()));
}
void Double::DoubleToBoolean(DataBox* doublebox, DataBox* boolbox)
{
    Double* dbox = static_cast<Double*>(doublebox);
    //Bool* bbox = static_cast<Bool*>(boolbox);
    //bbox->SetValue(dbox->GetValue() >= 1.0f);
}
void Double::DoubleToInt32(DataBox* doublebox, DataBox* intbox)
{
    Double* dbox = static_cast<Double*>(doublebox);
    //Int32* ibox = static_cast<Int32*>(intbox);
    //ibox->SetValue(static_cast<int>(dbox->GetValue()));
}

}
