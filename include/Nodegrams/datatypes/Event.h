
#pragma once
#ifndef NDGM_DT_EVENT_H
#define NDGM_DT_EVENT_H

#include "Nodegrams/datatypes/DataBox.h"

namespace Nodegrams
{
class Nodegrams;

namespace Data
{

class NDGM_EXPORT Event : public DataBox
{
public:
	Event(Nodegrams* engine);
    ~Event();

	bool IsComposite() { return false; }

    void Fire(int count=1);
    void Handle(int count=1) { m_count -= count; }
    void Clear() { m_count = 0; }
    bool IsPending() { return m_count > 0; }
    int GetCount() { return m_count; }

    void ValueChangeHandled() { Clear(); } // When transfered to connected outlets

	String ToString();
    DataWriteFunc GetConversionFunc(String tname);

    static void EventToEvent(DataBox*, DataBox*);

    void Serialize(Serializer& serer);
    void Deserialize(Deserializer& derer);

protected:
    int m_count;
    int m_totalcount;
};

}
} // namespace Nodegrams
#endif // ifndef NDGM_DT_EVENT_H
