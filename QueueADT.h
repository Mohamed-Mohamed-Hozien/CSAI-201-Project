
#ifndef QUEUEADT_H
#define QUEUEADT_H

#include "Node.h"

template <typename T>
class QueueADT {
private:
    Node<T>* front; 
    Node<T>* rear;  
    int size; 

public:
    QueueADT() : front(nullptr), rear(nullptr), size(0) {}

    virtual void enqueue(const T& data);

    virtual bool dequeue(T& data);

    virtual bool isEmpty() const;

    virtual int getSize() const;

    virtual bool getFront(T& data) const;
};

#endif
