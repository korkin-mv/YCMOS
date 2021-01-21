#pragma once

#include <stdint.h>
#include <stddef.h>

namespace ycmos
{

template<class T>
struct TypeTraits
{
    typedef size_t SizeType;
    typedef ptrdiff_t DiffType;
};

template<>
struct TypeTraits<char>
{
    typedef uint8_t SizeType;
    typedef int8_t DiffType;
};

}
