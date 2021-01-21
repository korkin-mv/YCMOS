#pragma once

#include "VTBase.hpp"

namespace ycmos::io::user
{

class VT : public VTBase<char>
{
public:
    typedef char CharType;
    typedef VTBase<CharType> Parent;
    typedef typename Parent::CharSizeType CharSizeType;
    typedef typename Parent::TransportType TransportType;
    typedef typename Parent::StringType StringType;
    static constexpr CharSizeType escSeqMaxSize = 10;
    static constexpr CharType newline[] = "\r\n";

public:
    VT(TransportType *transport);
    virtual ~VT() = default;

    virtual PtResult gets(Pt *pt, StringType &s) override;
    virtual PtResult puts(Pt *pt, const StringType &s) override;
    virtual PtResult puts(Pt *pt, const CharType *s) override;

    virtual bool inputAviable() const volatile override;
    virtual bool outputAviable() const volatile override;

protected:
    enum State
    {
        END,
        ASCII,
        ESC_SEQ,
        CSI_SEQ,
        ESC_SEQ_END
    };

protected:
    containers::Array<CharType, escSeqMaxSize> _escSeqData;
    StringType _escSeq;
    PtSem _inputSem, _outputSem;
    Pt _inputPt, _outputPt;
    StringType::ConstIterator _outputPointer;
    State _state;
    CharType _inputChar;
    StringType::Iterator _cursor;
};

inline bool VT::inputAviable() const volatile
{
    return _inputSem.count > 0;
}

inline bool VT::outputAviable() const volatile
{
    return _outputSem.count > 0;
}

}
