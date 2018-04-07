
#pragma once
#ifndef NDGM_DT_FLOAT_H
#define NDGM_DT_FLOAT_H

#include "Nodegrams/datatypes/DataBox.h"

namespace Nodegrams
{
class Nodegrams;

class NDGM_EXPORT Float : public DataBox
{
public:
	Float(Nodegrams* engine);
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

} // namespace Nodegrams
#endif // ifndef NDGM_DT_FLOAT_H
