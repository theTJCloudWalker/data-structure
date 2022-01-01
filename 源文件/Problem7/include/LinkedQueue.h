#pragma once
#include<iostream>

template<class T>class LinkedQueue;

template<class T>
class LinkQNode {    
    T data;
    LinkQNode<T>* link;//link to the next node
public:
    friend class LinkedQueue<T>;
    LinkQNode(){
        link=NULL;
    }
    LinkQNode(const T& item){
        data=item;
        link=NULL;
    }
    LinkQNode<T>* NextNode() {
        return link;
    }// return the address of the next node
    LinkQNode<T>* GetNode(const T& item, LinkQNode<T>* next = NULL) {
        LinkQNode<T>* newNode = new LinkQNode<T>(item);
        newNode->link = next;
        return newNode;
    }// create a new node with data:item and pointer :next
    void  InsertAfter(LinkQNode<T>* node) {
        node->link = link;
        link = node;
    }   // insert node after the current node
    LinkQNode<T>* RemoveAfter();// remove the next node of the current one
    T  GetData();
    //bool Search(const std::string dataName, T& x);
};



template<class T>
class LinkedQueue {
public:

    LinkedQueue() :rear(NULL), front(NULL) {}
    ~LinkedQueue() { makeEmpty(); }
    bool EnQueue(const T x);
    bool DeQueue(T& x);
    bool getFront(T& x)const;
    void makeEmpty();
    bool IsEmpty()const { return (front == NULL) ? true : false; }
    int getSize()const;
    template<class Type>friend std::ostream& operator<<(std::ostream& os, LinkedQueue<Type>& Q);
protected:
    LinkQNode<T>* front, * rear;
};

template<class T>
LinkQNode<T>* LinkQNode<T>::RemoveAfter() {
    LinkQNode<T>* temp = link;
    if (link == NULL) {
        return NULL;
    }
    link = temp->link;
    return temp;
}

template<class T>
T LinkQNode<T>::GetData() {
    return data;
}

template<class T>
void LinkedQueue<T>::makeEmpty() {
    LinkQNode<T>* p;
    while (front != NULL) {
        p = front;
        front = p->link;
        delete p;
    }
}

template<class T>
bool LinkedQueue<T>::EnQueue(const T x) {
    if (front == NULL) {
        front = rear = new LinkQNode<T>(x);
        if (front == NULL) {
            std::cerr << "Failed to create new queueNode!" << std::endl;
            return false;
        }
    }
    else {
        rear->link = new LinkQNode<T>(x);
        if (rear->link == NULL) {
            std::cerr << "Failed to create new queueNode!" << std::endl;
            return false;
        }
        rear = rear->link;
    }
    return true;
}

template<class T>
bool LinkedQueue<T>::DeQueue(T& x) {
    if (IsEmpty() == true) {
        return false;
    }
    LinkQNode<T>* p = front;
    x = front->data;
    front = front->link;
    delete p;
    return true;
}

template<class T>
bool LinkedQueue<T>::getFront(T& x)const {
    if (IsEmpty() == true) {
        return false;
    }
    x = front->data;
    return true;
}

template<class T>
int LinkedQueue<T>::getSize()const {
    LinkQNode<T>* p = front;
    int k = 0;
    while (p != NULL) {
        p = p->link;
        k++;
    }
    return k;
}

template<class Type>
std::ostream& operator<<(std::ostream& os, LinkedQueue<Type>& Q) {
    os << "The number of elements in the queue" << Q.getSize() << std::endl;
    LinkQNode<Type>* p = Q.front;
    int i = 0;
    while (p != NULL) {
        os << ++i << ":" << p->GetData() << std::endl;
        p = p->NextNode();
    }
    return os;
}