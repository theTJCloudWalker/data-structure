#pragma once
#include<iostream>
#include"LinkedQueue.h"

template<class T> class BinaryTree;

template<class T> class BinaryTreeNode {
    friend class BinaryTree<T>;
public:
    BinaryTreeNode() :leftChild(NULL), rightChild(NULL) {}
    BinaryTreeNode(T item, BinaryTreeNode<T>* left = NULL, BinaryTreeNode<T>* right = NULL) :data(item), leftChild(left), rightChild(right) {}
    
    T GetData()const { return data; }
    BinaryTreeNode<T>* GetLeft()const {
        return leftChild;
    }
    BinaryTreeNode<T>* GetRight()const {
        return rightChild;
    }
    void SetData(const T& item) {
        data = item;
    }
    void SetLeft(BinaryTreeNode<T>* L) {
        leftChild = L;
    }
    void SetRight(BinaryTreeNode<T>* R) {
        rightChild = R;
    }

private:
    BinaryTreeNode<T>* leftChild, * rightChild;
    T data;
};

 
template<class T>
class BinaryTree {
public:
    BinaryTree() :root(NULL) { }
    BinaryTree(T value) :RefValue(value), root(NULL) { }
    BinaryTree(BinaryTreeNode<T>* s);
    ~BinaryTree() { destroy(root); }
    bool IsEmpty() {
        return (root == NULL) ? true : false;
    }
    BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current) {
        return (root == NULL || root == current) ? NULL : Parent(root, current);
    }
    BinaryTreeNode<T>* LeftChild(BinaryTreeNode<T>* current) {
        return (root != NULL) ? current->LeftChild : NULL;
    }
    BinaryTreeNode<T>* RightChild(BinaryTreeNode<T>* current) {
        return (root != NULL) ? current->RightChild : NULL;
    }
    // virtual int Insert(const T&item);
     //virtual int Find(const T&item)const;
     // T GetData()const;
    int Height() { return Height(root); }
    int Size() { return Size(root); }
    BinaryTreeNode<T>* GetRoot()const { return root; }
    void PreOrder(void(*visit)(BinaryTreeNode<T>* p)) {
        PreOrder(root, visit);
    }
    void InOrder(void(*visit)(BinaryTreeNode<T>* p)) {
        InOrder(root, visit);
    }
    void PostOrder(void(*visit)(BinaryTreeNode<T>p)) {
        PostOrder(root, visit);
    }
    void levelOrder(void(*visit)(BinaryTreeNode<T>* p));
    int Insert(const T item);
    BinaryTreeNode<T>* Find(T item)const;
    template<class Type>friend std::istream& operator>>(std::istream& in, BinaryTree<Type>& Tree);
    template<class Type>friend std::ostream& operator<<(std::ostream& out, BinaryTree<Type>& Tree);

//protected:
private:
    BinaryTreeNode<T>* root;
    T RefValue=0;
    void CreateBinaryTree(std::istream& in, BinaryTreeNode<T>*& subTree);
    bool Insert(BinaryTreeNode<T>*& subTree, const T item);
    void destroy(BinaryTreeNode<T>*& subTree);
    bool Find(BinaryTreeNode<T>*& subTree, const T& item);
    BinaryTreeNode<T>* Copy(BinaryTreeNode<T>* originode);
    int Height(BinaryTreeNode<T>* subTree)const;
    int Size(BinaryTreeNode<T>* subTree)const;
    BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* start, BinaryTreeNode<T>* current);
    BinaryTreeNode<T>* Find(BinaryTreeNode<T>* subTree, const T& item)const;

    // int Insert(BinaryTreeNode<T>*&current,const T&item);
    void Traverse(BinaryTreeNode<T>* current, std::ostream& out);
    void PreOrder(BinaryTreeNode<T>* subTree, void(*visit)(BinaryTreeNode<T>* p));
    void InOrder(BinaryTreeNode<T>* subTree, void(*visit)(BinaryTreeNode<T>* p));
    void PostOrder(BinaryTreeNode<T>* subTree, void(*visit)(BinaryTreeNode<T>* p));
    // int Find(BinaryTreeNode<T>*current,const T&item)const;
    // void destroy(BinaryTreeNode<T>*&subTree);
};

template<class T>
void BinaryTree<T>::destroy(BinaryTreeNode<T>*& subTree) {
    if (subTree != NULL) {
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        delete subTree;
    }
    return;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* subTree, BinaryTreeNode<T>* current) {
    if (subTree == NULL) {
        return NULL;
    }
    if (subTree->leftChild == current || subTree->rightChild == current) {
        return subTree;
    }
    BinaryTreeNode<T>* p;
    if ((p = Parent(subTree->leftChild, current)) != NULL) {
        return p;
    }
    else {
        return Parent(subTree->rightChild, current);
    }
}

template<class T>
int BinaryTree<T>::Insert(const T item) {
    Insert(root, item);
    return 1;//temp 
}

