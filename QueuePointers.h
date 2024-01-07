#ifndef QUEUE_point
#define QUEUE_point

#include "QueueADT.h"
#include "Node.h"

template <typename T>
class QueuePointers {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;

public:
    QueuePointers() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(T* data) {
        Node<T>* temp = new Node<T>(data);
        if (isEmpty()) {
            rear = temp;
            rear->setNext(rear);
        } else {
            temp->setNext(rear->getNext());
            rear->setNext(temp);
            rear = temp;
        }
        size++;
    }

    T* dequeueAndReturn() {
        if (isEmpty()) return nullptr;
        else if (rear == rear->getNext()) {
            T* dequeuedElement = rear->getItem();
            delete rear;
            rear = nullptr;
            size--;
            return dequeuedElement;
        } else {
            Node<T>* old = rear->getNext();
            T* dequeuedElement = old->getItem();
            rear->setNext(old->getNext());
            delete old;
            size--;
            return dequeuedElement;
        }
    }

    bool dequeue(T*& data) {
        if (isEmpty()) {
            return false; // Unable to remove, list is empty
        } else if (rear == rear->getNext()) {
            delete rear;
            rear = nullptr;
        } else {
            Node<T>* old = rear->getNext();
            rear->setNext(old->getNext());
            delete old;
        }

        size--;
        return true;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    T* getFront() const {
        if (this->isEmpty()) {
            return nullptr;
        } else {
            return rear->getNext()->getItem();
        }
    }

    void displayQueue() const {
        if (isEmpty()) cout << "[ ]";
        else if (rear->getNext() == rear) cout << "[" << *(rear->getItem()) << "]";
        else {
            Node<T>* ptr = rear->getNext();
            cout << "[ ";
            do {
                cout << *(ptr->getItem()) << ' ';
                ptr = ptr->getNext();
            } while (ptr != rear->getNext());
            cout << ']';
        }
    }
};

#endif
