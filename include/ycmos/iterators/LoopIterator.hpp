#pragma once

#include "../utils/Common.hpp"
#include "Iterator.hpp"

namespace ycmos::iterators
{

template<class T>
class LoopIterator : public Iterator<
    typename IteratorTraits<T>::Category,
    typename IteratorTraits<T>::Type,
    typename IteratorTraits<T>::DiffType,
    typename IteratorTraits<T>::Pointer,
    typename IteratorTraits<T>::Reference
>
{
public:
    typedef T IteratorType;
    typedef typename IteratorTraits<T>::Reference Reference;
    typedef typename IteratorTraits<T>::DiffType DiffType;

public:
    LoopIterator(const IteratorType &begin, const IteratorType &end);
    LoopIterator(const IteratorType &begin, const IteratorType &end, const IteratorType &value);

    IteratorType base() const;
    Reference operator*() const;

    LoopIterator &operator=(const LoopIterator &) = default;

    LoopIterator &operator++();
    LoopIterator &operator--();
    LoopIterator operator++(int);
    LoopIterator operator--(int);
    LoopIterator operator+(DiffType i);
    LoopIterator operator-(DiffType i);
    LoopIterator &operator+=(DiffType i);
    LoopIterator &operator-=(DiffType i);

protected:
    const T _begin, _end;
    T _value;
};

template<class T>
inline LoopIterator<T>::LoopIterator(const IteratorType &begin, const IteratorType &end) :
    _begin(begin), _end(end), _value(begin)
{

}

template<class T>
inline LoopIterator<T>::LoopIterator(
    const IteratorType &begin,
    const IteratorType &end,
    const IteratorType &value) :
    _begin(begin), _end(end), _value(value)
{

}

template<class T>
inline typename LoopIterator<T>::IteratorType LoopIterator<T>::base() const
{
    return _value;
}

template<class T>
inline typename LoopIterator<T>::Reference LoopIterator<T>::operator*() const
{
    return *_value;
}

template<class T>
LoopIterator<T> &LoopIterator<T>::operator++()
{
    ++_value;
    if (_value >= _end)
        _value = _begin;

    return *this;
}

template<class T>
LoopIterator<T> &LoopIterator<T>::operator--()
{
    if (_value == _begin)
        _value = _end - 1;
    else
        --_value;

    return *this;
}

template<class T>
inline LoopIterator<T> LoopIterator<T>::operator++(int)
{
    LoopIterator<T> tmp(*this);
    ++(*this);
    return tmp;
}

template<class T>
inline LoopIterator<T> LoopIterator<T>::operator--(int)
{
    LoopIterator<T> tmp(*this);
    --(*this);
    return tmp;
}

template<class T>
inline LoopIterator<T> LoopIterator<T>::operator+(DiffType i)
{
    LoopIterator<T> tmp(*this);
    return tmp += i;
}

template<class T>
inline LoopIterator<T> LoopIterator<T>::operator-(DiffType i)
{
    LoopIterator<T> tmp(*this);
    return tmp -= i;
}

template<class T>
LoopIterator<T> &LoopIterator<T>::operator+=(DiffType i)
{
    if (i < 0)
        return (*this)-=utils::abs(i);
    for (;i > 0;--i)
        ++_value;
    return *this;
}

template<class T>
LoopIterator<T> &LoopIterator<T>::operator-=(DiffType i)
{
    if (i < 0)
        return (*this)+=utils::abs(i);
    for (;i > 0;--i)
        --_value;
    return *this;
}

}
