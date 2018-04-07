
#pragma once
#ifndef NDGM_DT_BOOLEAN_H
#define NDGM_DT_BOOLEAN_H

#include "Nodegrams/datatypes/DataBox.h"

namespace Nodegrams
{
class Nodegrams;

class NDGM_EXPORT Boolean : public DataBox
{
public:
	Boolean(Nodegrams* engine);
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

} // namespace Nodegrams
#endif // ifndef NDGM_DT_BOOLEAN_H
