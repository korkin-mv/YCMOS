#pragma once

#include "../../containers/String.hpp"
#include "../Transport.hpp"

namespace ycmos::io::user
{

template<class T>
class VTBase
{
public:
    typedef T CharType;
    typedef typename TypeTraits<CharType>::SizeType CharSizeType;
    typedef Transport<CharType> TransportType;
    typedef containers::StringBase<T> StringType;

public:
    VTBase(TransportType *transport);
    virtual ~VTBase() = default;

    PtResult getc(Pt *pt, CharType &c);
    PtResult putc(Pt *pt, CharType c);

    virtual PtResult gets(Pt *pt, StringType &s) = 0;
    virtual PtResult puts(Pt *pt, const StringType &s) = 0;
    virtual PtResult puts(Pt *pt, const CharType *s) = 0;

    virtual bool inputAviable() const volatile = 0;
    virtual bool outputAviable() const volatile = 0;

protected:
    TransportType *_transport;
};

template<class T>
VTBase<T>::VTBase(TransportType *transport) :
    _transport(transport)
{

}

template<class T>
inline PtResult VTBase<T>::getc(Pt *pt, CharType &c)
{
    return _transport->get(pt, c);
}

template<class T>
inline PtResult VTBase<T>::putc(Pt *pt, CharType c)
{
    return _transport->put(pt, c);
}

};
