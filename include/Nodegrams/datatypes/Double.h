
#pragma once
#ifndef NDGM_DT_DOUBLE_H
#define NDGM_DT_DOUBLE_H

#include "Nodegrams/datatypes/DataBox.h"

namespace Nodegrams
{
class Nodegrams;
namespace Data
{

class NDGM_EXPORT Double : public DataBox
{
public:
	Double(Nodegrams* engine);
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

    void Serialize(Serializer& serer);
    void Deserialize(Deserializer& derer);

protected:
    double m_data;
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_DT_DOUBLE_H
