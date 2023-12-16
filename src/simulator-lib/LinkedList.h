#pragma once
#include <iostream>

template<typename T>
class LinkedList
{
    private:
    template<typename G>
        struct Node
        {
            T key;
            Node<T>* next;
            Node<T>* prev;
            Node(T key) : key(key), next(nullptr), prev(nullptr) {};
        };

    public:
        LinkedList() noexcept;
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);
        ~LinkedList();

        // Operators 
        bool operator==(const LinkedList<T>& other) const;

        // Functions
        void push(const T& a);
        void pop_front();
        void pop_back();
        void push_at(const T& a, std::size_t index);

        void erase(std::size_t pos);
        T get(std::size_t pos) const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        std::size_t getSize() const;
        bool empty() const;
        void reverse();

        void sort();

        struct Iterator
        {
            friend LinkedList<T>::Iterator LinkedList<T>::erase(Iterator iter);

            public:
                Iterator() : current(nullptr) {};
                Iterator(Node<T>* current) : current(current) {};
                bool operator==(const Iterator& b)
                {
                    return current == b.current;
                };
                bool operator!=(const Iterator& b)
                {
                    return current != b.current;
                };

                T& operator*() const 
                {
                    return current->key;
                };

                Iterator& operator++()
                {
                    if(current)
                        current = current->next;

                    return *this;
                };
                Iterator operator++(int)
                {
                    Iterator copy = *this;
                    ++ (*this);
                    return copy;
                };

            private:
                Node<T>* current;
        };
        
        Iterator begin() const
        {
            return Iterator(head);
        };

        Iterator end() const
        {
            return Iterator(nullptr);
        };

        Iterator erase(Iterator iter);

    private:
        Node<T>* head;
        Node<T>* tail;
        std::size_t size;

        void free();
        void copyFrom(const LinkedList& other);
        void mergeSort(Node<T>*& source);
        void split(Node<T>* source, Node<T>*& front, Node<T>*& back);
        Node<T>* mergeHelper(Node<T>* left, Node<T>* right);

};

template <typename T>
inline LinkedList<T>::LinkedList() noexcept
: head(nullptr), tail(nullptr), size(0) {}

template <typename T>
inline LinkedList<T>::LinkedList(const LinkedList &other)
: head(nullptr), tail(nullptr), size(0) 
{
    copyFrom(other);
}

