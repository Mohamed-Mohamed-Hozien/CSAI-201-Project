#pragma once
#include ".\Node.h"
#include <iostream>
using namespace std;

template <typename T>
class Queue{
    private:
    Node<T> * front;
    Node<T> * rear;
    public:
    Queue(){
        front=nullptr;
        rear.getNext()=front;
    }
	Node<T>* getFront() {
        if(front->getNext() ==nullptr){
            return;
        }
		return front->getItem();
	}
    
    Node<T>* getRear(){
        Node<T>* curr;
        if (front==nullptr){
            return;
        }
        else if( front->getNext() ==nullptr){
            return front;
        }
        else{
            curr=front;
            while (curr.getNext()!=nullptr){
                curr=curr.getNext();
            }
            rear=curr;
            return rear;
        }
    }

	void display() {
        if (front == nullptr) cout << "[ ]";
        else if (front->getNext() == nullptr) cout << "[ " << front->getItem() << " ]";
        else {
            Node<T>* ptr = front;
            cout << "[ ";
			do {
				cout << ptr->getItem() << ' ';
				ptr = ptr->getNext();
			} while (ptr != front);
            cout << ']';
        }
    }


	void Enqueue(const T& data)  // inserts at rear
	{
		Node<T>* temp = new Node<T>(data);
		if (front==nullptr){
            front=temp;
            return;
        }
        if (front->getNext()==nullptr){
            front->setNext(temp);
            return;
        }
        Node<T>* curr;
        curr=front;
        while(curr->getNext()!=nullptr){
            curr =curr->getNext();
        }
        curr->setNext(temp);
        return;
	}

	void Dequeue() //from front
	{
        if (front==nullptr){
            return;
        }
        Node<T>* old=front;
		front = front->getNext();
        delete old;}
};
