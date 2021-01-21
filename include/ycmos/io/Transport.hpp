#pragma once

#include "../Pt.hpp"

namespace ycmos::io
{

template<class T>
class Transport
{
public:
    typedef T Type;

public:
    virtual ~Transport() = default;

    virtual PtResult get(Pt *pt, T &c) = 0;
    virtual PtResult put(Pt *pt, const T &c) = 0;
};

}
