
#pragma once
#ifndef DSSE_DT_INT32_H
#define DSSE_DT_INT32_H

#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class Dsse;

class DSSE_EXPORT Int32 : public DataBox
{
public:
	Int32(Dsse* engine);
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

protected:
    Dsse* m_engine;
	DataType m_datatype;

    int32_t m_data;
};

}
#endif // ifndef DSSE_DT_INT32_H
