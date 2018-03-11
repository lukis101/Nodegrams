
#include "Dsse/datatypes/Int64.h"
#include "Dsse/datatypes/Int32.h"
#include "Dsse/datatypes/Double.h"
#include "Dsse/datatypes/Float.h"
#include "Dsse/datatypes/Boolean.h"

namespace dsse
{

Int64::Int64(Dsse* engine)
    : DataBox(engine, "Int64", "Signed 64-bit integer", "Core")
{
    m_data = 0;
}
Int64::~Int64()
{
}

void Int64::SetValue(int64_t value)
{
    m_data = value;
    ValueChanged();
}
int64_t Int64::GetValue()
{
    return m_data;
}

String Int64::ToString()
{
    return std::to_string(m_data);
}

DataWriteFunc Int64::GetConversionFunc(String tname)
{
    if (tname == "Int64")        return &Int64ToInt64;
    else if (tname == "Int32")   return &Int64ToInt32;
    else if (tname == "Double")  return &Int64ToDouble;
    else if (tname == "Float")   return &Int64ToFloat;
    else if (tname == "Boolean") return &Int64ToBoolean;
    else return nullptr;
}

void Int64::Int64ToInt64(DataBox* intbox1, DataBox* intbox2)
{
    Int64* ibox1 = static_cast<Int64*>(intbox1);
    Int64* ibox2 = static_cast<Int64*>(intbox2);
    ibox2->SetValue(ibox1->GetValue());
}
void Int64::Int64ToInt32(DataBox* int64box, DataBox* int32box)
{
    Int64* i64box = static_cast<Int64*>(int64box);
    Int32* i32box = static_cast<Int32*>(int32box);
    // TODO write +/-MAX when overflowing
    i32box->SetValue(static_cast<int32_t>(i64box->GetValue()));
}
void Int64::Int64ToDouble(DataBox* intbox, DataBox* doublebox)
{
    Int64* ibox = static_cast<Int64*>(intbox);
    Double* dbox = static_cast<Double*>(doublebox);
    dbox->SetValue(static_cast<double>(ibox->GetValue()));
}
void Int64::Int64ToFloat(DataBox* intbox, DataBox* floatbox)
{
    Int64* ibox = static_cast<Int64*>(intbox);
    Float* fbox = static_cast<Float*>(floatbox);
    // TODO handle overflow
    fbox->SetValue(static_cast<float>(ibox->GetValue()));
}
void Int64::Int64ToBoolean(DataBox* intbox, DataBox* boolbox)
{
    Int64* ibox = static_cast<Int64*>(intbox);
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    bbox->SetValue(ibox->GetValue() != 0);
}

}
