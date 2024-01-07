#ifndef QUEUEADT_H
#define QUEUEADT_H

#include "Node.h"

template <typename T>
class QueueADT
{
public:
    // virtual void enqueue(const T& data, int pri);
    // virtual void enqueue(const T& data);
    virtual bool dequeue(T &data) = 0;
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
    virtual bool getFront(T &data) const = 0;
};

#endif
