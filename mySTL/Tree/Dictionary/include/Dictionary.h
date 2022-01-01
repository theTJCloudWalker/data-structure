#pragma once
#include"assert.h"

//Abstract data structure of Dictionary
const int DefaultSize=26;

template<class Name,class Attribute>
class Dictionary{
public:
    Dictionary(int size=DefaultSize);

    bool Member(Name name);

    Attribute*Search(Name name);

    void Insert(Name name,Attribute attribute);

    void Remove(Name name);
};



template<class E,class K>
struct ChainNode{
    E data;
    ChainNode<E,K>*link;
    ChainNode():link(NULL){}
    ChainNode(E&elem,ChainNode<E,K>*next=NULL)
    :data(elem),link(next){}
};

template<class E,class K>
class SortedChain{
public:
    SortedChain(){
        first=new ChainNode<E,K>;
        assert(first!=NULL);
    }
    ~SortedChain();
    ChainNode<E,K>*Search(const K key)const;
    void Insert(const K key,E&elem);
    bool Remove(const K key,E&elem);
    ChainNode<E,K>*Begin(){
        return first->link;
    }
    ChainNode<E,K>*Next(ChainNode<E,K>*current)const{
        if(current!=NULL){
            return current->link;
        }
        else{
            return NULL;
        }
    }
private:
    ChainNode<E,K>*first;
};

template<class E,class K>
ChainNode<E,K>*SortedChain<E,K>::Search(const K key)const{
    ChainNode<E,K>*p=first->link;
    while(p!=NULL&&p->data<key){
        p=p->link;
    }
    if(p!=NULL&&p->data==key){
        return p;
    }
    else{
        return NULL;
    }
}

template<class E,class K>
void SortedChain<E,K>::Insert(const K key,E&elem){
    ChainNode<E,K>*p=first->link,*pre=first,*newNode;
    while(p!=NULL&&p->data<key){
        pre=p;
        p=p->link;
    }
    if(p!=NULL&&p->data==key){
        p->data=elem;
        return;
    }
    newNode=new ChainNode<E,K>*(elem);
    if(newNode==NULL){
        std::cerr<<"存储分配失败！"<<std::endl;
        exit(1);
    }
    newNode->link=p;
    pre->link=newNode;
}

template<class E,class K>
bool SortedChain<E,K>::Remove(const K key,E&elem){
    ChainNode<E,K>*p=first->link,*pre=first;
    while(p!=NULL&&p->data<key){
        pre=p;
        p=p->link;
    }
    if(p!=NULL&&p->data==key){
        pre->link=p->link;
        elem=p->link;
        delete p;
        return true;
    }
    else{
        return false;
    }
}