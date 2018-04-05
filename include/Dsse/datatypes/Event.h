
#pragma once
#ifndef DSSE_DT_EVENT_H
#define DSSE_DT_EVENT_H

#include "Dsse/datatypes/DataBox.h"

namespace dsse
{
class Dsse;

class DSSE_EXPORT Event : public DataBox
{
public:
	Event(Dsse* engine);
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

protected:
    int m_count;
    int m_totalcount;
};

}
#endif // ifndef DSSE_DT_EVENT_H
