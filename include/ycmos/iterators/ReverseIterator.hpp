#pragma once

#include "Iterator.hpp"

namespace ycmos::iterators
{

template<class T>
class ReverseIterator : public Iterator<
    typename IteratorTraits<T>::Category,
    typename IteratorTraits<T>::Type,
    typename IteratorTraits<T>::DiffType,
    typename IteratorTraits<T>::Pointer,
    typename IteratorTraits<T>::Reference
>
{
public:
    typedef T IteratorType;
    typedef typename IteratorTraits<T>::DiffType DiffType;
    typedef typename IteratorTraits<T>::Reference Reference;

public:
    ReverseIterator() = default;
    ReverseIterator(const IteratorType &iterator);

    IteratorType base() const;
    Reference operator*() const;

    ReverseIterator &operator++();
    ReverseIterator operator++(int);
    ReverseIterator &operator--();
    ReverseIterator operator--(int);
    ReverseIterator operator+(DiffType i);
    ReverseIterator operator-(DiffType i);
    ReverseIterator &operator+=(DiffType i);
    ReverseIterator &operator-=(DiffType i);

protected:
    IteratorType _iterator;
};

template<class T>
inline ReverseIterator<T>::ReverseIterator(const IteratorType &iterator) :
    _iterator(iterator)
{

}

template<class T>
inline typename ReverseIterator<T>::IteratorType ReverseIterator<T>::base() const
{
    return _iterator;
}

template<class T>
inline typename ReverseIterator<T>::Reference ReverseIterator<T>::operator*() const
{
    IteratorType i(_iterator);
    return *(--i);
}

template<class T>
ReverseIterator<T> &ReverseIterator<T>::operator++()
{
    --_iterator;
    return *this;
}

template<class T>
ReverseIterator<T> ReverseIterator<T>::operator++(int)
{
    ReverseIterator<T> i(*this);
    --_iterator;
    return i;
}

template<class T>
ReverseIterator<T> &ReverseIterator<T>::operator--()
{
    ++_iterator;
    return *this;
}

template<class T>
ReverseIterator<T> ReverseIterator<T>::operator--(int)
{
    ReverseIterator<T> i(*this);
    ++_iterator;
    return i;
}

template<class T>
ReverseIterator<T> ReverseIterator<T>::operator+(DiffType i)
{
    return ReverseIterator<T>(_iterator - i);
}

template<class T>
ReverseIterator<T> ReverseIterator<T>::operator-(DiffType i)
{
    return ReverseIterator<T>(_iterator + i);
}

template<class T>
ReverseIterator<T> &ReverseIterator<T>::operator+=(DiffType i)
{
    _iterator -= i;
    return *this;
}

template<class T>
ReverseIterator<T> &ReverseIterator<T>::operator-=(DiffType i)
{
    _iterator += i;
    return *this;
}

template<class T>
inline bool operator==(const ReverseIterator<T> &a, ReverseIterator<T> &b)
{
    return (a.base() == b.base());
}

template<class T>
inline bool operator!=(const ReverseIterator<T> &a, ReverseIterator<T> &b)
{
    return !(a == b);
}

template<class T>
inline bool operator<(const ReverseIterator<T> &a, ReverseIterator<T> &b)
{
    return (b.base() < a.base());
}

template<class T>
inline bool operator>=(const ReverseIterator<T> &a, ReverseIterator<T> &b)
{
    return !(a < b);
}

template<class T>
inline bool operator>(const ReverseIterator<T> &a, ReverseIterator<T> &b)
{
    return (b < a);
}

template<class T>
inline bool operator<=(const ReverseIterator<T> &a, ReverseIterator<T> &b)
{
    return !(b < a);
}

}
