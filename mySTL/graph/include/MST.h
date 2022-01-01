#pragma once
#define MAXINT 2147483647

class MinSpanTree;

class MSTEdgeNode{
    friend class MinSpanTree;
private:
    int tail,head;
    float cost;
}

class MinSpanTree{
public:
    MinSpanTree(int sz=numOfVertices-1):MaxSize(sz),n(0){
        edgevalue=new MSTEdgeNode[MaxSize];
    }
    int Insert(MSTEdgeNode& item);
protected:
    MSTEdgeNode*edgevalue;
    int MaxSize,n;
}

void Graph<string,float>::Kruskal(MinSpanTree& T){
    MSTEdgeNode e;
    MinHeap
}