#pragma once
#include<iostream>
#include"LinkedStack.h"//for Prim()

const int MaxWeight = 2147483647;//代表正无穷的值
const int DefaultVertices = 10;//最多顶点数

template<class T, class E>
struct Edge {
    int dest;
    E cost;//权值
    Edge<T, E>* link;//指向下一条边的指针
    Edge() :dest(-1), cost(0), link(NULL) {}
    Edge(int num, E weight) : dest(num), cost(weight), link(NULL) {}//构造函数
    bool operator!=(const Edge<T, E>& R)const {
        return (dest != R.dest) ? true : false;
    }
};

//存放最小生成树的边
template<class T,class E>
struct Edges{
    T data1;
    T data2;
    E weight;
    Edges();
    Edges(T start,T end,E Weight) : data1(start), data2(end),weight(Weight){}
    ~Edges();
};

template<class T, class E>
struct Vertex {
    T data;
    Edge<T, E>* adj;//边链表的头指针
};

template<class T, class E>
class Graphlink {
    template<class T1, class E1>friend std::istream& operator>>(std::istream& in, Graphlink<T1, E1>& G);
    template<class T1, class E1>friend std::ostream& operator<<(std::ostream& out, Graphlink<T1, E1>& G);
public:
    Graphlink(int sz = DefaultVertices);
    ~Graphlink();

    T GetValue(int i) const
    {
        return (i >= 0 && i < numOfVertices) ? NodeTable[i].data : 0;
    }
    E GetWeight(int v1, int v2);
    int GetFirstNeighbor(int v);
    int GetNextNeighbor(int v, int w);

    bool InsertVertex(const T vertex);
    bool RemoveVertex(int v);
    bool InsertEdge(int v1, int v2, E cost);
    bool RemoveEdge(int v1, int v2);

    int Find(T vertex) {
        return GetVertexPos(vertex);
    }
    int NumberOfVertices() {
        return numOfVertices;
    }
    int NumberOfEdges() {
        return numOfEdges;
    }

    //Function
    Edges<T, E>* Prim(T start);
    void DestroyPrim();

private:
    int maxVertices;
    int numOfEdges;
    int numOfVertices;
    Vertex<T, E>* NodeTable;
    int GetVertexPos(const T vertex) {
        for (int i = 0; i < numOfVertices; i++) {
            if (NodeTable[i].data == vertex) {
                return i;
            }
        }
        return -1;
    }
};

template<class T, class E>
Graphlink<T, E>::Graphlink(int sz) {
    maxVertices = sz; numOfVertices = 0; numOfEdges = 0;
    NodeTable = new Vertex<T, E>[maxVertices];
    if (NodeTable == NULL) {
        std::cerr << "存储分配错误" << std::endl;
        exit(1);
    }
    for (int i = 0; i < maxVertices; i++) {
        NodeTable[i].adj = NULL;
    }
}

template<class T, class E>
Graphlink<T, E>::~Graphlink() {
    for (int i = 0; i < numOfVertices; i++) {
        Edge<T, E>* p = NodeTable[i].adj;
        while (p != NULL) {
            NodeTable[i].adj = p->link;
            delete p;
            p = NodeTable[i].adj;
        }
    }
    delete[] NodeTable;
}

template<class T, class E>
int Graphlink<T, E>::GetFirstNeighbor(int v) {
    if (v != -1) {
        Edge<T, E>* p = NodeTable[v].adj;
        if (p != NULL) {
            return p->dest;
        }
    }
    return -1;
}

template<class T, class E>
int Graphlink<T, E>::GetNextNeighbor(int v, int w) {
    if (v != -1) {
        Edge<T, E>* p = NodeTable[v].adj;
        while (p != NULL && p->dest != w) {
            p = p->link;
        }
        if (p != NULL && p->link != NULL) {
            return p->link->dest;
        }
    }
    return -1;
}

template<class T, class E>
E Graphlink<T, E>::GetWeight(int v1, int v2) {
    if (v1 != -1 && v2 != -1) {
        Edge<T, E>* p = NodeTable[v1].adj;
        while (p != NULL && p->dest != v2) {
            p = p->link;
        }
        if (p != NULL) {
            return p->cost;
        }
    }
    return 0;//边不存在
}

template<class T, class E>
bool Graphlink<T, E>::InsertVertex(const T vertex) {
    if (numOfVertices == maxVertices) {
        return false;
    }
    NodeTable[numOfVertices].data = vertex;
    numOfVertices++;
    return true;
}

template<class T, class E>
bool Graphlink<T, E>::RemoveVertex(int v) {
    if (numOfVertices == 1 || v < 0 || v >= numOfVertices) {
        //表空或顶点号超出范围
        return false;
    }
    Edge<T, E>* p, * s, * t;
    int i;
    while (NodeTable[v].adj != NULL) {
        p = NodeTable[v].adj;//取邻接顶点k
        s = NodeTable[p->dest].adj;//找对称存放的边结点
        t = NULL;
        while (s != NULL && s->dest != v) {
            t = s;
            s = s->link;
        }
        if (s != NULL) {
            if (t == NULL) {
                NodeTable[v].adj = s->link;
            }
            else {
                t->link = s->link;
            }
            delete s;
        }
        NodeTable[v].adj = p->link;
        delete p;
        numOfEdges--;
    }
    numOfVertices--;
    NodeTable[v].data = NodeTable[numOfVertices].data;
    p = NodeTable[v].adj = NodeTable[numOfVertices].adj;
    while (p != NULL) {
        s = NodeTable[p->dest].adj;
        while (s != NULL) {
            if (s->dest == numOfVertices) {
                s->dest = v;
                break;
            }
            else {
                s = s->link;
            }
        }
    }
    return true;
}

