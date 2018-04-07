
#pragma once
#ifndef NDGM_SPARSEARRAY_H
#define NDGM_SPARSEARRAY_H

//#include <iterator>
#include "Nodegrams/SparseArrayIterator.h"

namespace Nodegrams
{

template<typename arrDataType, int arrCapacity>
class SparseArray
{
    //friend class SparseArrayIterator<arrDataType>;
    friend class SparseArrayIterator<arrDataType, arrCapacity>;
public:
    const int capacity = arrCapacity;
    int count;

    SparseArray()
    {
        count = 0;
        m_minfree = 0;
        m_first = capacity;
        m_last = capacity;
        for (int i=0; i < capacity; ++i)
            m_array[i] = nullptr;
    }
    ~SparseArray() {}

    arrDataType Remove(int index)
    {
        assert(m_array[index] != nullptr);

        arrDataType element = m_array[index];
        m_array[index] = nullptr;
	    // Update helper indices
        if (--count > 0)
        {
            if (index == m_first)
                while (m_first < (capacity-1))
                    if (m_array[++m_first] != nullptr)
                        break; // found new start
            if (index == m_last)
                while (m_last > 0)
                    if (m_array[--m_last] != nullptr)
                        break; // found new end
        }
        else
        {
            // Now empty
            m_first = capacity;
            m_last = capacity;
        }
        if (index < m_minfree)
            m_minfree = index;
        return element;
    }

    arrDataType Get(int index)
    {
        assert((index >= 0) && (index < capacity)); // Bounds
        assert(m_array[index] != nullptr); // Invalid index
        return m_array[index];
    }

    void Set(int index, arrDataType element)
    {
        assert((index >= 0) && (index < capacity)); // Bounds
        assert(m_array[index] == nullptr); // Replacement

        m_array[index] = element;
	    // Update helper indices
        if (++count > 1)
        {
            if (index > m_last) // == covers "first element" case
                m_last = index;
            else if (index < m_first)
                m_first = index;
        }
        else
        {
            // No longer empty
            m_first = index;
            m_last = index;
        }
        if (index == m_minfree)
        {
            // Find next free slot
            ++m_minfree;
            while (m_minfree < capacity)
                if (m_array[m_minfree] == nullptr)
                    break; // found
                else
                    ++m_minfree;
        }
    }
    int Add(arrDataType element)
    {
        int index = m_minfree;
        Set(m_minfree, element);
        return index;
    }

    int GetFreeSlot() { return m_minfree; }

    bool IsSet(int id)
    {
        if ((id > 0) && (id <= m_last))
            return (m_array[id] != nullptr);
        return false;
    }

    typedef SparseArrayIterator<arrDataType, arrCapacity>       iterator;
    typedef SparseArrayIterator<const arrDataType, arrCapacity> const_iterator;

    iterator       begin()  { return iterator(this, m_first); }
    iterator       end()    { return iterator(this, capacity); }
    const_iterator cbegin() { return const_iterator(this, m_first); }
    const_iterator cend()   { return const_iterator(this, capacity); }

protected:
    arrDataType m_array[arrCapacity];
    int m_minfree;
    int m_first;
    int m_last;
};

} // namespace Nodegrams
#endif // ifndef NDGM_SPARSEARRAY_H
