#pragma once

#include <stddef.h>

#include "../TypeTraits.hpp"

namespace ycmos::iterators
{

struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BiDirectIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BiDirectIteratorTag {};

template<class C, class T, class D = typename TypeTraits<T>::DiffType, class Tp = T*, class Tr = T&>
struct Iterator
{
    typedef C Category;
    typedef T Type;
    typedef D DiffType;
    typedef T *Pointer;
    typedef T &Reference;
};

template<class T>
struct IteratorTraits
{
    typedef typename T::Category Category;
    typedef typename T::Type Type;
    typedef typename T::DiffType DiffType;
    typedef typename T::Pointer Pointer;
    typedef typename T::Reference Reference;
};

template<class T>
struct IteratorTraits<T*>
{
    typedef RandomAccessIteratorTag Category;
    typedef T Type;
    typedef T *Pointer;
    typedef ptrdiff_t DiffType;
    typedef T &Reference;
};

template<class T>
struct IteratorTraits<const T*>
{
    typedef RandomAccessIteratorTag Category;
    typedef T Type;
    typedef ptrdiff_t DiffType;
    typedef const T *Pointer;
    typedef const T &Reference;
};

}
