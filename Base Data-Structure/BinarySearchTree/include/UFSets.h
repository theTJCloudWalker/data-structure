#pragma once

const int DefaultSize=10;

class UFSets{
public:
    UFSets(int s=DefaultSize);
    ~UFSets(){delete []parent;}
    const UFSets&operator=(UFSets const&Value);
    void Union(int Root1,int Root2);
    int Find(int x);
    int CollapsingFind(int i);
    void UnionByHeight(int Root1,int Root2);
    void WeightedUnion(int Root1,int Root2);
private:
    int *parent;
    int size;
};

UFSets::UFSets(int s){
    size=s;
    parent=new int [size+1];
    for(int i=0;i<=size;i++){
        parent[i]=-1;
    }
}

//递归
int UFSets::Find(int x){
    if(parent[x]<=0){
        return x;
    }
    else{
        return Find(parent[x]);
    }
}

void UFSets::Union(int Root1,int Root2){
    parent[Root2]=Root1;
}

void UFSets::WeightedUnion(int Root1,int Root2){
    int temp=parent[Root1]+parent[Root2];
    if(parent[Root2]<parent[Root1]){
        parent[Root1]=Root2;
        parent[Root2]=temp;
    }
    else{
        parent[Root2]=Root1;
        parent[Root1]=temp;
    }
}

int UFSets::CollapsingFind(int i){
    int j;
    for(j=i;parent[j]>=0;j=parent[j]){
        ;
    }
    while(i!=j){
        int temp=parent[i];
        parent[i]=j;
        i=temp;
    }
    return j;
}