#pragma once
#include<iostream>
#include <stack>

#define INF 2147483647//代表正无穷的值
//#include"Graph.h"
//用邻接矩阵表示的图定义

const int DefaultVertices = 10;//最多顶点数

//存放最小生成树
template<class T, class E>
struct Edges {
    T data1, data2;
    E weight;
};

template<class T, class E>
class Graphmtx {
    template<class T1, class E1>friend std::istream& operator>>(std::istream& in, Graphmtx<T1, E1>& G);
    template<class T1, class E1>friend std::ostream& operator<<(std::ostream& out, Graphmtx<T1, E1>& G);
public:
    Graphmtx(int sz = DefaultVertices);//构造函数
    ~Graphmtx() { delete[]VerticesList; delete[]Edge; };//析构函数

    T GetValue(int i)//取顶点i的值，不合理返回0
    {
        return i >= 0 && i <= numOfVertices ? VerticesList[i] : NULL;
    }
    E GetWeight(int v1, int v2)//取边<v1,v2>的权值
    {
        return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
    }
    int GetFirstNeighbor(int v);//取顶点v的第一个邻接顶点
    int GetNextNeighbor(int v, int w);//取顶点v的邻接顶点w的下一个邻接顶点
    int Find(T vertex) {
        return GetVertexPos(vertex);
    }
    int NumberOfVertices() {
        return numOfVertices;
    }
    int NumberOfEdges() {
        return numOfEdges;
    }

    bool InsertVertex(const T vertex);//插入顶点vertex
    bool InsertEdge(int v1, int v2, E cost);//插入边<v1,v2>,权值为cost

    bool RemoveVertex(int v);//删去顶点vertex和所有相关联的边
    bool RemoveEdge(int v1, int v2);//删去边<v1,v2>

    void Prim(T start);

private:
    int maxVertices;
    int numOfEdges;
    int numOfVertices;
    T* VerticesList; //顶点表
    E** Edge; //邻接矩阵
    int GetVertexPos(T vertex) {
        //给出vertex在图中的位置
        for (int i = 0; i < numOfVertices; i++) {
            if (VerticesList[i] == vertex) {
                return i;
            }
        }
        return -1;
    }
};

template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz) {
    //构造函数
    maxVertices = sz; numOfVertices = 0; numOfEdges = 0;

    VerticesList = new T[maxVertices];
    Edge = (int**)new int* [maxVertices];
    for (int i = 0; i < maxVertices; i++) {
        Edge[i] = new int[maxVertices];
    }
    for (int i = 0; i < maxVertices; i++) {
        for (int j = 0; j < maxVertices; j++) {
            Edge[i][j] = (i == j) ? 0 : INF;
        }
    }
}

template<class T, class E>
int Graphmtx<T, E>::GetFirstNeighbor(int v) {
    //取顶点v的第一个邻接顶点
    if (v != -1) {
        for (int col = 0; col < numOfVertices; col++) {
            if (Edge[v][col] > 0 && Edge[v][col] < INF) {
                return col;
            }
        }
    }
    return -1;
}

template<class T, class E>
int Graphmtx<T, E>::GetNextNeighbor(int v, int w) {
    if (v != -1 && w != -1) {
        for (int col = w + 1; col <= numOfVertices; col++) {
            if (Edge[v][col] > 0 && Edge[v][col] < INF) {
                return col;
            }
        }
    }
    return -1;
}

template<class T, class E>
bool Graphmtx<T, E>::InsertVertex(const T vertex) {
    if (numOfVertices == maxVertices) {
        return false;
    }
    VerticesList[numOfVertices++] = vertex;
    return true;
}

template<class T, class E>
bool Graphmtx<T, E>::RemoveVertex(int v) {
    if (v < 0 || v >= maxVertices) {
        return false;//v 不在图中
    }
    if (numOfVertices == 1) {
        return false;//只有一个顶点，不删除
    }

    VerticesList[v] = VerticesList[numOfVertices - 1];//在顶点表中删除该顶点
    for (int i = 0; i < numOfVertices; i++) {
        if (Edge[i][v] > 0 && Edge[i][v] < INF) {
            numOfEdges--;//删除与v相关联边数
        }
    }
    for (int i = 0; i < numOfVertices; i++) {
        Edge[i][v] = Edge[i][numOfVertices - 1];
    }
    numOfVertices--;
    for (int i = 0; i < numOfVertices; i++) {
        Edge[v][i] = Edge[numOfVertices][i];
    }
    return true;
}

template<class T, class E>
bool Graphmtx<T, E>::InsertEdge(int v1, int v2, E cost) {
    if (v1 > -1 && v1<numOfVertices &&
        v2>-1 && v2 < numOfVertices &&
        Edge[v1][v2] == INF) {
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numOfEdges++;
        return true;
    }
    return false;
}

template<class T, class E>
bool Graphmtx<T, E>::RemoveEdge(int v1, int v2) {
    if (v1 > -1 && v1<numOfVertices &&
        v2>-1 && v2 < numOfVertices &&
        Edge[v1][v2]>0 && Edge[v1][v2] < INF) {
        Edge[v1][v2] = Edge[v2][v1] = INF;
        numOfEdges--;
        return true;
    }
    else {
        return false;
    }
}

template<class T1, class E1>
std::istream& operator>>(std::istream& in, Graphmtx<T1, E1>& G) {
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
    std::cout << std::endl;
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
std::ostream& operator<<(std::ostream& out, Graphmtx<T1, E1>& G) {
    int w, vertexNum = G.NumberOfVertices(), edgeNum = G.NumberOfEdges();
    out << vertexNum << "," << edgeNum << std::endl;
    for (int i = 0; i < vertexNum; i++) {
        for (int j = i+1; j < vertexNum; j++) {
            w = G.GetWeight(i, j);
            if (w > 0 && w < INF) {
                out << "(" << G.GetValue(i) << "," << G.GetValue(j) << "," << w << ")" << std::endl;
            }
        }
    }
    return out;
}

template<class T, class E>
void Graphmtx<T, E>::Prim(T start) {
    int pos = Find(start);
    if (pos == -1) {
        std::cout << "could not find " << start << std::endl;
        return;
    }

    std::stack<int> opStack;
    int count = numOfVertices;
    int min = -1;
    int vertex2 = -1, vertex1 = -1;
    Edges<T, E>* result = new Edges<T, E>[count];
    bool* visited = new bool[count];

    for (int i = 0; i < count; i++) {
        visited[i] = false;
    }

    opStack.push(pos);
    visited[pos] = true;

    for (int i = 1; i < count; i++) {
        min = INF;
        vertex2 = -1;
        while (!opStack.empty()) {
            int vertex = opStack.top();
            opStack.pop();
            for (int j = 0; j < numOfVertices; j++) {
                int cost = GetWeight(vertex, j);
                if (visited[j] == false && cost < INF) {
                    if (min > cost) {
                        min = cost;
                        vertex2 = j;
                        vertex1 = vertex;
                    }
                }
            }

        }
        if (vertex2 != -1) {
            visited[vertex2] = true;
            for (int j = 0; j < count; j++) {
                if (visited[j] == true) {
                    opStack.push(j);
                }
            }
            result[i].data1 = VerticesList[vertex1];
            result[i].data2 = VerticesList[vertex2];
            result[i].weight = min;
        }
    }

    for (int i = 1; i < count ; i++) {
        std::cout << result[i].data1 << " " << result[i].data2 << " " << result[i].weight << std::endl;
    }
    return;
}