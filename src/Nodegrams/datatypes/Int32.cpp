
#include "Nodegrams/datatypes/Int32.h"
#include "Nodegrams/datatypes/Int64.h"
#include "Nodegrams/datatypes/Double.h"
#include "Nodegrams/datatypes/Float.h"
#include "Nodegrams/datatypes/Boolean.h"

namespace Nodegrams
{

Int32::Int32(Nodegrams* engine)
    : DataBox(engine, "Int32", "Signed 32-bit integer", "Core")
{
    m_data = 0;
}
Int32::~Int32()
{
}

void Int32::SetValue(int32_t value)
{
    m_data = value;
    ValueChanged();
}
int32_t Int32::GetValue()
{
    return m_data;
}

String Int32::ToString()
{
    return std::to_string(m_data);
}

DataWriteFunc Int32::GetConversionFunc(String tname)
{
    if (tname == "Int32")        return &Int32ToInt32;
    else if (tname == "Int64")   return &Int32ToInt64;
    else if (tname == "Double")  return &Int32ToDouble;
    else if (tname == "Float")   return &Int32ToFloat;
    else if (tname == "Boolean") return &Int32ToBoolean;
    else return nullptr;
}

void Int32::Int32ToInt32(DataBox* intbox1, DataBox* intbox2)
{
    Int32* ibox1 = static_cast<Int32*>(intbox1);
    Int32* ibox2 = static_cast<Int32*>(intbox2);
    ibox2->SetValue(ibox1->GetValue());
}
void Int32::Int32ToInt64(DataBox* int32box, DataBox* int64box)
{
    Int32* i32box = static_cast<Int32*>(int32box);
    Int64* i64box = static_cast<Int64*>(int64box);
    i64box->SetValue(static_cast<int64_t>(i32box->GetValue()));
}
void Int32::Int32ToDouble(DataBox* intbox, DataBox* doublebox)
{
    Int32* ibox = static_cast<Int32*>(intbox);
    Double* dbox = static_cast<Double*>(doublebox);
    dbox->SetValue(static_cast<double>(ibox->GetValue()));
}
void Int32::Int32ToFloat(DataBox* intbox, DataBox* floatbox)
{
    Int32* ibox = static_cast<Int32*>(intbox);
    Float* fbox = static_cast<Float*>(floatbox);
    fbox->SetValue(static_cast<float>(ibox->GetValue()));
}
void Int32::Int32ToBoolean(DataBox* intbox, DataBox* boolbox)
{
    Int32* ibox = static_cast<Int32*>(intbox);
    Boolean* bbox = static_cast<Boolean*>(boolbox);
    bbox->SetValue(ibox->GetValue() != 0);
}

} // namespace Nodegrams
