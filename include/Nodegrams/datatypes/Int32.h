
#pragma once
#ifndef NDGM_DT_INT32_H
#define NDGM_DT_INT32_H

#include "Nodegrams/datatypes/DataBox.h"

namespace Nodegrams
{
class Nodegrams;

namespace Data
{

class NDGM_EXPORT Int32 : public DataBox
{
public:
	Int32(Nodegrams* engine);
    ~Int32();

	bool IsComposite() { return false; }

    void SetValue(int32_t value);
    int32_t GetValue();

	String ToString();
    DataWriteFunc GetConversionFunc(String tname);

    static void Int32ToInt32(DataBox*, DataBox*);
    static void Int32ToInt64(DataBox*, DataBox*);
    static void Int32ToFloat(DataBox*, DataBox*);
    static void Int32ToDouble(DataBox*, DataBox*);
    static void Int32ToBoolean(DataBox*, DataBox*);

    void Serialize(Serializer& serer);
    void Deserialize(Deserializer& derer);

protected:
    int32_t m_data;
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_DT_INT32_H
