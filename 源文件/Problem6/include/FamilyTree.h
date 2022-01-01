#pragma once
#include<iostream>
#include"LinkedStack.h"

class FamilyTree;

class FamilyNode{
public:
    friend class FamilyTree;

    enum Mate{
        male=0,
        female,
        unknown,
    };

    FamilyNode();
    FamilyNode(std::string name);
    FamilyNode(FamilyNode* s);
    ~FamilyNode() { };

    void SetName(const std::string Name);
    void SetAge(int Age);

    void InsertJunior(FamilyNode*Son);
    void InsertSibling(FamilyNode*Bro);
    void SetSpouse(FamilyNode*Mate);//add husband or wife

    void PrintJunior();

private:
    FamilyNode*junior;//younger generation of the Node
    FamilyNode*sibling;//brothers and sisters
    FamilyNode*spouse;//husband or wife

    int numOfSibling = 0, numOfJunior = 0;
    
    std::string name;
    Mate mate;
    int age;
};



class FamilyTree{
public:
    FamilyTree();
    FamilyTree(const std::string Name);
    ~FamilyTree(){Destroy(ancestor);};

    bool IsEmpty()const;
    void Destroy(FamilyNode*&Ancestor);

    void Insert(FamilyNode* newNode);
    void RemoveByName(const std::string Name);

    FamilyNode* SearchByName(const std::string Name);
    FamilyNode* GetParent(const std::string Name);

    void InsertChild(std::string Name, FamilyNode* Child);
    void SetSpouse(std::string Name, FamilyNode* Mate);
    void InsertSibling(std::string Name, FamilyNode* Sibling);


    void ModifyName(const std::string NewName);
    
private:
    FamilyNode* ancestor;

    FamilyNode* SearchByName(FamilyNode*Ancestor,const std::string Name);
    FamilyNode* GetParent(FamilyNode* Ancestor, const std::string Name);
};

FamilyNode::FamilyNode(){
    junior=sibling=spouse=NULL;
    name="NULL";
    mate=unknown;
    age=-1;
}

FamilyNode::FamilyNode(std::string Name){
    junior=sibling=spouse=NULL;
    name=Name;
    mate=unknown;
    age=-1;
}

FamilyNode::FamilyNode(FamilyNode* s) {
    junior = s->junior;
    sibling = s->sibling;
    spouse = s->spouse;
    name = s->name;
    mate = s->mate;
    age = s->age;
}

void FamilyNode::SetName(const std::string Name) {
    name=Name;
    return;
}

void FamilyNode::SetAge(int Age) {
    age=Age;
    return;
}

void FamilyNode::InsertJunior(FamilyNode*Son){
    if(junior==NULL){
        junior=Son;
    }
    else{
       junior->InsertSibling(Son);
    }
    return;
}

void FamilyNode::InsertSibling(FamilyNode*Bro){
    //the first sibling
    if (sibling == NULL) {
        sibling = Bro;
        return;
    }
    
    FamilyNode* ptr = sibling;
    while (ptr->sibling != NULL) {
        ptr = ptr->sibling;
    }
    ptr->sibling = Bro;
    return;
}

void FamilyNode::SetSpouse(FamilyNode*Mate){
    if(spouse==NULL){
        spouse=Mate;
    }
    else{
        ;
    }
    return;
}

void FamilyNode::PrintJunior() {
    //(没有直接子女)||(没有配偶)||(配偶也没有直接子女)
    if (junior == NULL||(spouse!=NULL&&spouse->junior==NULL)) {
        std::cout << "Zero child!" << std::endl;
        return;
    }

    std::cout << name << "的第一代子孙是:" << std::endl;
    FamilyNode* ptr = junior;
    while (ptr != NULL) {
        std::cout << ptr->name << "  ";
        ptr = ptr->sibling;
    }
    std::cout << std::endl;
    return;
}

