
#include "Dsse/datatypes/Float.h"

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

String Float::ToString()
{
    return std::to_string(m_data);
}

DataBox* Float::ConvertTo(DataType datatype)
{
    return nullptr;
}

}
