#pragma once
#include<iostream>

template<class T>class LinkedQueue;

template<class T>
class LinkNode{
	T data;
    LinkNode<T> * link;//link to the next node
public:
    friend class LinkedQueue<T>;

    LinkNode();
	LinkNode(const T&item);
	LinkNode<T>* NextNode(){
		return link;
	}// return the address of the next node
	LinkNode<T>*GetNode(const T &item,LinkNode<T>* next=NULL){
        LinkNode<T>*newNode = new LinkNode<T>(item);
		newNode->link=next;
		return newNode;
	}// create a new node with data:item and pointer :next
	void  InsertAfter(LinkNode<T>* node){
		node->link=link;
		link=node;
	}   // insert node after the current node
	 LinkNode<T>* RemoveAfter();// remove the next node of the current one
	T  GetData();
	bool Search(const std::string dataName,T&x);
};

template<class T>
LinkNode<T>:: LinkNode():link(NULL){ };

template<class T>
LinkNode<T>:: LinkNode(const T&item):data(item),link(NULL){  };


template<class T>
LinkNode<T>* LinkNode<T>::RemoveAfter(){
	LinkNode<T>*temp=link;
	if(link==NULL){
		return NULL;
	}
	link=temp->link;
	return temp;
}

template<class T>
T LinkNode<T>::GetData(){
	return data;
}

template<class T>
class LinkedQueue{
public:

    LinkedQueue():rear(NULL),front(NULL){}
    ~LinkedQueue(){makeEmpty();}  
    bool EnQueue(const T x);
    bool DeQueue(T&x);
    bool getFront(T&x)const;
    void makeEmpty();
    bool IsEmpty()const{return (front==NULL)?true:false;}
    int getSize()const;
    template<class Type>friend std::ostream& operator<<(std::ostream&os,LinkedQueue<Type>&Q);
protected:
    LinkNode<T>*front,*rear;
};

template<class T>
void LinkedQueue<T>::makeEmpty(){
    LinkNode<T>*p;
    while(front!=NULL){
        p=front;
        front=p->link;
        delete p;
    }
}

template<class T>
bool LinkedQueue<T>::EnQueue(const T x){
    if(front==NULL){
        front=rear=new LinkNode<T>(x);
        if(front==NULL){
            std::cerr<<"Failed to create new queueNode!"<<std::endl;
            return false;
        }
    }
    else{
        rear->link=new LinkNode<T>(x);
        if(rear->link==NULL){
            std::cerr<<"Failed to create new queueNode!"<<std::endl;
            return false;
        }
        rear=rear->link;
    }
    return true;
}

template<class T>
bool LinkedQueue<T>::DeQueue(T&x){
    if(IsEmpty()==true){
        return false;
    }
    LinkNode<T>*p=front;
    x=front->data;
    front=front->link;
    delete p;
    return true;
}

template<class T>
bool LinkedQueue<T>::getFront(T&x)const{
    if(IsEmpty()==true){
        return false;
    }
    x=front->data;
    return true;
}

template<class T>
int LinkedQueue<T>::getSize()const{
    LinkNode<T>*p=front;
    int k=0;
    while(p!=NULL){
        p=p->link;
        k++;
    }
    return k;
}

template<class Type>
std::ostream& operator<<(std::ostream&os,LinkedQueue<Type>&Q){
    os<<"The number of elements in the queue"<<Q.getSize()<<std::endl;
    LinkNode<Type>*p=Q.front;
    int i=0;
    while(p!=NULL){
        os<<++i<<":"<<p->GetData()<<std::endl;
        p=p->NextNode();
    }
    return os;
}