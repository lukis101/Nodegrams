
#pragma once
#ifndef DSSE_DATAHOLDER_H
#define DSSE_DATAHOLDER_H

#include "Dsse/Config.h"
#include "Dsse/DataTypes.h"
#include "Dsse/datatypes/DataBox.h"

namespace dsse
{

class DSSE_EXPORT DataHolder
{
public:
	DataHolder(DataBox* data) { m_data = data; }
	virtual ~DataHolder() {};

	DataBox* GetData() { return m_data; }
	bool HasDataChanged() { return m_dataChanged; }
	void DataChanged() { m_dataChanged = true; }
	void DataChangeHandled() { m_dataChanged = false; }
	//virtual void ReceiveData(DataBox* data) = 0;
    String GetDataString() { return m_data->ToString(); }

protected:
	DataBox* m_data;
	bool m_dataChanged = false;
	//bool m_dataReady;
};

}
#endif // ifndef DSSE_DATAHOLDER_H
