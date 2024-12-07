#include "DynamicQueue.h"

template<typename T>
DynamicQueue<T>::
    DynamicQueue() {}

template<typename T>
DynamicQueue<T>::
    DynamicQueue(std::initializer_list<T> list):
        _list{list} {}

template<typename T>
DynamicQueue<T>::
    DynamicQueue(const DynamicQueue& stack):
        _list{stack._list} {}

template<typename T>
DynamicQueue<T>::
    DynamicQueue(DynamicQueue&& stack):
        _list{ std::move(stack._list) } {}

template<typename T>
bool DynamicQueue<T>::
    isEmpty() const
    {
        return _list.isEmpty();
    }

template<typename T>
uint DynamicQueue<T>::
    getSize() const
    {
        return _list.getSize();
    }

template<typename T>
DynamicQueue<T>& DynamicQueue<T>::
    clear()
    {
        _list.clear();

        return *this;
    }

template<typename T>
DynamicQueue<T>& DynamicQueue<T>::
    enqueue(const T& value)
    {
        _list.addBack(value);

        return *this;
    }

template<typename T>
T DynamicQueue<T>::
    dequeue()
    {
        return _list.deleteBack();
    }

template<typename T>
T DynamicQueue<T>::
    peek() const
    {
        return _list.getLast();
    }

template<typename T>
std::ostream& operator<<(std::ostream& out, const DynamicQueue<T>& queue)
{
    out << queue._list << std::endl;
    
    return out;
}

