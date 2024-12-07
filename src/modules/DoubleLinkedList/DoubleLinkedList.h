#pragma once

#ifndef __DOUBLE_LINKED_LIST_H__ 
#define __DOUBLE_LINKED_LIST_H__

#include <iostream>
#include <initializer_list>

typedef unsigned int uint;

template<typename T>
class DoubleLinkedList 
{
    private:
        struct Node
        {
            T     value;
            Node* next;
            Node* prev;

            Node(const T& value); 
        };

        Node* _first;
        Node* _last;

        Node* getNodeAt(uint index) const;

    public:
        DoubleLinkedList();

        DoubleLinkedList(const std::initializer_list<T>& list);

        DoubleLinkedList(const DoubleLinkedList& list);

        DoubleLinkedList(DoubleLinkedList&& list);

        ~DoubleLinkedList();

        bool isEmpty() const;

        uint getSize() const;

        DoubleLinkedList& clear();

        T getLast() const;

        T getFirst() const;

        T getAt(uint index) const;

        T setAt(uint index, const T& value);

        T deleteAt(uint index);

        DoubleLinkedList& insertAt(uint index, const T& value);

        DoubleLinkedList& addBack(const T& value);

        DoubleLinkedList& addForward(const T& value);

        T deleteBack();

        T deleteForward();

        T& operator[](uint index) const;

        uint operator()() const;

        T operator()(uint index);

        T operator()(uint index, const T& value);

        DoubleLinkedList& operator=(const DoubleLinkedList& list);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const DoubleLinkedList<U>& list);
};

#include "DoubleLinkedList.cpp"

#endif 