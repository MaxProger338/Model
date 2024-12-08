#pragma once

#ifndef __DYNAMIC_QUEUE_H__
#define __DYNAMIC_QUEUE_H__

#include "../DoubleLinkedList/DoubleLinkedList.h"

#include <iostream>
#include <initializer_list>

typedef unsigned int uint;

template<typename T>
class DynamicQueue
{
    private:
        DoubleLinkedList<T> _list;

    public:
        DynamicQueue();

        DynamicQueue(std::initializer_list<T> list);

        DynamicQueue(const DynamicQueue& stack);

        DynamicQueue(DynamicQueue&& stack);

        bool isEmpty() const;

        uint getSize() const;

        DynamicQueue& clear();

        DynamicQueue& enqueue(const T& value);

        T dequeue();

        T peek() const;

        DynamicQueue& operator=(const DynamicQueue& src);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const DynamicQueue<U>& queue);
};

#include "DynamicQueue.cpp"

#endif