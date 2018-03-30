
#pragma once
#ifndef DSSE_SPARSEARRAYITERATOR_H
#define DSSE_SPARSEARRAYITERATOR_H

#include <iterator>

namespace dsse
{

template<typename arrDataType>
class SparseArrayIterator : public std::iterator<std::random_access_iterator_tag,
                                           arrDataType, ptrdiff_t, arrDataType*, arrDataType&>
{
public:
    SparseArrayIterator(arrDataType* ptr, arrDataType* last)
    {
        m_ptr = ptr;
        m_last = last;
    }
    SparseArrayIterator(const SparseArrayIterator<arrDataType>& rawIterator) = default;
    ~SparseArrayIterator() {}

    SparseArrayIterator<arrDataType>& operator=(const SparseArrayIterator<arrDataType>& rawIterator) = default;
    SparseArrayIterator<arrDataType>& operator=(arrDataType* ptr) { m_ptr = ptr; return (*this); }

    operator bool() const { return (m_ptr) ? true : false; }

    bool operator==(const SparseArrayIterator<arrDataType>& rawIterator) const
    {
        return (m_ptr == rawIterator.getConstPtr());
    }
    bool operator!=(const SparseArrayIterator<arrDataType>& rawIterator) const
    {
        return (m_ptr != rawIterator.getConstPtr());
    }

    /*SparseArrayIterator<arrDataType>& operator+=(const ptrdiff_t& movement)
    {
        m_ptr += movement;
        return (*this);
    }
    SparseArrayIterator<arrDataType>& operator-=(const ptrdiff_t& movement)
    {
        m_ptr -= movement;
        return (*this);
    }*/
    SparseArrayIterator<arrDataType>& operator++()
    {
        do { ++m_ptr; }
        while((m_ptr < m_last) && (m_ptr != nullptr));
        return (*this);
    }
    SparseArrayIterator<arrDataType>& operator--()
    {
        do { --m_ptr; }
        while((m_ptr < m_last) && (m_ptr != nullptr));
        return (*this);
    }

    SparseArrayIterator<arrDataType>  operator++(int)
    {
        auto temp(*this);
        ++m_ptr;
        return temp;
    }
    SparseArrayIterator<arrDataType>  operator--(int)
    {
        auto temp(*this);
        --m_ptr;
        return temp;
    }
    SparseArrayIterator<arrDataType>  operator+(const ptrdiff_t& movement)
    {
        auto oldPtr = m_ptr;
        m_ptr+=movement;
        auto temp(*this);
        m_ptr = oldPtr;
        return temp;
    }
    SparseArrayIterator<arrDataType>  operator-(const ptrdiff_t& movement)
    {
        auto oldPtr = m_ptr;
        m_ptr-=movement;
        auto temp(*this);
        m_ptr = oldPtr;
        return temp;
    }

    ptrdiff_t                        operator-(const SparseArrayIterator<arrDataType>& rawIterator)
    {
        return std::distance(rawIterator.getPtr(), this->getPtr());
    }

    arrDataType&        operator*()         { return *m_ptr; }
    const arrDataType&  operator*() const   { return *m_ptr; }
    arrDataType*        operator->()        { return m_ptr; }

    arrDataType*        getPtr()      const { return m_ptr; }
    const arrDataType*  getConstPtr() const { return m_ptr; }

protected:
    arrDataType* m_ptr;
    arrDataType* m_last;
};

}
#endif // ifndef DSSE_SPARSEARRAYITERATOR_H
