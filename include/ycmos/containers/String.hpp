#pragma once

#include "StringBase.hpp"

namespace ycmos::containers
{

class String : public StringBase<char>
{
public:
    typedef StringBase<char> Parent;
    typedef Parent::SizeType SizeType;

public:
    String(char *buffer, SizeType size);
};

inline String::String(char *buffer, SizeType size) :
    Parent(buffer, size)
{

}

}
