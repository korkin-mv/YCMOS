#pragma once

#include "Array.hpp"

namespace ycmos::containers
{

template<class T>
class StringBase
{
public:
    typedef T CharType;
    typedef CharType *Iterator;
    typedef const CharType *ConstIterator;
    typedef typename TypeTraits<T>::SizeType SizeType;
    enum StorageType : uint8_t
    {
        RAM, Flash, EEEPROM, None
    };

public:
    StringBase();
    StringBase(CharType *buffer, SizeType size, StorageType type = RAM);

    template<SizeType n>
    StringBase(Array<CharType, n> &array);

    CharType *data();
    const CharType *cdata() const;

    Iterator begin();
    Iterator end();
    Iterator max();

    StorageType type() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;
    ConstIterator cmax() const;

    SizeType length() const;
    SizeType length(const Iterator &i) const;
    static SizeType clength(const CharType *s);
    SizeType maxLength() const;

    bool empty() const;
    bool full() const;

    void clear();

    bool append(Iterator pos, CharType c);
    bool append(Iterator pos, const CharType *c);
    bool remove(Iterator pos, SizeType count);

protected:
    const Iterator _begin, _end;
    Iterator _last;
    StorageType _type;
};

template<class T>
StringBase<T>::StringBase() :
    _begin(NULL), _end(NULL), _last(NULL),
    _type(None)
{

}

template<class T>
StringBase<T>::StringBase(CharType *buffer, SizeType size, StorageType type) :
    _begin(buffer), _end(buffer + size), _last(_begin),
    _type(type)
{

}

template<class T>
template<typename StringBase<T>::SizeType n>
StringBase<T>::StringBase(Array<CharType, n> &array) :
    _begin(array.begin()), _end(array.end()),
    _last(_begin)
{

}

template<class T>
inline typename StringBase<T>::CharType *StringBase<T>::data()
{
    return _begin;
}

template<class T>
inline const typename StringBase<T>::CharType *StringBase<T>::cdata() const
{
    return _begin;
}

template<class T>
inline typename StringBase<T>::Iterator StringBase<T>::begin()
{
    return _begin;
}

template<class T>
inline typename StringBase<T>::Iterator StringBase<T>::end()
{
    return _last;
}

template<class T>
inline typename StringBase<T>::Iterator StringBase<T>::max()
{
    return _end;
}

template<class T>
inline typename StringBase<T>::ConstIterator StringBase<T>::cbegin() const
{
    return _begin;
}

template<class T>
inline typename StringBase<T>::ConstIterator StringBase<T>::cend() const
{
    return _last;
}

template<class T>
inline typename StringBase<T>::ConstIterator StringBase<T>::cmax() const
{
    return _end;
}

template<class T>
inline typename StringBase<T>::StorageType StringBase<T>::type() const
{
    return _type;
}

template<class T>
inline typename StringBase<T>::SizeType StringBase<T>::length() const
{
    return static_cast<SizeType>(_last - _begin);
}

template<class T>
inline typename StringBase<T>::SizeType StringBase<T>::length(const Iterator &i) const
{
    return static_cast<SizeType>(_last - i);
}

template<class T>
typename StringBase<T>::SizeType StringBase<T>::clength(const CharType *s)
{
    SizeType i;
    for (i = 0; *s; ++i, ++s);
    return i;
}

template<class T>
inline typename StringBase<T>::SizeType StringBase<T>::maxLength() const
{
    return static_cast<SizeType>(_end - _begin);
}

template<class T>
inline bool StringBase<T>::empty() const
{
    return _last <= _begin;
}

template<class T>
inline bool StringBase<T>::full() const
{
    return _last + 1 >= _end;
}

template<class T>
void StringBase<T>::clear()
{
    if (_type != RAM)
        return;
    _last = _begin;
    *_last = '\0';
}

template<class T>
bool StringBase<T>::append(Iterator pos, CharType c)
{
    Iterator j;
    if (full() || _type != RAM)
        return false;
    for (j = _last; j > pos; --j)
        *j = *(j-1);
    *(++_last) = '\0';
    *pos = c;
    return true;
}

template<class T>
bool StringBase<T>::append(Iterator pos, const CharType *s)
{
    Iterator j;
    const SizeType n = clength(s);

    if (length() + n > maxLength() || _type != RAM)
        return false;
    for (j = pos; j < pos + n; ++j)
        *(j+n) = *j;
    *(_last += n) = '\0';
    while (*s)
        *(pos++) = *(s++);
    return true;
}

template<class T>
bool StringBase<T>::remove(Iterator pos, SizeType count)
{
    Iterator j;
    if (count > length() || _type != RAM)
        return false;
    for (j = pos; j < _last; ++j)
        *j = *(j+count);
    *(_last -= count) = '\0';
    return true;
}

}
