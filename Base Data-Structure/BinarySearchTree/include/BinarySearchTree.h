#pragma once
#include<iostream>

template<class E,class K>class BST;

template<class E,class K>
class BSTNode{
    friend class BST<E,K>;
public:
    BSTNode():leftChild(NULL), rightChild(NULL){}
    BSTNode(const E d):data(d),leftChild(NULL),rightChild(NULL){}
    BSTNode(const E d=0,BSTNode<class E,class K>*L=NULL,BSTNode<class E,class K>*R=NULL):data(d),leftChild(L),rightChild(R){}
    ~BSTNode(){}

    void setData(const E d){data=d;}
    E getData(){return data;}


protected:
    E data;
    BSTNode<E,K>*leftChild,* rightChild;
};

template<class E,class K>
class BST{
private:
    BSTNode<class E,class K>*root;
    T RefValue;
    BSTNode<class E,class K>*lastFound;
    void MakeEmpty(BSTNode<class E,class K>*&ptr);
    bool Insert(const E&x,BSTNode<class E,class K>*&ptr);
    bool Remove(const E&x,BSTNode<class E,class K>*&ptr);
    void PrintTree(BSTNode<class E,class K>*&ptr)const;
    BSTNode<class E,class K>*Copy(const BSTNode<class E,class K>*&ptr);
    BSTNode<class E,class K>*Find(const E&x,BSTNode<class E,class K>*&ptr)const;
    BSTNode<class E,class K>*Min(BSTNode<class E,class K>*&ptr)const;
    BSTNode<class E,class K>*Max(BSTNode<class E,class K>*&ptr)const;
    //friend class BSTIterator<class E,class K>;
public:
    BST():root(NULL){}
    BST(E value):RefValue(value),root(NULL){}
    ~BST();
    const BST<class E,class K>&operator=(const BST<class E,class K>&Value);
    void MakeEmpty(){
        MakeEmpty(root);
        root=NULL;
    }
    void PrintTree()const{
        PrintTree(root);
    }
    int Find(const E&x)const{
        return Find(x,root)!=NULL;
    }
    E Min(){
        return Min(root)->data;
    }
    E Max(){
        return Max(root)->data;
    }
    void Insert(const E&x){
        Insert(x,root);
    }
    void Remove(const E&x){
        Remove(x,root);
    }
};

template<class E,class K>
BSTNode<class E,class K>* BST<class E,class K>::Find(const E&x,BSTNode<class E,class K>*&ptr)const{
    if(ptr==NULL){
        return  NULL;
    }
    else if(x<ptr->data){
        return Find(x,ptr->leftChild);
    }
    else if(x>ptr->data){
        return Find(x,ptr->rightChild);
    }
    else{
        return ptr;//found 
    }
}

//非递归算法
template<class E,class K>
BSTNode<class E,class K>* BST<class E,class K>::Find(const E&x,BSTNode<class E,class K>*&ptr)const{
    if(ptr!=NULL){
        BSTNode<class E,class K>*temp=ptr;
        while(temp!=NULL){
            if(temp->data==x){
                return temp;//found
            }
            else if(temp->data<x){
                temp=temp->rightChild;
            }
            else if(temp->data>x){
                temp=temp->leftChild;
            }
        }
    }
    return NULL;
}

template<class E,class K>
bool BST<class E,class K>::Insert(const E&x,BSTNode<class E,class K>*&ptr){
    if(ptr==NULL){
        ptr=new BSTNode<T>(x);
        if(ptr==NULL){
            std::cout<<"Out of Space"<<std::endl;
            exit(1);
        }
    }
    else if(x<ptr->data){
        Insert(x,ptr->leftChild);
    }
    else if(x>ptr->data){
        Insert(x,ptr->rightChild);
    }
    else{
        //repeated data is missed
        ;
    }
}

template<class E,class K>
BST<class E,class K>::BST(E value){
    E&x;
    root=NULL;
    RefValue=value;
    std::cout<<"输入元素："<<std::endl;
    std::cin>>x;
    while(x->data!=RefValue){
        Insert(x,root);
        std::cout<<"继续输入："<<std::endl;
        std::cin>>x;
    }
}

template<class E,class K>
bool BST<class E,class K>::Remove(const E&x,BSTNode<class E,class K>*&ptr){
    BSTNode<class E,class K>*temp;
    if(ptr!=NULL){
        if(x<ptr->data){
            Remove(x,ptr->leftChild);
        }
        else if(x>ptr->data){
            Remove(x,ptr->rightChild);
        }
        else if(ptr->leftChild!=NULL&&ptr->rightChild!=NULL){
            temp=ptr->rightChild;
            while(temp->leftChild!=NULL){
                temp=temp->leftChild;
            }
            ptr->data=temp->data;
            Remove(ptr->data,ptr->rightChild);
        }
        else{
            temp=ptr;
            if(ptr->leftChild!=NULL){
                ptr=ptr->leftChild;
            }
            else{
                ptr=ptr->rightChild;
            }
            delete temp;
            return true;
        }
    }
    return false;
}

