#pragma once

#include <stddef.h>

#include "../TypeTraits.hpp"

namespace ycmos::containers
{

template<class T, typename TypeTraits<T>::SizeType n>
class Array
{
public:
    typedef T Type;
    typedef Type *Iterator;
    typedef const Type *ConstIterator;
    typedef typename TypeTraits<T>::SizeType SizeType;
    static constexpr SizeType size = n;

public:
    T *data();
    T *data(const Iterator &i);

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    T &operator[](SizeType i);

    T *find(const T &value);
    T *find(bool (*func)(const T &));

protected:
    T _data[n];
};

template<class T, typename TypeTraits<T>::SizeType n>
inline T *Array<T, n>::data()
{
    return _data;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline T *Array<T, n>::data(const Iterator &i)
{
    return i;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline typename Array<T, n>::Iterator Array<T, n>::begin()
{
    return Iterator(_data);
}

template<class T, typename TypeTraits<T>::SizeType n>
inline typename Array<T, n>::Iterator Array<T, n>::end()
{
    return Iterator(_data + n);
}

template<class T, typename TypeTraits<T>::SizeType n>
inline typename Array<T, n>::ConstIterator Array<T, n>::cbegin() const
{
    return ConstIterator(_data);
}

template<class T, typename TypeTraits<T>::SizeType n>
inline typename Array<T, n>::ConstIterator Array<T, n>::cend() const
{
    return ConstIterator(_data + n);
}

template<class T, typename TypeTraits<T>::SizeType n>
inline T &Array<T, n>::operator[](SizeType i)
{
    return _data[i];
}

template<class T, typename TypeTraits<T>::SizeType n>
inline T *Array<T, n>::find(const T &value)
{
    T *p;
    for (p = _data; p < _data + n; p++)
        if (*p == value)
            return p;
    return NULL;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline T *Array<T, n>::find(bool (*func)(const T &))
{
    T *p;
    for (p = _data; p < _data + n; p++)
        if (func(*p))
            return p;
    return NULL;
}

}
