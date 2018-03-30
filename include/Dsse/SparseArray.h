
#pragma once
#ifndef DSSE_SPARSEARRAY_H
#define DSSE_SPARSEARRAY_H

//#include <iterator>
#include "Dsse/SparseArrayIterator.h"

namespace dsse
{

template<typename arrDataType, int arrCapacity>
class SparseArray
{
public:
    const int capacity = arrCapacity;
    int count;

    SparseArray()
    {
        count = 0;
        m_minfree = 0;
        m_last = 0;
        for (int i=0; i < capacity; i++)
            m_array[i] = nullptr;
    }
    ~SparseArray() {}

    arrDataType* Remove(int index)
    {
        assert(m_array[index] != nullptr);

        arrDataType* element = m_array[index];
        m_array[index] = nullptr;
        --count;
        if (index < m_minfree)
            m_minfree = index;
        if (index == m_last)
            while (m_last > 0)
                if (m_array[--m_last] != nullptr)
                    break; // found new end
        return element;
    }
    arrDataType* Get(int id) { return m_array[id]; }
    void Set(int index, arrDataType* element)
    {
        assert((index >= 0) && (index < arrCapacity)); // Bounds
        assert(m_array[index] == nullptr); // Replacement

        m_array[index] = element;
        ++count;
	    // Update helper indices
        if (index == m_minfree)
        {
            if (m_minfree == (m_last+1)) // Placed at end
            {
                m_minfree++;
            }
            else // middle, find next free slot
            {
                m_minfree = m_last+1;
                for (int i=index+1; i<arrCapacity; i++)
                {
                    if (m_array[i-1] == nullptr)
                    {
                        m_minfree = i;
                        break;
                    }
                }
            }
        }
        if (index >= m_last) // == covers "first element" case
        {
            m_last = index;
        }
    }
    int Add(arrDataType* element)
    {
        int index = m_minfree;
        Set(m_minfree, element);
        return index;
    }

    bool IsSet(int id)
    {
        if ((id > 0) && (id <= m_last))
            return (m_array[id] != nullptr);
        return false;
    }

    typedef SparseArrayIterator<arrDataType>       iterator;
    typedef SparseArrayIterator<const arrDataType> const_iterator;

    iterator       begin()  { return iterator(m_array[0], m_array[arrCapacity]); }
    iterator       end()    { return iterator(m_array[m_last], m_array[arrCapacity]); }
    const_iterator cbegin() { return const_iterator(m_array[0], m_array[arrCapacity]); }
    const_iterator cend()   { return const_iterator(m_array[m_last], m_array[arrCapacity]); }

protected:
    arrDataType* m_array[arrCapacity];
    int m_minfree;
    int m_last;
};

}
#endif // ifndef DSSE_SPARSEARRAY_H
