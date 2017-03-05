#ifndef _LINK_LIST_H
#define _LINK_LIST_H

#include <iostream.h>

template <class T>
class Node
{
private:
	Node<T> *nextptr;
public:
	T data;
	Node();
	~Node();
	Node <T> *next() const;
	Node(const T &item, Node<T> *ptrnext=NULL);
	void setNext(Node<T> *ptrnext=NULL);
};

template <class T>
class LinkList
{
private:
	Node<T> *head;
	Node<T> *tail;
	Node<T> *curr;
	Node<T> *getNode(const T &item, Node<T> *ptrnext=NULL);
	void freeNode(Node <T> *p);
	int size;
public:
	LinkList();
	~LinkList();
	Node<T> *next();
	Node<T> *current();
	Node<T> *first();
	Node<T> *last();
	Node<T> *findNode(int index);
	Node<T> *findNode(const T &item); //此功能需要模板类重载等于运算符
	void reset();
	int getSize();
	int insertFront(const T &item);
	int insertTail(const T &item);
	int insertAfter(const T &item, int index);
	int deleteFront(T *item);
	int deleteTail(T *item);
	int deleteNode(T *item, int index);
	void clear();
	bool isEmpty();
};


#endif