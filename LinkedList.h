#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
template <typename T>

class Iterator {
private:
    Node<T>* current;

public:
    Iterator(Node<T>* node) : current(node) {}

    T operator*() const {
        return current->getItem();
    }

    Iterator& operator++() {
        current = current->getNext();
        return *this;
    }

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList();
    ~LinkedList();

    void InsertEnd(const T& item);
    T RemoveBegin(const T& item);
    void RemoveAt(int index);
    bool IsEmpty() const;
    bool RemovewithItem(const T& item);
    bool getFront(const T& item);
    Iterator<T> begin() const {
        return Iterator<T>(head);
    }

    Iterator<T> end() const {
        return Iterator<T>(nullptr);
    }
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->getNext();
        delete current;
        current = next;
    }
    head = nullptr;
}

template <typename T>
bool LinkedList<T>::RemovewithItem(const T& item) {
    if (head == nullptr) {
        return false;
    }

    if (head->getItem() == item) {
        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    Node<T>* current = head;
    while (current->getNext() != nullptr) {
        if (current->getNext()->getItem() == item) {
            Node<T>* temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
            return true;
        }
        current = current->getNext();
    }
    return false;
}

template <typename T>
void LinkedList<T>::InsertEnd(const T& item) {
    Node<T>* newNode = new Node<T>(item);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
    }
}

template <typename T>
void LinkedList<T>::RemoveAt(int index) {
    if (index < 0 || head == nullptr) {
        return;
    }

    if (index == 0) {
        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        return;
    }

    Node<T>* current = head;
    for (int i = 0; current != nullptr && i < index - 1; ++i) {
        current = current->getNext();
    }

    if (current == nullptr || current->getNext() == nullptr) {
        return;
    }

    Node<T>* temp = current->getNext();
    current->setNext(temp->getNext());
    delete temp;
}

template <typename T>
bool LinkedList<T>::IsEmpty() const {
    return head == nullptr;
}

template <typename T>
T LinkedList<T>::RemoveBegin(const T& item) {
    if (head == nullptr) {
        return T();
    }

    Node<T>* temp = head;
    head = head->getNext();
    T data = temp->getItem();
    delete temp;
    return data;
}

template <typename T>
bool LinkedList<T>::getFront(const T& item){
    if (head == nullptr) {
        return false;
    }
    item = head->getItem();
    return true;
}


#endif
