#pragma once
#include"LinkedStack.h"

template<class T>
struct AVLNode{
        T data;
        AVLNode<T>*left,*right;
        int balance;
        AVLNode():left(NULL),right(NULL),balance(0) {};
        AVLNode(T d,AVLNode<T>*l=NULL,AVLNode<T>*r=NULL):data(d),left(l),right(r),balance(0) {};
};

template<class T>
class AVLTree{
protected:
    T RefValue;
    AVLNode<T>*root;
    bool insert(AVLNode<T>*&ptr,T& el);
    void RotateLeft(AVLNode<T>*Tree);
    void RotateRight(AVLNode<T>*Tree);
    void RotateLR(AVLNode<T>*&Tree);
    void RotateRL(AVLNode<T>*&Tree);
    int Depth(AVLNode<T>*t)const;
public:
    AVLTree():root(NULL){}
    AVLTree(T Ref):RefValue(Ref),root(NULL){}
    int Insert(T& x){
        return insert(root,x);
    }
    void Traverse(AVLNode<T>*ptr,std::ostream& out)const;
    template<class Type>friend std::istream& operator>>(std::istream&in,AVLTree<Type>&Tree);
    template<class Type>friend std::ostream& operator<<(std::ostream&out,AVLTree<Type>&Tree);

    int Depth()const;
};

//左旋
template<class T>
void AVLTree<T>::RotateLeft(AVLNode<T>*Tree){
    AVLNode<T>*subL=Tree;
    Tree=Tree->right;
    subL->right=Tree->left;
    Tree->left=subL;
    subL->balance=Tree->balance=0;
}

template<class T>
void AVLTree<T>::RotateRight(AVLNode<T>*Tree){
    AVLNode<T>*subR=Tree;
    Tree=Tree->left;
    subR->left=Tree.right;
    Tree->right=subR;
    subR->balance=Tree->balance=0;
}

template<class T>
void AVLTree<T>::RotateLR(AVLNode<T>*&Tree){
    AVLNode<T>*subR=Tree,*subL=subR->left;
    Tree=subL->right;
    subL->right=Tree->left;
    Tree->left=subL;
    if(Tree->balance<=0){
        subL->balance=0;
    }
    else{
        subL->balance=-1;
    }
    subR->left=Tree->right;
    Tree->right=subR;
    if(Tree->balance==-1){
        subR->balance=1;
    }
    else{
        subR->balance=0;
    }
    Tree->balance=0;
}

template<class T>
void AVLTree<T>::RotateRL(AVLNode<T>*&Tree){
    AVLNode<T>*subL=Tree,*subR=Tree->right;
    Tree=subR->left;
    subR->left = Tree->right;
    // ptr成为新根前甩掉它右边的负载
    Tree->right = subR;
    //右单旋转，ptr成为新根
    if ( Tree->balance >= 0){ 
        subR->balance = 0;
    }
    else{ 
        subR->balance = 1;
    }
    subL->right=Tree->left ;
    // ptr成为新根前甩掉它左边的负载
    Tree->left= subL;
    //左单旋转，ptr成为新根
    if (Tree->balance == 1){ 
        subL->balance = -1 ;
    }
    else{ 
        subL->balance=0;
    }
    Tree->balance=0;
}

template<class T>
bool AVLTree<T>::insert(AVLNode<T>*&ptr,T&el){
    AVLNode<T>*pr=NULL,*p=ptr,*q;
    int d;
    LinkedStack<AVLNode<T>*>st;
    while(p!=NULL){
        if(el==p->data){
            return false;
        }
        pr=p;
        st.Push(pr);
        if(el<p->data){
            p=p->left;
        }
        else{
            p=p->right;
        }
    }
    p=new AVLNode<T>*(el);
    if(p==NULL){
        std::cerr<<"存储空间不足!"<<std::endl;
        exit(1);
    }
    if(pr==NULL){//空树
        ptr=p;
        return true;
    }
    if(el<pr->data){
        pr->left=p;
    }
    else{
        pr->right=p;
    }
    while(!st->IsEmpty()){
        st.Pop(pr);
        if(p==pr->left){
            pr->balance--;
        }
        else{
            pr->balance++;
        }
        if(pr->balance==0){
            break;
        }
        if(pr->balance==1||pr->balance==-1){
            p=pr;
        }
        else{
            d=(pr->balance<0)?-1:1;
            if(p->balance==d){
                if(d==-1){
                    RotateRight(pr);
                }
                else{
                    RotateLeft(pr);
                }
            }
            else{
                if(d==-1){
                    RotateLR(pr);
                }
                else{
                    RotateRL(pr);
                }
            }
            break;
        }
    }
    if(st.IsEmpty()==true){
        ptr=pr;
    }
    else{
        st.getTop(q);
        if(q->dara>pr->data){
            q->left=pr;
        }
        else{
            q->right=pr;
        }
    }
    return true;
}

template<class Type>
std::istream& operator>>(std::istream&in,AVLTree<Type>&Tree){
    Type item;
    std::cout<<"Construct AVL"<<std::endl;
    std::cout<<"Input Data(end with"<<Tree.RefValue<<"):";
    in>>item;
    while(item!=Tree.RefValue){
        Tree.Insert(item);
        std::cout<<"Input Data(end with"<<Tree.RefValue<<"):";
        in>>item;
    }
    return in;
}

template<class Type>
std::ostream& operator<<(std::ostream&out,AVLTree<Type>&Tree){
    out<<"InOrder traversal of AVL tree";
    Tree.Traverse(Tree.root,out);
    out<<std::endl;
    return out;
}

template<class T>
void AVLTree<T>::Traverse(AVLNode<T>*ptr,std::ostream&out)const{
    if(ptr!=NULL){
        Traverse(ptr->left,out);
        out<<ptr->data<<" ";
        Traverse(ptr->right,out);
    }
}