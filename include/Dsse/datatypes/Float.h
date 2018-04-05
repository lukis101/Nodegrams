
#pragma once
#ifndef DSSE_DT_FLOAT_H
#define DSSE_DT_FLOAT_H

#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class Dsse;

class DSSE_EXPORT Float : public DataBox
{
public:
	Float(Dsse* engine);
    ~Float();

	bool IsComposite() { return false; }

    void SetValue(float value);
    float GetValue();

	String ToString();
    DataWriteFunc GetConversionFunc(String tname);

    static void FloatToFloat(DataBox*, DataBox*);
    static void FloatToDouble(DataBox*, DataBox*);
    static void FloatToBoolean(DataBox*, DataBox*);
    static void FloatToInt32(DataBox*, DataBox*);
    static void FloatToInt64(DataBox*, DataBox*);

protected:
    float m_data;
};

}
#endif // ifndef DSSE_DT_FLOAT_H
