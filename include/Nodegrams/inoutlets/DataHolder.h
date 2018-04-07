
#pragma once
#ifndef NDGM_DATAHOLDER_H
#define NDGM_DATAHOLDER_H

#include "Nodegrams/Config.h"
#include "Nodegrams/DataTypes.h"
#include "Nodegrams/datatypes/DataBox.h"

namespace Nodegrams
{

class NDGM_EXPORT DataHolder
{
public:
	DataHolder(DataBox* data)
    {
        m_data = data;
        data->SetHolder(this);
    }
	virtual ~DataHolder() {};

	DataBox* GetData() { return m_data; }
	bool HasDataChanged() { return m_dataChanged; }
	void DataChanged() { m_dataChanged = true; }
	void DataChangeHandled() { m_dataChanged = false; m_data->ValueChangeHandled(); }

    String GetDataString() { return m_data->ToString(); }
	virtual String GetFullName() = 0;

protected:
	DataBox* m_data;
	bool m_dataChanged = false;
	//bool m_dataReady;
};

} // namespace Nodegrams
#endif // ifndef NDGM_DATAHOLDER_H
