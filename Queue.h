
#ifndef QUEUE_H
#define QUEUE_H

#include "QueueADT.h"
#include "Node.h"

template <typename T>
class Queue : public QueueADT<T>
{
private:
    Node<T> *front;
    Node<T> *rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(const T &data)
    {
        Node<T> *temp = new Node<T>(data);
        if (isEmpty())
        {
            rear = temp;
            rear->setNext(rear);
        }
        else
        {
            temp->setNext(rear->getNext());
            rear->setNext(temp);
            rear = temp;
        }
        size++;
    }

    T dequeueAndReturn()
    {
        if (this->isEmpty())
            return T();
        else if (rear == rear->getNext())
        {
            T dequeuedElement = rear->getItem();
            delete rear;
            rear = nullptr;
            size--;
            return dequeuedElement;
        }
        else
        {
            Node<T> *old = rear->getNext();
            T dequeuedElement = old->getItem();
            rear->setNext(old->getNext());
            delete old;
            size--;
            return dequeuedElement;
        }
    }

    bool dequeue(T &data)
    {
        if (isEmpty())
        {
            return false; // Unable to remove, list is empty
        }
        else
        {
            Node<T> *old = rear->getNext();
            data = old->getItem(); // Set data to the item being removed
            if (rear == old)
            {
                // The queue only has one item
                rear = nullptr;
            }
            else
            {
                rear->setNext(old->getNext());
            }
            delete old;
            size--;
        }
        return true;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }

    bool getFront(T &data) const
    {
        if (this->isEmpty())
        {
            return false;
        }
        else
        {
            data = rear->getNext()->getItem();
            return true;
        }
    }

    void displayQueue() const
    {
        if (isEmpty())
            cout << "[ ]";
        else if (rear->getNext() == rear)
            cout << "[" << rear->getItem() << "]";
        else
        {
            Node<T> *ptr = rear->getNext();
            cout << "[ ";
            do
            {
                cout << ptr->getItem() << ' ';
                ptr = ptr->getNext();
            } while (ptr != rear->getNext());
            cout << ']';
        }
    }
};

#endif