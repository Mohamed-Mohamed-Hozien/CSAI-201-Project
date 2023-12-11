
#ifndef QUEUE_H
#define QUEUE_H

#include "QueueADT.h"
#include "Node.h"

template <typename T> //Linked Queue chain
class Queue : public QueueADT<T> {
private:
    Node<T>* rear;
    int size;

public:
    Queue() : rear(nullptr), size(0) {}

    void enqueue(const T& data) {
        Node<T>* temp = new Node<T>(data);
        if (isEmpty()) {
            rear = temp;
            rear->setNext(rear); 
        } else {
            temp->setNext(rear->getNext());
            rear->setNext(temp);
            rear = temp;
        }
    }
    
    T dequeueAndReturn()  {   //dequeues and returns dequeues element
        if (this->isEmpty()) return T();
        else if (rear == rear->getNext()) {
            T dequeuedElement = rear->getItem();
            delete rear;
            rear = nullptr;
            return dequeuedElement;
        } else {
            Node<T>* old = rear->getNext();
            T dequeuedElement = old->getItem();
            rear->setNext(old->getNext());
            delete old;
            return dequeuedElement;
        }
    }   

    bool dequeue(T& data)  { //dequeues only
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

        return true;
    }

    bool isEmpty() const  {
        return size == 0;
    }

    int getSize() const  {
        return size;
    }

    T getFront() const {
        if (this->isEmpty()) {
            return false;
        } else {
            return rear->getNext()->getItem();
            
        }
    }


    void displayQueue() const {
        if (isEmpty()) cout << "[ ]";
        else if (rear->getNext()==rear) cout<<"["<<rear->getItem()<<"]";
        else {
            Node<T>* ptr = rear->getNext();
            cout << "[ ";
            do {
                cout << ptr->getItem() << ' ';
                ptr = ptr->getNext();
            } while (ptr != rear->getNext());
            cout << ']';
        }
    }


};

#endif
