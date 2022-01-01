#pragma once

#include <iostream>
//#include"Examinee.h"

template<class T>
class List;

template<class T>
class ListNode {
	friend class List<T>;
	T data;
	ListNode<T>* link;//link to the next node
public:
	ListNode();
	ListNode(const T& item);
	ListNode<T>* NextNode() {
		return link;
	}// return the address of the next node
	ListNode<T>* GetNode(const T& item, ListNode<T>* next = NULL) {
		ListNode<T>* newNode = new ListNode<T>(item);
		newNode->link = next;
		return newNode;
	}// create a new node with data:item and pointer :next
	void  InsertAfter(ListNode<T>* node) {
		node->link = link;
		link = node;
	}   // insert node after the current node
	ListNode<T>* RemoveAfter();// remove the next node of the current one
	T  GetData();
	T* GetDataAddress() {
		return &data;
	}
	bool Search(const std::string dataName, T& x);
};

template<class T>
class List {
	ListNode<T>* first;
public:
	List() { first = new ListNode<T>; }
	List(const T& value) {
		first = new ListNode<T>(value);
	}
	~List();
	void MakeEmpty();//clear the whole List
	int lenth()const;
	ListNode<T>* FindWithCertainData(T value);//return the address of the node with certain data
	ListNode<T>* FindWithCertainData(const std::string& dataName, T& x);
	ListNode<T>* Find(int i);
	ListNode<T>* GetFirst() {
		return first;
	}
	bool Insert(T value, int i);//insert a value to position[i-1]
	T* Remove(int i);
	T* Get(int i);//return an  address of the value at position[i-1]
	void output();
};

template<class T>
ListNode<T>::ListNode() :link(NULL) { };

//template<class T>
//ListNode<T>:: ListNode():data(item),link(NULL){  };



template<class T>
ListNode<T>* ListNode<T>::RemoveAfter() {
	ListNode<T>* temp = link;
	if (link == NULL) {
		return NULL;
	}
	link = temp->link;
	return temp;
}

template<class T>
T ListNode<T>::GetData() {
	return data;
}

template<class T>
List<T>::~List() {
	MakeEmpty();
	delete first;
}

template<class T>
void List<T>::MakeEmpty() {
	ListNode<T>* p;
	while (first->link != NULL) {
		p = first->link;
		first->link = p->link;
		delete p;
	}
}

template<class T>
int List<T>::lenth()const {
	ListNode<T>* p = first->link;
	int count = 0;
	while (p != NULL) {
		p = p->link;
		count++;
	}
	return count;
}

template<class T>
ListNode<T>* List<T>::FindWithCertainData(T value) {
	ListNode<T>* p = first->link;
	while (p != NULL && p->data != value) {
		p = p->link;
	}
	return p;
}

/*template<class T>
ListNode<T>* List<T>::FindWithCertainData(const std::string& dataType,T& x){
	ListNode<T>*p=first->link;
	while(p!=NULL){

	}
}*/

template<class T>
ListNode<T>* List<T>::Find(int i) {
	if (i < -1) {
		return NULL;
	}
	else if (i == -1) {
		return first;
	}
	else {
		ListNode<T>* p = first->link;
		int j = 0;
		while (p != NULL && j < i) {
			p = p->link;
			j++;
		}
		return p;
	}
}

template<class T>
bool List<T>::Insert(T value, int i) {
	ListNode<T>* p = Find(i - 1);
	if (p == NULL) {
		return false;
	}
	ListNode<T>* newNode = new ListNode<T>;
	newNode->data = value;
	newNode->link = p->link;
	p->link = newNode;
	return true;
}

template<class T>
T* List<T>::Remove(int i) {
	ListNode<T>* p = Find(i - 1), * q;
	if ((p == NULL) || (p->link == NULL)) {
		return NULL;
	}
	q = p->link;//memory the next node
	p->link = q->link;
	T* value = new T(q->data);
	delete q;
	return value;
}

template<class T>
T* List<T>::Get(int i) {
	ListNode<T>* p = Find(i);
	if (p == NULL || p == first) {
		return NULL;
	}
	else {
		return &p->data;
	}
}

template<class T>
void List<T>::output() {
	ListNode<T>* p = first->link;
	int count = 1;
	while (p != NULL) {
		std::cout << "#" << count++ << " " << p->data;
		p = p->link;
	}
}


