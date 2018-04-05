
#pragma once
#ifndef DSSE_DT_DOUBLE_H
#define DSSE_DT_DOUBLE_H

#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class Dsse;

class DSSE_EXPORT Double : public DataBox
{
public:
	Double(Dsse* engine);
    ~Double();

	bool IsComposite() { return false; }

    void SetValue(double value);
    double GetValue();

	String ToString();
    DataWriteFunc GetConversionFunc(String tname);

    static void DoubleToDouble(DataBox*, DataBox*);
    static void DoubleToFloat(DataBox*, DataBox*);
    static void DoubleToBoolean(DataBox*, DataBox*);
    static void DoubleToInt32(DataBox*, DataBox*);
    static void DoubleToInt64(DataBox*, DataBox*);

protected:
    double m_data;
};

}
#endif // ifndef DSSE_DT_DOUBLE_H
