#include "DoubleLinkedList.h"

// ========== Node ==========

template<typename T>
DoubleLinkedList<T>::Node::
    Node(const T& value):
        value{ value }, 
        next{ nullptr }, 
        prev{ nullptr }
    {}

// ========== DoubleLinkedList ==========

template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::
    getNodeAt(uint index) const
    {
        uint size = getSize();

        if (index >= size)
            throw "Out of range";

        Node* current = nullptr;
        if (index <= (uint)size / 2)
        {
            current = _first;
            for (size_t i = 0; i < index; i++)
            {
                current = current->next;
            }
        }
        else
        {
            current = _last;
            for (size_t i = 0; i < size - index - 1; i++)
            {
                current = _last->prev;
            }
        }

        return current;
    }

template<typename T>
DoubleLinkedList<T>::
    DoubleLinkedList():
        _first{ nullptr },
        _last{ nullptr }
    {}

template<typename T>
DoubleLinkedList<T>::
    DoubleLinkedList(const std::initializer_list<T>& list):
        DoubleLinkedList()
    {
        for (auto i : list)
        {
            addBack(i);
        }
    }

template<typename T>
DoubleLinkedList<T>::
    DoubleLinkedList(const DoubleLinkedList& list):
        DoubleLinkedList()
    {
        Node* current = list._first;
        while (current)
        {
            addBack(current->value);
            current = current->next;
        }
    }

template<typename T>
DoubleLinkedList<T>::
    DoubleLinkedList(DoubleLinkedList&& list)
    {
        Node* current = list._first;
        _first = current;
        _last = list._last;

        while (current)
        {
            _first->next = current->next;
            _first->prev = current->prev;
            _first = _first->next;

            current = current->next;
        }
        _first = list._first;

        list._first = nullptr;
        list._last = nullptr;
    }

template<typename T>
DoubleLinkedList<T>::
    ~DoubleLinkedList()
    {
        if (!isEmpty())
        {
            Node* current = _first->next;
            while (current)
            {
                delete _first;
                _first = current;
                current = current->next;
            }

            delete _first;

            _first = nullptr;
            _last = nullptr;
        }
    }

template<typename T>
bool DoubleLinkedList<T>::
    isEmpty() const
    {
        return _first == nullptr;
    }

template<typename T>
uint DoubleLinkedList<T>::
    getSize() const
    {
        uint size = 0;

        Node* current = _first;
        while (current)
        {
            size++;
            current = current->next;
        }

        return size;
    }

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::
    clear()
    {
        this->~DoubleLinkedList();

        return *this;
    }

template<typename T>
T DoubleLinkedList<T>::
    getLast() const
    {
        return _last->value;
    }

template<typename T>
T DoubleLinkedList<T>::
    getFirst() const
    {
        return _first->value;
    }

template<typename T>
T DoubleLinkedList<T>::
    getAt(uint index) const
    {
        return getNodeAt(index)->value;
    }

template<typename T>
T DoubleLinkedList<T>::
    setAt(uint index, const T& value)
    {
        Node* node = getNodeAt(index);
        T current = node->value;

        node->value = value;

        return current;
    }

template<class T> 
T DoubleLinkedList<T>::
    deleteAt(uint index)
    {
        if (index >= getSize())
        {
            throw "Out of range";
        }

        if (index == 0)
        {
            return deleteForward();
        }

        else if (index == getSize() - 1)
        {
            return deleteBack();
        }

        Node* node = getNodeAt(index);
        T value{ node->value };

        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;
            
        return value;
    }

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::
    insertAt(uint index, const T& value)
    {
        if (index >= getSize())
        {
            throw "Out of range";
        }

        if (index == 0)
        {
            addForward(value);
        }

        else if (index == getSize() - 1)
        {
            Node* node = getNodeAt(index);

            addBack(_last->value);

            node->value = value;
        }

        else
        {
            Node* newNode = new Node(value);
            Node* nodeDist = getNodeAt(index);

            nodeDist->prev->next = newNode;
            newNode->next = nodeDist;

            newNode->prev = nodeDist->prev;
            nodeDist->prev = newNode;
        }

        return *this;
    }

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::
    addBack(const T& value)
    {
        Node* node = new Node(value);

        if (isEmpty())
        {
            _first = node;
            _last = node;
        }
        else
        {
            _last->next = node;
            node->prev = _last;
            _last = node;
        }

        return *this;
    }

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::
    addForward(const T& value)
    {
        Node* node = new Node(value);
        if (isEmpty())
        {
            _first = node;
            _last = node;
        }
        else
        {
            node->next = _first;
            _first->prev = node;
            _first = node;
        }

        return *this;
    }

template<typename T>
T DoubleLinkedList<T>::
    deleteBack()
    {
        if (isEmpty())
        {
            throw "Out of range";
        }

        Node* current = _last;
        T value = current->value;

        if (getSize() > 1)
        {
            _last = current->prev;
            _last->next = nullptr;
        }
        else
        {
            _last  = nullptr;
            _first = nullptr;
        }

        delete current;

        return value;
    }

template<typename T>
T DoubleLinkedList<T>::
    deleteForward()
    {
        if (isEmpty())
        {
            throw "Out of range";
        }

        Node* current = _first;
        T value = current->value;

        if (getSize() > 1)
        {
            _first = current->next;
            _first->prev = nullptr;
        }
        else
        {
            _first = nullptr;
            _last  = nullptr;
        }

        delete current;

        return value;
    }

template<typename T>
T& DoubleLinkedList<T>::
    operator[](uint index) const
    {
        return getNodeAt(index)->value;
    }

template<typename T>
uint DoubleLinkedList<T>::
    operator()() const
    {
        return getSize();
    }

template<typename T>
T DoubleLinkedList<T>::
    operator()(uint index)
    {
        return deleteAt(index);    
    }

template<typename T>
T DoubleLinkedList<T>::
    operator()(uint index, const T& value)
    {
        return setAt(index, value);
    }

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::
    operator=(const DoubleLinkedList& list)
    {
        if (&list == this)
        {
            return *this;
        }

        this->~DoubleLinkedList();

        Node* current = list._first;

        while (current)
        {
            addBack(current->value);
            current = current->next;
        }

        return *this;
    }

template<typename T>
std::ostream& operator<<(std::ostream& out, const DoubleLinkedList<T>& list)
    {
        typename DoubleLinkedList<T>::Node* current = list._first;
        while (current)
        {
            out << current->value << '\t';
            current = current->next;
        }
        out << std::endl;

        return out;
    }