#pragma once
#include<iostream>

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
    ~FamilyNode();

    void SetName(const std::string Name);
    void SetAge(int Age);
    void SetJunior(FamilyNode*Son);
    void SetSibling(FamilyNode*Bro);
    void SetSpouse(FamilyNode*Mate);//add husband or wife

private:
    FamilyNode*junior;//younger generation of the Node
    FamilyNode*sibling;//brothers and sisters
    FamilyNode*spouse;//husband or wife
    
    std::string name;
    bool mate;
    int age;
};



class FamilyTree{
public:
    FamilyTree();
    FamilyTree(const std::string Name);
    ~FamilyTree(){destroy(ancestor);};

    bool IsEmpty()const;
    void Destroy(FamilyNode*&Ancestor);

    void Insert(FamilyNode*new);
    void RemoveByName(const std::string Name);

    FamilyNode* SearchByName(const std::string Name);

    void SetChild(FamilyNode* Child);
    void SetSpouse(FamilyNode* Mate);
    void SetSibling(FamilyNode* Sibling);

    void ModifyName(const std::string NewName);
    
private:
    FamilyNode* ancestor;
    FamilyNode* SearchByName(FamilyNode*Ancestor,const std::string Name);
};

FamilyNode::FamilyNode(){
    junior=sibiling=spouse=NULL;
    name="NULL";
    mate=unknown;
    age=-1;
}

FamilyNode::FamilyNode(std::string Name){
    junior=sibiling=spouse=NULL;
    name=Name;
    mate=unknown;
    age=-1;
}

void FamilyNode::SetName(const std::string Name) {
    name=Name;
    return;
}

void FamilyNode::SetAge(int Age) {
    age=Age;
    return;
}

void FamilyNode::SetJunior(FamilyNode*Son){
    FamilyNode*ptr=junior;
    if(ptr==NULL){
        ptr=Son;
    }
    else{
       ptr->SetSibling(Son);
    }
    return;
}

void FamilyNode::SetSibling(FamilyNode*Bro){
    FamilyNode*ptr=sibling;
    //向右到底
    while(ptr!=NULL){
        ptr=ptr->sibling;
    }
    ptr=Bro;
    return;
}

void FamilyNode::SetSpouse(FamilyNode*Mate){
    if(mate==NULL){
        mate=Mate;
    }
    else{
        ;
    }
    return;
}

FamilyTree::FamilyTree(const std::string Name){
    ancestor=new FamilyTree(Name);
}

FamilyNode* FamilyTree::SearchByName(const std::string Name){
    return SearchByName(ancestor,Name);
}

void FamilyTree::Destroy(FamilyNode*&Ancestor){
    if(Ancestor!=NULL){
        Destroy(Ancestor->spouse);
        Destroy(Ancestor->sibling);
        Destroy(Ancestor->junior);
        delete ancestor;
    }
    return;
}

void FamilyTree::RemoveByName(const std::string Name){
    FamilyNode*ptr=SearchByName(Name);
    if(FamilyNode==NULL){
        std::cout<<"could not find"<<std::endl;
        return;
    }
    
    Destroy(ptr->spouse);
    Destroy(ptr->sibling);
    Destroy(ptr->junior);
    //uncertain
    Destroy(ptr);
    
}

FamilyNode* FamilyTree::SearchByName(FamilyNode*Ancestor,const std::string Name){
    FamilyNode*ptr=Ancestor;
    //查看自身
    if(Ancestor==NULL||Ancestor->name==Name){
        return Ancestor;//successfully found
    }
    //查看配偶
    if(Ancestor->spouse!=NULL&&Ancestor->spouse->name==Name){
        return Ancestor->spouse;//successfully found
    }
    //在兄弟姐妹中搜索
    ptr=SearchByName(ptr->sibling,Name);
    if(ptr!=NULL){
        return ptr;
    }
    //在后辈中搜索
    ptr=SearchByName(ptr->junior,Name);
    if(ptr!=NULL){
        return ptr;
    }
    //搜索失败
    return NULL;
}

void FamilyTree::SetChild(FamilyNode* Child){
    
}