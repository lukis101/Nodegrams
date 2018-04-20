
#pragma once
#ifndef NDGM_DT_INT64_H
#define NDGM_DT_INT64_H

#include "Nodegrams/datatypes/DataBox.h"

namespace Nodegrams
{
class Nodegrams;

namespace Data
{

class NDGM_EXPORT Int64 : public DataBox
{
public:
	Int64(Nodegrams* engine);
    ~Int64();

	bool IsComposite() { return false; }

    void SetValue(int64_t value);
    int64_t GetValue();

	String ToString();
    DataWriteFunc GetConversionFunc(String tname);

    static void Int64ToInt64(DataBox*, DataBox*);
    static void Int64ToInt32(DataBox*, DataBox*);
    static void Int64ToFloat(DataBox*, DataBox*);
    static void Int64ToDouble(DataBox*, DataBox*);
    static void Int64ToBoolean(DataBox*, DataBox*);

    void Serialize(Serializer& serer);
    void Deserialize(Deserializer& derer);

protected:
    int64_t m_data;
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_DT_INT64_H
