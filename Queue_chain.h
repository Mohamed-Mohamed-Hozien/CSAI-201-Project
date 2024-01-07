#pragma once
#include ".\Node.h"
#include <iostream>
using namespace std;

template <typename T>
class Queue
{
private:
    Node<T> *rear;

public:
    Queue()
    {
        rear = nullptr;
    }
    // front = rear.getnext
    Node<T> *getFront()
    {
        if (rear == nullptr)
        {
            return nullptr;
        }
        else
        {
            return rear->getNext();
        }
    }

    Node<T> *getRear()
    {
        return rear;
    }
    T getFrontItem()
    {
        if (rear == nullptr)
        {
            return false;
        }
        else
        {
            return rear->getNext()->getItem();
        }
    }

    T getRearItem()
    {
        if (rear == nullptr)
        {
            return false;
        }
        return rear->getItem();
    }

    void display()
    {
        if (rear == nullptr)
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

    // enqueues from rear
    void enqueue(const T &data)
    {
        Node<T> *temp = new Node<T>(data);
        if (rear == nullptr)
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
    }

    // dequeues from front
    void dequeue()
    {
        if (rear == nullptr)
        {
            return;
        }
        else if (rear == rear->getNext())
        {
            delete rear;
            rear = nullptr;
        }
        else
        {
            Node<T> *old = rear->getNext();
            rear->setNext(old->getNext());
            delete old;
        }
    }
};