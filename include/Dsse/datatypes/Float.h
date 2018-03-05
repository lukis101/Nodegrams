
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

	String ToString();
    DataBox* ConvertTo(DataType datatype);

protected:
    Dsse* m_engine;
	DataType m_datatype;

    float m_data;
};

}
#endif // ifndef DSSE_DT_FLOAT_H
