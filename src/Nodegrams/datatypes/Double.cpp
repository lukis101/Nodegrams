
#include "Nodegrams/datatypes/Double.h"
#include "Nodegrams/datatypes/Float.h"
#include "Nodegrams/datatypes/Boolean.h"
#include "Nodegrams/datatypes/Int32.h"
#include "Nodegrams/datatypes/Int64.h"

namespace Nodegrams
{

Double::Double(Nodegrams* engine)
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
    ValueChanged();
}
double Double::GetValue()
{
    return m_data;
}

String Double::ToString()
{
    return std::to_string(m_data);
}

DataWriteFunc Double::GetConversionFunc(String tname)
{
    if (tname == "Double")       return &DoubleToDouble;
    else if (tname == "Float")   return &DoubleToFloat;
    else if (tname == "Boolean") return &DoubleToBoolean;
    else if (tname == "Int32")   return &DoubleToInt32;
    else return nullptr;
}

void Double::DoubleToDouble(DataBox* doublebox1, DataBox* doublebox2)
{
    Double* dbox1 = static_cast<Double*>(doublebox1);
    Double* dbox2 = static_cast<Double*>(doublebox2);
    dbox2->SetValue(dbox1->GetValue());
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
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    bbox->SetValue(dbox->GetValue() >= 0.5); // TODO check negative side?
}
void Double::DoubleToInt32(DataBox* doublebox, DataBox* intbox)
{
    Double* dbox = static_cast<Double*>(doublebox);
    Int32* ibox = static_cast<Int32*>(intbox);
    ibox->SetValue(static_cast<int32_t>(dbox->GetValue()));
}
void Double::DoubleToInt64(DataBox* doublebox, DataBox* intbox)
{
    Double* dbox = static_cast<Double*>(doublebox);
    Int64* ibox = static_cast<Int64*>(intbox);
    ibox->SetValue(static_cast<int64_t>(dbox->GetValue()));
}

} // namespace Nodegrams
