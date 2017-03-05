#include "stdafx.h"

template <class T>
Node<T>::Node()
{
	next = NULL;
}

template <class T>
Node<T>::Node(const T &item,Node<T> *ptrnext):data(item), nextptr(ptrnext)
{
}

template <class T>
Node<T>::~Node()
{
	nextptr = NULL;
}

template <class T>
void Node<T>::setNext(Node<T> *ptrnext)
{
	nextptr = ptrnext;
}

template <class T>
Node<T> *Node<T>::next() const
{
	return nextptr;
}

template <class T>
LinkList<T>::LinkList()
{
	head = NULL;
	tail = NULL;
	curr = NULL;
	size = 0;
}

template <class T>
LinkList<T>::~LinkList()
{
	Node<T> *t;
	curr = head;
	while(curr != NULL)
	{
		t = curr;
		curr = curr->next();
		freeNode(t);
	}
	head = NULL;
	tail = NULL;
	curr = NULL;
	size = 0;
}

template <class T>
Node<T> *LinkList<T>::next()
{
	if(curr == NULL)  return NULL;

	curr = curr->next();
	return curr;
}

template <class T>
Node<T> *LinkList<T>::current()
{
	return curr;
}

template <class T>
Node<T> *LinkList<T>::first()
{
	return head;
}

template <class T>
Node<T> *LinkList<T>::last()
{
	return tail;
}

template <class T>
Node<T> *LinkList<T>::getNode(const T &item, Node<T> *ptrnext)
{
	Node<T> *newNode;

	newNode = new Node<T>(item, ptrnext);

	return newNode;
}

template <class T>
Node<T> *LinkList<T>::findNode(int index)
{
	int icount = 0;
	curr = head;
	while(curr != NULL)
	{
		icount ++;
		if(icount == index)
			return curr;
		curr = curr->next();
	}
	return NULL;
}

template <class T>
Node<T> *LinkList<T>::findNode(const T &item)
{
	curr = head;
	while(curr != NULL)
	{
		if(curr->data == item)
			return curr;
		curr = curr->next();
	}
	return NULL;
}

template <class T>
void LinkList<T>::freeNode(Node <T> *p)
{
	delete p;
}

template <class T>
int LinkList<T>::getSize()
{
	return size;
}

template <class T>
int LinkList<T>::insertFront(const T &item)
{
	Node<T> *newNode;

	newNode = getNode(item, head);
	if(newNode == NULL) return -1;

	if(head == NULL)
	{
		head = newNode;
		tail = head;
	}
	else
		head = newNode;

	size ++;

	return 0;
}

template <class T>
int LinkList<T>::insertTail(const T &item)
{
	Node<T> *newNode;

	newNode = getNode(item, NULL);
	if(newNode == NULL) return -1;

	if(head == 0)
	{
		head = newNode;
		tail = head;
	}
	else
	{
		tail->setNext(newNode);
		tail = newNode;
	}
	size ++;

	return 0;
}

template <class T>
int LinkList<T>::insertAfter(const T &item, int index)
{
	int icount = 0;
	Node<T> *p = NULL, *newNode = NULL;

	if(index == 0)
	{
		if(insertFront(item) < 0)
			return -1;
		return 0;
	}

	p = head;
	while(p != NULL)
	{
		icount ++;
		if(icount == index)
			break;
		p = p->next();
	}

	if(p == NULL)
	{
		if(insertTail(item) < 0)
			return -1;
		return 0;
	}

	newNode = getNode(item, p->next());
	if(newNode == NULL) return -1;

	p->setNext(newNode);
	size ++;

	return 0;
}

template <class T>
int LinkList<T>::deleteFront(T *item)
{
	Node<T> *p;

	if(head == NULL)
	{
		if(item != NULL) item = NULL;
		return -1;
	}

	p = head;
	head = head->next();

	if(tail == p)
		tail = head;

	if(item != NULL)
		*item = p->data;

	size --;
	freeNode(p);

	return 0;
}

template <class T>
int LinkList<T>::deleteTail(T *item)
{
	Node<T> *p;

	if(head == NULL)
	{
		if(item != NULL) item = NULL;
		return -1;
	}

	if(head == tail)
	{
		if(item != NULL) *item = p->data;
		freeNode(p);
		head = tail = curr = NULL;
		size = 0;
		return 0;
	}

	p = head;
	while(p != NULL && p->next() != tail)
	{
		p = p->next();
	}

	tail = p;
	p = p->next();
	tail->setNext(NULL);

	if(item != NULL) *item = p->data;
	freeNode(p);
	size --;

	return 0;
}

template <class T>
int LinkList<T>::deleteNode(T *item, int index)
{
	int icount = 0, flag = 0;
	Node<T> *p = NULL, *t = NULL;

	p = head;
	if(index == 1)
	{
		if(deleteFront(item) < 0)
			return -1;
		return 0;
	}

	while(p != NULL)
	{		
		icount ++;
		if(icount == index - 1)
		{
			flag = 1;
			break;
		}
		p = p->next();
	}
	if(flag == 0 || p == tail) return -1;

	t = p->next();
	if(t == tail)
		tail = p;

	p->setNext(t->next());
	if(item != NULL) *item = t->data;
	freeNode(t);
	size --;

	return 0;
}

template <class T>
void LinkList<T>::reset()
{
	curr = head;
}

template <class T>
bool LinkList<T>::isEmpty()
{
	if(size == 0) 
		return true;
	else
		return false;
}

template <class T>
void LinkList<T>::clear()
{
	Node<T> *p, *t;
	p = head;

	while(p != NULL)
	{
		t = p;
		p = p->next();
		freeNode(t);
	}
	head = NULL;
	tail = NULL;
	curr = NULL;
	size = 0;
}
