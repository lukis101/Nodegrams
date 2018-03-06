
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
    DataBox* ConvertTo(DataType datatype);

    static void FloatToDouble(DataBox*, DataBox*);
    static void FloatToBoolean(DataBox*, DataBox*);
    static void FloatToInt32(DataBox*, DataBox*);

protected:
    Dsse* m_engine;
	DataType m_datatype;

    float m_data;
};

}
#endif // ifndef DSSE_DT_FLOAT_H
