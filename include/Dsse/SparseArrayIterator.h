
#pragma once
#ifndef DSSE_SPARSEARRAYITERATOR_H
#define DSSE_SPARSEARRAYITERATOR_H

#include <iterator>
#include "Dsse/SparseArray.h"

namespace dsse
{

template<typename arrDataType, int arrCapacity>
class SparseArray;

template<typename arrDataType, int arrCapacity>
class SparseArrayIterator : public std::iterator<std::bidirectional_iterator_tag,
                                           arrDataType, ptrdiff_t, arrDataType*, arrDataType&>
{
public:
    SparseArrayIterator(SparseArray<arrDataType, arrCapacity>* sarr, int index)
    {
        m_sarr = sarr;
        m_index = index;
    }
    SparseArrayIterator(const SparseArrayIterator<arrDataType, arrCapacity>& rawIterator) = default;
    ~SparseArrayIterator() {}

    SparseArrayIterator<arrDataType, arrCapacity>& operator=(const SparseArrayIterator<arrDataType, arrCapacity>& rawIterator) = default;

    operator bool() const { return *(m_sarr->Get(m_index)) ? true : false; }

    bool operator==(const SparseArrayIterator<arrDataType, arrCapacity>& rawIterator) const
    {
        return ((m_sarr == rawIterator.m_sarr) && (m_index == rawIterator.m_index));
    }
    bool operator!=(const SparseArrayIterator<arrDataType, arrCapacity>& rawIterator) const
    {
        return ((m_sarr != rawIterator.m_sarr) || (m_index != rawIterator.m_index));
    }

    SparseArrayIterator<arrDataType, arrCapacity>& operator++()
    {
        do { ++m_index; }
        while ((m_index <= m_sarr->capacity) && (m_sarr->m_array[m_index] == nullptr));
        return (*this);
    }
    SparseArrayIterator<arrDataType, arrCapacity>& operator--()
    {
        do { --m_index; }
        while ((m_index > m_sarr->m_first) && (m_sarr->m_array[m_index] == nullptr));
        return (*this);
    }

    SparseArrayIterator<arrDataType, arrCapacity>  operator++(int)
    {
        auto temp(*this);
        ++this;
        return temp;
    }
    SparseArrayIterator<arrDataType, arrCapacity>  operator--(int)
    {
        auto temp(*this);
        --this;
        return temp;
    }

          arrDataType& operator*()        { return m_sarr->m_array[m_index]; }
    const arrDataType& operator*()  const { return m_sarr->m_array[m_index]; }
          arrDataType  operator->()       { return m_sarr->m_array[m_index]; }
    const arrDataType  operator->() const { return m_sarr->m_array[m_index]; }

protected:
    SparseArray<arrDataType, arrCapacity>* m_sarr;
    int m_index;
};

}
#endif // ifndef DSSE_SPARSEARRAYITERATOR_H
