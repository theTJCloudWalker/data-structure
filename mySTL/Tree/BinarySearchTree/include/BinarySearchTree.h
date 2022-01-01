#pragma once
#include<iostream>

template<class E, class K>class BST;

template<class E, class K>
class BSTNode {
    friend class BST<E, K>;
public:
    BSTNode() :leftChild(NULL), rightChild(NULL) {}
    BSTNode(const E d) :data(d), leftChild(NULL), rightChild(NULL) {}
   // BSTNode(const E d = 0, BSTNode<E,K>* L = NULL, BSTNode<E,K>* R = NULL) :data(d), leftChild(L), rightChild(R) {}
    BSTNode<E,K>& operator=(BSTNode<E,K>& Value) {
        this->data = Value.data;
        this->leftChild = Value.leftChild;
        this->rightChild = Value.rightChild;

        return *this;
    }
    ~BSTNode() {}

    void setData(const E d) { data = d; }
    E getData() { return data; }

protected:
    E data;
    BSTNode<E, K>* leftChild, * rightChild;
};

template<class E, class K>
class BST {
private:
    BSTNode<E, K>* root;
    E RefValue=0;//输入终止符
    //BSTNode<E, K>* lastFound;
    void MakeEmpty(BSTNode<E, K>*& ptr);
    bool Insert(const E& x, BSTNode<E, K>*& ptr);
    bool Remove(const E& x, BSTNode< E, K>*& ptr);
    void PrintTree(BSTNode< E, K>* ptr)const;
    BSTNode<E, K>* Copy(const BSTNode< E, K>*& ptr);
    BSTNode<E, K>* Find(const E& x, BSTNode< E, K>*& ptr)const;
    BSTNode<E, K>* Min(BSTNode< E, K>*& ptr)const;
    BSTNode<E, K>* Max(BSTNode< E, K>*& ptr)const;
    //friend class BSTIterator<class E,class K>;
public:
    BST() :root(NULL) {}
    BST(E value) :RefValue(value), root(NULL) {}
    ~BST() { MakeEmpty(); }
    //const BST<class E, class K>& operator=(const BST<class E, class K>& Value);
    
    //void CreateWithArray(E arr[]);

    void MakeEmpty() {
        MakeEmpty(root);
        root = NULL;
    }
    void PrintTree()const {
        PrintTree(root);
    }
    int Find(const E& x)const {
        return Find(x, root) != NULL;
    }
    E Min() {
        return Min(root)->data;
    }
    E Max() {
        return Max(root)->data;
    }
    void Insert(const E& x) {
        Insert(x, root);
    }
    void Remove(const E& x) {
        Remove(x, root);
    }
};

//Search
template<class E, class K>
BSTNode<E, K>* BST< E, K>::Find(const E& x, BSTNode< E, K>*& ptr)const {
    if (ptr == NULL) {
        return  NULL;
    }
    else if (x < ptr->data) {
        return Find(x, ptr->leftChild);
    }
    else if (x > ptr->data) {
        return Find(x, ptr->rightChild);
    }
    else {
        return ptr;//found 
    }
}

//非递归算法
//template<class E, class K>
//BSTNode<E, K>* BST<E, K>::Find(const E& x, BSTNode<E, K>*& ptr)const {
//    if (ptr != NULL) {
//        BSTNode<E, K>* temp = ptr;
//        while (temp != NULL) {
//            if (temp->data == x) {
//                return temp;//found
//            }
//            else if (temp->data < x) {
//                temp = temp->rightChild;
//            }
//            else if (temp->data > x) {
//                temp = temp->leftChild;
//            }
//        }
//    }
//    return NULL;
//}

//Insert
template<class E, class K>
bool BST<E, K>::Insert(const E& x, BSTNode<E, K>*& ptr) {
    if (ptr == NULL) {
        ptr = new BSTNode<E, K>(x);
        if (ptr == NULL) {
            std::cout << "Out of Space" << std::endl;
            exit(1);
        }
    }
    else if (x < ptr->data) {
        Insert(x, ptr->leftChild);
    }
    else if (x > ptr->data) {
        Insert(x, ptr->rightChild);
    }
    else {
        //repeated data is missed
        ;
    }
    return true;
}

//template<class E, class K>
//BST<E, K>::BST(E value) {
//    E& x;
//    root = NULL;
//    RefValue = value;
//    std::cout << "输入元素" << std::endl;
//    std::cin >> x;
//    while (x->data != RefValue) {
//        Insert(x, root);
//        std::cout << "继续输入" << std::endl;
//        std::cin >> x;
//    }
//}

//Remove
template<class E, class K>
bool BST<E, K>::Remove(const E& x, BSTNode<E, K>*& ptr) {
    BSTNode< E,  K>* temp;
    if (ptr != NULL) {
        if (x < ptr->data) {
            Remove(x, ptr->leftChild);
        }
        else if (x > ptr->data) {
            Remove(x, ptr->rightChild);
        }
        else if (ptr->leftChild != NULL && ptr->rightChild != NULL) {
            temp = ptr->rightChild;
            while (temp->leftChild != NULL) {
                temp = temp->leftChild;
            }
            ptr->data = temp->data;
            Remove(ptr->data, ptr->rightChild);
        }
        else {
            temp = ptr;
            if (ptr->leftChild != NULL) {
                ptr = ptr->leftChild;
            }
            else {
                ptr = ptr->rightChild;
            }
            delete temp;
            return true;
        }
    }
    return false;
}

//MakeEmpty
template<class E, class K>
void BST<E, K>::MakeEmpty(BSTNode<E, K>*& ptr) {
    if (ptr != NULL) {
        MakeEmpty(ptr->leftChild);
        MakeEmpty(ptr->rightChild);
        delete ptr;
    }
    return;
}

//PrintTree
template<class E, class K>
void BST<E, K>::PrintTree(BSTNode<E, K>* ptr)const {
    if (ptr != NULL) {
        std::cout << ptr->data << " ";
        PrintTree(ptr->leftChild); 
        PrintTree(ptr->rightChild);
    }
    return;
}

//Copy
template<class E, class K>
BSTNode<E, K>* BST<E, K>::Copy(const BSTNode<E, K>*& ptr) {
    if (ptr == NULL) {
        return NULL;
    }
    BSTNode<E, K>* newNode = new BSTNode<E, K>;
    newNode->data = ptr->data;
    newNode->leftChild = ptr->leftChild;
    newNode->rightChild = ptr->rightChild;
    return newNode;
}

//find the Min
template<class E, class K>
BSTNode<E, K>* BST<E, K>::Min(BSTNode<E, K>*& ptr)const {
    BSTNode<E, K>* min = ptr;
    while (min->leftChild != NULL) {
        min = min->leftChild;
    }
    return min;
}

//find the Max
template<class E, class K>
BSTNode<E, K>* BST<E, K>::Max(BSTNode<E, K>*& ptr)const {
    BSTNode<E, K>* max = ptr;
    while (max->rightChild != NULL) {
        max = max->rightChild;
    }
    return max;
}