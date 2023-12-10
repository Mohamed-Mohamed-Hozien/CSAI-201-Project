
#ifndef _NODE
#define _NODE
template <typename T>
class Node
{
private:
	T item; 
	Node<T>* next;
	int priority;
public :
	Node();
	Node(const T & r_Item);	
	Node(const T & r_Item, Node<T>* nextNodePtr);
	void setItem(const T & r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const ;
	Node<T>* getNext() const ;
	int getPriority() const;
	void setPriority(int r_Priority);
}; 

template < typename T>
Node<T>::Node() 
{
	next = nullptr;
	priority = 0;
} 

template < typename T>
Node<T>::Node( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T Node<T>::getItem() const
{
	return item;
} 

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
} 

template < typename T>
int Node<T>::getPriority() const { return priority; }

template < typename T> 
void Node<T>::setPriority(int r_Priority){
	priority = r_Priority;
}

#endif
