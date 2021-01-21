#include <ctype.h>

#include <ycmos/utils/Common.hpp>
#include <ycmos/io/user/VT.hpp>

using namespace ycmos;
using namespace ycmos::io::user;

VT::VT(TransportType *transport) :
    Parent(transport), _escSeq(_escSeqData)
{
    PT_SEM_INIT(&_inputSem, 1);
    PT_SEM_INIT(&_outputSem, 1);
}

PtResult VT::gets(Pt *pt, StringType &s)
{
    char itoabuf[6];
    PT_BEGIN(pt);
    PT_SEM_WAIT(pt, &_inputSem);
    _state = ASCII;
    s.clear();
    _cursor = s.begin();
    do
    {
        PT_SPAWN(pt, &_inputPt, getc(&_inputPt, _inputChar));
        switch (_state)
        {
        case ASCII:
            switch(_inputChar)
            {
            case '\e':
                _state = ESC_SEQ;
                _escSeq.clear();
                _escSeq.append(_escSeq.begin(), '\e');
                break;
            case '\r':
                PT_SPAWN(pt, &_inputPt, puts(&_inputPt, newline));
                _state = END;
                break;
            case '\b':
                if (_cursor != s.begin() && s.remove(_cursor-1, 1))
                {
                    --_cursor;
                    PT_SPAWN(pt, &_inputPt, puts(&_inputPt, "\b \b"));
                    if (_cursor < s.end())
                    {
                        PT_SPAWN(pt, &_inputPt, puts(&_inputPt, "\e[K"));
                        goto print_cursor;
                    }
                }
                break;
            default:
                if (isspace(_inputChar))
                {
                    _inputChar = ' ';
                    goto add_char;
                }
                if (isprint(_inputChar) || _inputChar == ' ')
                {
add_char:
                    if (s.append(_cursor, _inputChar))
                    {
                        ++_cursor;
                        PT_SPAWN(pt, &_inputPt, putc(&_inputPt, _inputChar));
                        if (_cursor < s.end())
                        {
print_cursor:
                            PT_SPAWN(pt, &_inputPt, puts(&_inputPt, _cursor));
                            _escSeq.clear();
                            _escSeq.append(_escSeq.begin(), "\e[");
                            utils::itoa(s.length(_cursor), itoabuf);
                            _escSeq.append(_escSeq.end(), itoabuf);
                            _escSeq.append(_escSeq.end(), 'D');
                            _state = ESC_SEQ_END;
                        }
                    }
                }
            }
            break;
        case ESC_SEQ:
            switch (_inputChar)
            {
            case '[':
                _state = CSI_SEQ;
                _escSeq.append(_escSeq.end(), _inputChar);
                break;
            default:
                _state = ASCII;
            }
            break;
        case CSI_SEQ:
            switch (_inputChar)
            {
            case 'D':
                if (_cursor > s.begin())
                {
                    --_cursor;
                    _escSeq.append(_escSeq.end(), 'D');
                    _state = ESC_SEQ_END;
                }
                else
                    _state = ASCII;
                break;
            case 'C':
                if (_cursor < s.end())
                {
                    ++_cursor;
                    _escSeq.append(_escSeq.end(), 'C');
                    _state = ESC_SEQ_END;
                }
                else
                    _state = ASCII;
                break;
            default:
                _state = ASCII;
            }
            break;
        case END:
            break;
        default:
            (void)0;
        }
        if (_state == ESC_SEQ_END)
        {
            PT_SPAWN(pt, &_inputPt, puts(&_inputPt, _escSeq.data()));
            _state = ASCII;
        }
        PT_YIELD(pt);
    }
    while (_state != END);
    PT_SEM_SIGNAL(pt, &_inputSem);
    PT_END(pt);
}

PtResult VT::puts(Pt *pt, const StringType &s)
{
    if (s.type() != StringType::RAM)
        PT_EXIT(pt);
    return puts(pt, s.cdata());
}

PtResult VT::puts(Pt *pt, const CharType *s)
{
    PT_BEGIN(pt);
    PT_SEM_WAIT(pt, &_outputSem);
    _outputPointer = s;
    while (*_outputPointer)
    {
        PT_SPAWN(pt, &_outputPt, putc(&_outputPt, *_outputPointer));
        ++_outputPointer;
    }
    PT_SEM_SIGNAL(pt, &_outputSem);
    PT_END(pt);
}
