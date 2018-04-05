
#pragma once
#ifndef DSSE_DT_BOOLEAN_H
#define DSSE_DT_BOOLEAN_H

#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class Dsse;

class DSSE_EXPORT Boolean : public DataBox
{
public:
	Boolean(Dsse* engine);
    ~Boolean();

	bool IsComposite() { return false; }

    void SetValue(bool value);
    bool GetValue();

	String ToString();
    DataWriteFunc GetConversionFunc(String tname);

    static void BooleanToBoolean(DataBox*, DataBox*);
    static void BooleanToFloat(DataBox*, DataBox*);
    static void BooleanToDouble(DataBox*, DataBox*);
    static void BooleanToInt32(DataBox*, DataBox*);
    static void BooleanToInt64(DataBox*, DataBox*);

protected:
    bool m_data;
};

}
#endif // ifndef DSSE_DT_BOOLEAN_H
