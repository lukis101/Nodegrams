
#pragma once
#ifndef DSSE_DT_INT64_H
#define DSSE_DT_INT64_H

#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class Dsse;

class DSSE_EXPORT Int64 : public DataBox
{
public:
	Int64(Dsse* engine);
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

protected:
    int64_t m_data;
};

}
#endif // ifndef DSSE_DT_INT64_H
