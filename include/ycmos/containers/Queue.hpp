#pragma once

#include "Array.hpp"
#include "../iterators/LoopIterator.hpp"

namespace ycmos::containers
{

template<class T, typename TypeTraits<T>::SizeType n>
class Queue
{
public:
    static_assert(n > 0);
    typedef T Type;
    typedef typename TypeTraits<T>::SizeType SizeType;
    static constexpr SizeType size = n;

public:
    typedef Array<T, n> DataType;
    typedef iterators::LoopIterator<typename DataType::Iterator> Iterator;

public:
    Queue();
    Queue(const Queue &) = delete;
    Queue(Queue &&) = delete;

    bool push(const Type &value);
    bool pop(Type &value);

    Iterator front() const;
    Iterator rear() const;

    SizeType count() const;
    bool empty() const;
    bool full() const;

protected:
    DataType _data;
    Iterator _front, _rear;
    volatile SizeType _count;
};

template<class T, typename TypeTraits<T>::SizeType n>
Queue<T, n>::Queue() :
    _data(),
    _front(_data.begin(), _data.end()),
    _rear(_data.begin(), _data.end()),
    _count(0)
{

}

template<class T, typename TypeTraits<T>::SizeType n>
bool Queue<T, n>::push(const Type &value)
{
    if (full())
        return false;
    ++_count;
    *_rear = value;
    ++_rear;

    return true;
}

template<class T, typename TypeTraits<T>::SizeType n>
bool Queue<T, n>::pop(Type &value)
{
    if (empty())
        return false;
    --_count;
    value = *_front;
    ++_front;

    return true;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline typename Queue<T, n>::Iterator Queue<T, n>::front() const
{
    return _front;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline typename Queue<T, n>::Iterator Queue<T, n>::rear() const
{
    return _rear;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline bool Queue<T, n>::empty() const
{
    return _count <= 0;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline bool Queue<T, n>::full() const
{
    return _count >= n;
}

template<class T, typename TypeTraits<T>::SizeType n>
inline typename Queue<T, n>::SizeType Queue<T, n>::count() const
{
    return _count;
}

}