template <typename T>
inline LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other)
{
    if(this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}


template <typename T>
inline LinkedList<T>::~LinkedList()
{
    free();
}

template <typename T>
inline bool LinkedList<T>::operator==(const LinkedList & other) const {
    if(this->size == 0 &&  other.size == 0)
        return false;

    if(this->size != other.size)
        return false;

    Node<T>* front = head;
    Node<T>* otherFront = other.front;

    while(front)
    {
        if(front->key != otherFront->key)
            return false;

        front = front->next;
        otherFront = otherFront->next;
    };

    return true;
}

template <typename T>
inline void LinkedList<T>::free()
{
    while (head)
    {
        Node<T>* toDel = head;
        head = head->next;

        delete toDel;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
inline void LinkedList<T>::copyFrom(const LinkedList &other)
{
    if(!other.head) 
        return;

    head = new Node<T>(other.head->key);
    Node<T>* otherFront = other.head->next;
    size = 1;

    Node<T>* front = head;
    while(otherFront)
    {
        front->next = new Node<T>(otherFront->key);
        front->next->prev = front;

        front = front->next;
        otherFront = otherFront->next;

        size++;
    }

    tail = front;
}

template <typename T>
inline void LinkedList<T>::push(const T &a)
{
    Node <T> *newNode = new Node<T>(a);

    if(!head)
    {
        head = newNode;
    }else {
        tail->next = newNode;
        newNode->prev = tail;
    }

    tail = newNode;
    size++;
}

template<typename T> inline void LinkedList<T>::pop_back()
{
    if(head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node<T>* toDel = tail;

        tail = tail->prev;
        tail->next = nullptr;
        delete toDel;             
    }

    size--;
}

template <typename T>
inline void LinkedList<T>::push_at(const T &a, std::size_t index)
{
    if(index > size)
        throw std::out_of_range("Invalid index to push at");

    Node<T>* newNode = new Node<T>(a);

    if(index == 0)
    {
        newNode->next = head;

        if(head != nullptr) head->prev = newNode;

        head = newNode;

        if(tail == nullptr) tail = newNode;
    } else 
    {
        Node<T>* current = head;
        for(std::size_t i = 0; i < index - 1; ++i)
            current = current->next;

        newNode->next = current->next;
        newNode->prev = current;

        if(current->next != nullptr) current->next->prev = newNode;
        current->next = newNode;

        if(newNode->next == nullptr) tail = newNode;
    }
    size++;
}

template <typename T>
inline void LinkedList<T>::pop_front()
{
    if(head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node<T>* toRemove = head;
        head = head->next;
        head->prev = nullptr;

        delete toRemove;
    }

    size--;
}

template <typename T>
inline T &LinkedList<T>::front()
{
    if(head)
        return head->key;
    throw std::out_of_range("Linked List is empty");
}

template <typename T>
inline const T &LinkedList<T>::front() const
{
    if(head)
        return head->key;
    throw std::out_of_range("Linked List is empty");
}

template <typename T>
inline const T &LinkedList<T>::back() const
{
    if(tail)
        return tail->key;

    throw std::out_of_range("Linked List is empty");
}

template <typename T>
inline T &LinkedList<T>::back() 
{
    if(tail)
        return tail->key;

    throw std::out_of_range("Linked List is empty");
}

template <typename T>
inline bool LinkedList<T>::empty() const
{
    return size == 0;
}

template<typename T> inline void LinkedList<T>::reverse()
{
    Node<T>* current = head;
    Node<T>* temp = nullptr;
    tail = head;

    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != nullptr) {
        head = temp->prev;
    }
}

template <typename T>
inline void LinkedList<T>::erase(std::size_t index)
{
    if(index >= size)
        throw std::out_of_range("Invalid index passed to erase");

    Node<T>* current = head;

    for(std::size_t i = 0; i < index; ++i)
        current = current->next;

    if(current->prev) current->prev->next = current->next;
    else head = current->next;

    if(current->next) current->next->prev = current->prev;
    else tail = current->prev;

    delete current;

    size--;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::erase(Iterator iter) {
    Node<T>* nodeToDelete = iter.current;

    if (nodeToDelete == nullptr) 
        return Iterator(nullptr); 

    if (nodeToDelete->prev)
        nodeToDelete->prev->next = nodeToDelete->next;
    else
        head = nodeToDelete->next;  

    if (nodeToDelete->next)
        nodeToDelete->next->prev = nodeToDelete->prev;
    else
        tail = nodeToDelete->prev; 
        
    Iterator nextIter(nodeToDelete->next);
    delete nodeToDelete;
    size--;

    return nextIter;  
}


template<typename T>
inline std::size_t LinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
inline T LinkedList<T>::get(std::size_t index) const
{
    if(index >= size)
        throw std::out_of_range("Invalid argument");

    if(index == 0)
        return front();

    else if (index == size - 1)
        return back();

    else {
        Node<T>* front = head;

        while(index)
        {
            index--;
            front = front->next;
        }

        return front->key;
    }
}

template <typename T>
void LinkedList<T>::sort()
{
    if (size <= 1)
        return;

    mergeSort(head);

    size = 1;
    Node<T>* front = head;

    while (front && front->next) {
        size++;
        front = front->next;
    }
    tail = front;
}


template <typename T>
void LinkedList<T>::mergeSort(Node<T>*& source)
{
    if (!source || !source->next)
        return;

    Node<T>* left, *right;
    split(source, left, right); 

    mergeSort(left);
    mergeSort(right);

    source = mergeHelper(left, right);
}

template <typename T>
void LinkedList<T>::split(Node<T>* source, Node<T> *&front, Node<T> *&back)
{
    if (!source  || !source->next)
    {
        front = source;
        back = nullptr;
        return;
    }

    Node<T> * slow = source;
    Node<T> * fast = source->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    front = source;
    back = slow->next;
    slow->next = nullptr;
}

template <typename T>
LinkedList<T>::Node<T> *LinkedList<T>::mergeHelper(Node<T> * left, Node<T> * right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    Node<T> * result = nullptr;

    if (left->key <= right->key)
    {
        result = left;
        result->next = mergeHelper(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeHelper(left, right->next);
    }

    Node<T>* head = result;
    while (head->prev != nullptr) {
        head = head->prev;
    }
    
    result->prev = nullptr;  

    return result;
}