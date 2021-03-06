
#include "Nodegrams/datatypes/Event.h"
#include "Nodegrams/Serializer.h"
#include "Nodegrams/Deserializer.h"

namespace Nodegrams {
namespace Data
{

Event::Event(Nodegrams* engine)
    : DataBox(engine, "Event", "Simple event that adds-up when not handled", "Core")
{
    m_count = 0;
    m_totalcount = 0;
}
Event::~Event()
{
}

void Event::Fire(int count)
{
    m_count += count;
    m_totalcount += count;
    ValueChanged();
}

String Event::ToString()
{
    return std::to_string(m_totalcount);
}

void Event::Serialize(Serializer& serer)
{
    serer.AddInt(m_count);
}
void Event::Deserialize(Deserializer& derer)
{
    m_count = derer.GetInt();
    m_totalcount = m_count;
}

DataWriteFunc Event::GetConversionFunc(String tname)
{
    if (tname == "Event") return &EventToEvent;
    else return nullptr;
}

void Event::EventToEvent(DataBox* eventbox1, DataBox* eventbox2)
{
    Event* ebox1 = static_cast<Event*>(eventbox1);
    Event* ebox2 = static_cast<Event*>(eventbox2);
    ebox2->Fire(ebox1->GetCount());
}

}
} // namespace Nodegrams
