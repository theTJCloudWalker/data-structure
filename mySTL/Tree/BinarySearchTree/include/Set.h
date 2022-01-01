#pragma once

#include<assert.h>

const int DefaultSize=100;

class Set{
private:
    int *bitVector;
    int MaxSize;
public:
    Set(int MaxSetSize=DefaultSize);
    ~Set(){delete []bitVector;}
    void MakeEmpty();//为每一位置零
    int AddMember(const int x);
    int DeleteMember(const int x);
    Set&operator=(const Set&right);
    Set&operator+(const Set&right);
    Set&operator-(const Set&right);
    Set&operator*(const Set&right);
    int Contains(const int x);
    int SubSet(Set&right);
    int operator==(const Set&right);
};

void Set::MakeEmpty(){
    for(int i=0;i<MaxSize;i++){
        bitVector[i] = 0;
    }
    return;
}

Set::Set(int MaxSetSize):MaxSize(MaxSetSize){
    assert(MaxSize>0);
    bitVector=new int[MaxSize];
    assert(bitVector!=0);
    for(int i=0;i<MaxSize;i++){
        bitVector[i]=0;
    }
}

int Set::AddMember(const int x){
    assert(x>=0&&x<MaxSize);
    if(!bitVector[x]){
        bitVector[x]=1;
        return 1;
    }
    return 0;
}

int Set::DeleteMember(const int x){
    assert(x>=0&&x<MaxSize);
    if(bitVector[x]){
        bitVector[x]=0;
        return 1;
    }
    return 0;
}

Set&Set::operator=(const Set&right){
    assert(MaxSize==right.MaxSize);
    for(int i=0;i<MaxSize;i++){
        bitVector[i]=right.bitVector[i];
    }
    return *this;
}

Set&Set::operator+(const Set&right){
    assert(MaxSize==right.MaxSize);
    for(int i=0;i<MaxSize;i++){
        bitVector[i]=right.bitVector[i]||bitVector[i];
    }
    return *this;
}

Set&Set::operator-(const Set&right){
    assert(MaxSize==right.MaxSize);
    for(int i=0;i<MaxSize;i++){
        bitVector[i]=!right.bitVector[i]&&bitVector[i];
    }
    return *this;
}

Set&Set::operator*(const Set&right){
    assert(MaxSize==right.MaxSize);
    for(int i=0;i<MaxSize;i++){
        bitVector[i]=right.bitVector[i]&&bitVector[i];
    }
    return *this;
}

int Set::Contains(const int x){
    assert(x>=0&&x<MaxSize);
    return bitVector[x];
}

int Set::operator==(const Set&right){
    assert(MaxSize==right.MaxSize);
    for(int i=0;i<MaxSize;i++){
        if(bitVector[i]!=right.bitVector[i]){
            return 0;
        }
    }
    return 1;
}

int Set::SubSet(Set&right){
    assert(MaxSize==right.MaxSize);
    for(int i=0;i<MaxSize;i++){
        if(bitVector[i]&&!right.bitVector[i]){
            return 0;
        }
    }
    return 1;
}