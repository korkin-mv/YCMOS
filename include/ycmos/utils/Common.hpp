#pragma once

#include "../TypeTraits.hpp"

namespace ycmos::utils
{

template<class T>
inline constexpr T abs(T x)
{
    return x >= 0 ? x : -x;
}

template<class C>
void reverse(const C *S)
{

}

namespace _private
{

template<class N, class C>
C *utoa(N n, C *s)
{
    if (n >= 10)
        s = utoa(n/10, s);
    *s = '0' + (n % 10);
    return ++s;
}

}

template<class N, class C>
C *itoa(N n, C *s)
{
    if (n < 0)
    {
        *(s++) = '-';
        n = -n;
    }
    return &(*(_private::utoa(n, s)) = '\0');
}

template<class T, typename... H>
constexpr T bitmask(H... bits)
{
    return (... | (1 << bits));
}

template<uint8_t shift, class T>
constexpr uint8_t byte(T value)
{
    return (value >> (8*shift)) & 0xFF;
}

}