template<class T>
bool BinaryTree<T>::Insert(BinaryTreeNode<T>*& subTree, const T item) {
    if (subTree == NULL) {
        subTree = new BinaryTreeNode<T>(item);
        if (subTree == NULL) {
            std::cout << "内存分配出错" << std::endl;
            exit(1);
        }
        return true;
    }
    if (subTree->data > item) {
        Insert(subTree->leftChild, item);
    }
    else if(subTree->data<item){
        Insert(subTree->rightChild, item);
    }
    else {
        //repeated data is missed 
    }
    return true;
}

template<class T>
void  BinaryTree<T>::Traverse(BinaryTreeNode<T>* current, std::ostream& out) {
    if (current != NULL) {
        out << current->data << " ";
        Traverse(current->leftChild, out);
        Traverse(current->rightChild, out);
    }//PreOrder
}

template<class Type>
std::istream& operator>>(std::istream& in, BinaryTree<Type>& Tree) {
    Type item;
    std::cout << "构造二叉树";
    std::cout << "输入数据（用" << Tree.RefValue << "结束）：";
    in >> item;
    while (item != Tree.RefValue) {
        Tree.Insert(item);
        std::cout << "输入数据（用" << Tree.RefValue << "结束）：";
        in >> item;
    }
    return in;
}

template<class Type>
std::ostream& operator<<(std::ostream& out, BinaryTree<Type>& Tree) {
    out << "二叉树的前序遍历." << std::endl;
    Tree.Traverse(Tree.root,out);
    //Tree.PreOrder(Tree.root,std::cout);
    out << std::endl;
    return out;
}

/*template<class T>
void BinaryTree<T>::InOrder(){
        InOrder(root);
}*/

template<class T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* subTree, void(*visit)(BinaryTreeNode<T>* p)) {
    if (subTree != NULL) {
        InOrder(subTree->leftChild, visit);
        //visit(subTree);
        InOrder(subTree->rightChild, visit);
    }
}

template<class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* subTree, void(*visit)(BinaryTreeNode<T>* p)) {
    if (subTree != NULL) {
        visit(subTree);
        PreOrder(subTree->leftChild, visit);
        PreOrder(subTree->rightChild, visit);
    }
}

template<class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* subTree, void(*visit)(BinaryTreeNode<T>* p)) {
    if (subTree != NULL) {
        PostOrder(subTree->leftChild, visit);
        PostOrder(subTree->rightChild, visit);
        visit(subTree);
    }
}

template<class T>
int BinaryTree<T>::Size(BinaryTreeNode<T>* subTree) const {
    if (subTree == NULL) {
        return 0;
    }
    else {
        return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
    }
}

template<class T>
int BinaryTree<T>::Height(BinaryTreeNode<T>* subTree) const {
    if (subTree == NULL) {
        return 0;
    }
    else {
        int i = Height(subTree->leftChild);
        int j = Height(subTree->rightChild);
        return i < j ? j + 1 : i + 1;
    }
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Copy(BinaryTreeNode<T>* orignode) {
    if (orignode == NULL) {
        return NULL;
    }
    BinaryTreeNode<T>* temp = new BinaryTreeNode<T>;
    temp->data = orignode->data;
    temp->leftChild = orignode->leftChild;
    temp->rightChild = orignode->rightChild;
    return temp;
}

template<class T>
int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t) {
    return (equal(s.root, t.root)) ? true : false;
}

template<class T>
bool equal(BinaryTreeNode<T>* a, BinaryTreeNode<T>* b) {
    if (a == NULL && b == NULL) {
        return true;
    }
    if ((a != NULL) && (b != NULL) && a->data == b->data && equal(a->leftChild, b->leftChild) && equal(a->rightChild, b->rightChild)) {
        return true;
    }
    else {
        return false;
    }
}

template<class T>
void BinaryTree<T>::CreateBinaryTree(std::istream& in, BinaryTreeNode<T>*& subTree) {
    T item;
    if (!in.eof()) {
        in >> item;
        if (item != RefValue) {
            subTree = new BinaryTreeNode<T>(item);
            if (subTree == NULL) {
                std::cerr << "存储分配错误" << std::endl;
                exit(1);
            }
            CreateBinaryTree(in, subTree->leftChild);
            CreateBinaryTree(in, subTree->rightChild);
        }
    }
}

template<class T>
void PrintBinaryTree(BinaryTreeNode<T>* BT) {
    if (BT != NULL) {
        std::cout << BT->data;
        if (BT->leftChild != NULL || BT->rightChild != NULL) {
            std::cout << "(";
            PrintBinaryTree(BT->leftChild);
            std::cout << ", ";
            if (BT->rightChild != NULL) {
                PrintBinaryTree(BT->rightChild);
            }
            std::cout << ")";
        }
    }
}

template<class T>
void BinaryTree<T>::levelOrder(void(*visit)(BinaryTreeNode<T>*p)){
    LinkedQueue<BinaryTreeNode<T>*>Q;
    BinaryTreeNode<T>* p = root;
    Q.EnQueue(p);
    while (!Q.IsEmpty()) {
        Q.DeQueue(p);
        visit(p);
        if (p->leftChild != NULL) {
            Q.EnQueue(p->leftChild);
        }
        if (p->rightChild != NULL) {
            Q.EnQueue(p->rightChild);
        }
    }
}