#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Node.h"
#include "QueueADT.h"
#include <iostream>

template <typename T>
class PriorityQueue : public QueueADT<T>
{
private:
    Node<T> *front;
    int size;

public:
    PriorityQueue() : front(nullptr), size(0) {}

    void enqueue(const T &data, int pri)
    {

        Node<T> *newnode = new Node<T>;
        newnode->setItem(data);
        newnode->setPriority(pri);

        if (this->isEmpty() || front->getPriority() < newnode->getPriority())
        {
            newnode->setNext(front);
            front = newnode;
            size++;
            return;
        }
        else
        {
            Node<T> *temp = front;
            while (temp->getNext() != nullptr && temp->getNext()->getPriority() > newnode->getPriority())
            {
                temp = temp->getNext();
            }

            newnode->setNext(temp->getNext());
            temp->setNext(newnode);
            size++;
        }
    }

    T dequeueAndReturn()
    {
        if (this->isEmpty())
            return T();
        T data = front->getItem();
        Node<T> *delptr = front;
        front = front->getNext();
        delete delptr;
        size--;
        return data;
    }

    bool dequeue(T &data)
    {

        if (this->isEmpty())
            return false;
        data = front->getItem();
        Node<T> *delptr = front;
        front = front->getNext();
        delete delptr;
        size--;
        return true;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    bool getFront(T &data) const
    {
        if (this->isEmpty())
        {
            std::cout << "Queue is empty" << std::endl;
            data = T();
            return false;
        }
        else
        {
            data = front->getItem();
            return true;
        }
    }

    // get front pointer not item
    Node<T> *getFrontPtr() const
    {
        return front;
    }

    void displayQueue()
    {
        Node<T> *temp = front;
        while (temp != nullptr)
        {
            std::cout << (temp->getItem()) << "  <  ";
            temp = temp->getNext();
        }
        std::cout << std::endl;
    }
    bool removeAt(int position)
    {
        if (position < 0 || position >= size)
        {
            return false;
        }

        if (position == 0)
        {
            dequeue();
            return true;
        }

        Node<T> *temp = front;
        for (int i = 0; i < position - 1; ++i)
        {
            temp = temp->getNext();
        }

        Node<T> *toRemove = temp->getNext();
        temp->setNext(toRemove->getNext());
        delete toRemove;
        size--;

        return true;
    }
};

#endif

// class name and all its methods and attributes
// Priority queue : enqueue, dequeue, isEmpty, getSize, getFront, displayQueue attributes : front, size