FamilyNode* FamilyTree::GetParent(const std::string Name) {
    if (ancestor->name == Name) {
        return NULL;//temp
    }
    else {
        return GetParent(ancestor, Name);
    }
}

FamilyNode* FamilyTree::GetParent(FamilyNode* Ancestor, const std::string Name) {
    FamilyNode* ptr = ancestor;
    LinkedStack<FamilyNode*> t,*s=&t;
    s->Push(ptr);
    while (!s->IsEmpty()) {
        s->getTop(ptr);

        if (ptr->spouse != NULL&& ptr->spouse->name == Name) {
           return ptr;
        }

        if (ptr->junior != NULL) {
            if (ptr->junior->name == Name) {
                return ptr;
            }
            else {
                s->Push(ptr->junior);
            }
        }
        if (ptr->sibling != NULL) {
            if (ptr->sibling->name == Name) {
                return ptr;
            }
            else {
                s->Push(ptr->sibling);
            }
        }
    }
    //搜索失败
    return NULL;
}

FamilyTree::FamilyTree(const std::string Name){
    ancestor=new FamilyNode(Name);
}

FamilyNode* FamilyTree::SearchByName(const std::string Name){
    return SearchByName(ancestor,Name);
}

bool FamilyTree::IsEmpty() const{
    return ancestor != NULL ? true : false;
}

void FamilyTree::Destroy(FamilyNode*& Ancestor){
    if(Ancestor!=NULL){
        Destroy(Ancestor->spouse);
        Destroy(Ancestor->sibling);
        Destroy(Ancestor->junior);
        delete Ancestor;
        Ancestor = NULL;
    }
    return;
}

void FamilyTree::RemoveByName(const std::string Name){
    FamilyNode*ptr=SearchByName(Name);
    if(ptr==NULL){
        std::cout<<"could not find"<<Name<<std::endl;
        return;
    }
    
    //case1:the node to delete is a leaf node
    ptr->PrintJunior();
    if (ptr == ancestor) {
        Destroy(ptr->sibling);
        Destroy(ptr->junior);
        Destroy(ptr->spouse);
        std::cout << "All Child Removed,the ancestor " << ptr->name << " cannot be deleted,but you can change the ancestor by modifying his data" << std::endl;
    }
    else if(ptr->sibling==NULL){
        Destroy(ptr);
    }
    else {
        //case2:the node to delete has sibling as rightChild
        FamilyNode* parentNode = GetParent(Name);
        parentNode->sibling = parentNode->sibling->sibling;
        ptr->sibling = NULL;
        Destroy(ptr);
    }
    return;
}

FamilyNode* FamilyTree::SearchByName(FamilyNode*Ancestor,const std::string Name){
    FamilyNode*ptr;
    //查看自身
    if(Ancestor==NULL||Ancestor->name==Name){
        return Ancestor;//successfully found
    }
    //查看配偶
    if(Ancestor->spouse!=NULL&&Ancestor->spouse->name==Name){
        return Ancestor->spouse;//successfully found
    }
    //在兄弟姐妹中搜索
    ptr=SearchByName(Ancestor->sibling,Name);
    if(ptr!=NULL){
        return ptr;
    }
    //在后辈中搜索
    ptr=SearchByName(Ancestor->junior,Name);
    if(ptr!=NULL){
        return ptr;
    }
    //搜索失败
    return NULL;
}

void FamilyTree::InsertChild(std::string Name, FamilyNode* Child){
    FamilyNode*ptr=SearchByName(Name);
    if(ptr!=NULL){
        ptr->numOfJunior++;
        ptr->InsertJunior(Child);
    }
    else{
        std::cout << "could not find " << Name << std::endl;
    }
    return;
}

void FamilyTree::InsertSibling(std::string Name, FamilyNode*Sibling){
    FamilyNode*ptr=SearchByName(Name);
    if(ptr!=NULL){
        ptr->numOfSibling++;
        ptr->InsertSibling(Sibling);
    }
    else{
        std::cout << "could not find " << Name << std::endl;
    }
    return;
}