template<class T, class E>
bool Graphlink<T, E>::InsertEdge(int v1, int v2, E weight) {
    if (v1 >= 0 && v1 <= numOfVertices && v2 >= 0 && v2 <= numOfVertices ) {
        Edge<T, E>* q, * p = NodeTable[v1].adj;
        while (p != NULL && p->dest != v2) {
            p = p->link;
        }
        if (p != NULL) {
            return false;
        }
        p = new Edge<T, E>;
        q = new Edge<T, E>;
        p->dest = v2;
        p->cost = weight; 
        p->link = NodeTable[v1].adj;
        NodeTable[v1].adj = p;
        q->dest = v1;
        q->cost = weight;
        q->link = NodeTable[v2].adj;
        NodeTable[v2].adj = q;
        numOfEdges++;
        return true;
    }
    return false;
}

template<class T, class E>
bool Graphlink<T, E>::RemoveEdge(int v1, int v2) {
    if (v1 != -1 && v2 != -1) {
        Edge<T, E>* p = NodeTable[v1].adj, * q = NULL, * s = p;
        while (p != NULL && p->dest != v2) {
            q = p;
            p = p->link;
        }
        if (p != NULL) {
            if (p == s) {
                NodeTable[v1].adj = p->link;
            }
            else {
                q->link = p->link;
            }
            delete p;
        }
        else {
            return false;
        }
        p = NodeTable[v2].adj;
        q = NULL;
        s = p;
        while (p->dest != v1) {
            q = p;
            p = p->link;
        }
        if (p == s) {
            NodeTable[v2].adj = p->link;
        }
        else {
            q->link = p->link;
        }
        delete p;
        return true;
    }
    return false;
}

template<class T1, class E1>
std::istream& operator>>(std::istream& in, Graphlink<T1, E1>& G) {
    int vertexNum, edgeNum;
    T1 e1, e2;
    E1 weight;
    std::cout << "输入顶点数与边数" << std::endl;
    in >> vertexNum >> edgeNum;
    std::cout << "请依次输入顶点  " << std::endl;
    for (int i = 0; i < vertexNum; i++) {
        in >> e1;
        G.InsertVertex(e1);
    }
    int j, k;
    std::cout << "请依次输入边" << std::endl;
    for (int i = 0; i < edgeNum; i++) {
        in >> e1 >> e2 >> weight;
        j = G.Find(e1);
        k = G.Find(e2);
        G.InsertEdge(j, k, weight);
    }
    return in;
}

template<class T1, class E1>
std::ostream& operator<<(std::ostream& out, Graphlink<T1, E1>& G) {
    int w, vertexNum = G.NumberOfVertices(), edgeNum = G.NumberOfEdges();
    out << vertexNum << "," << edgeNum << std::endl;
    for (int i = 0; i < vertexNum; i++) {
        for (int j = i + 1; j < vertexNum; j++) {
            w = G.GetWeight(i, j);
            if (w > 0 && w < MaxWeight) {
                out << "(" << G.GetValue(i) << "," << G.GetValue(j) << "," << w << ")" << std::endl;
            }
        }
    }
    return out;
} 

template<class T, class E>
Edges<T, E>* Graphlink<T, E>::Prim(T start){
    int pos=GetVertexPos(start);

    if(pos==-1){ 
        return NULL;
    }

    bool* visited=new bool[numOfVertices];
    int* order=new int[numOfVertices];//记录顺序
    Edges<T,E>* result=new Edges[numOfVertices];

    for(int i = 0; i < numOfVertices; i++){
        visited[i]=false;//默认都未访问过
    }
    visited[pos]=true;
    int count=numOfVertices;
    T data1;

    LinkedStack<Vertex*> opStack;
    opStack.Push(NodeTable[pos]); 

    for(int i=0; i<count; i++){
        Edge<T, E>*min;
        while(!opStack.IsEmpty()){
            Vertex<T, E>*p=new Vertex<T, E>;
            opStack.Pop(p);
            Edge<T, E>*ptr=p->adj;
            if(min==NULL){
                min=ptr;//初始化最小边
                data1=p->data;
            }
            while(ptr!=NULL){
                if(ptr->cost<min->cost&&visited[GetVertexPos(ptr->dest)]){
                    min=ptr;
                    data1=p->data;
                }
                ptr=ptr->link;
            }
            delete p;
        }
        pos=GetVertexPos(data1);
        order[i]=pos;
        visited[pos]=true;
        result[i]->data1=data1;
        result[i]->data2=data2;
        result[i]->weight=min->weight;
        for(int j=0; j<i;j++){
            opStack.Push(NodeTable[order[j]]);
        }
    }
    return result;
}

template<class T,class E>
void Graphlink<T, E>::DestroyPrim(){
    delete[]result;
}