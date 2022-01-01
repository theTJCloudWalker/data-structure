#pragma once
//图的模板基类

const int MaxWeight = 2147483647;//代表正无穷的值
const int DefaultVertices=10;//最多顶点数

template<class NameType,class DistType>
class Graph{
private:
    int maxVertices;
    int numOfEdges;
    int numOfVertices;
    
    int GetVertexPos(const NameType&vertx);
public:
    Graph(int sz=DefaultVertices);
    ~Graph();

    bool GraphEmpty()const{
        return numOfEdges==0?true:false;
    }
    bool GraphFull()const{
        if((numOfVertices==DefaultVertices)||
           (numOfEdges==DefaultVertices*(DefaultVertices-1)/2)){
            return true;
        }
        else{
            return false;
        }
    }
    int NumberOfVertices(){
        return numOfVertices;
    }
    int NumberOfEdges(){
        return numOfEdges;
    }
    virtual NameType GetValue(int i);//返回顶点i的值，不合理返回0
    virtual DistType GetWeight(int v1,int v2);//取边<v1,v2>上的权值
    virtual int GetFirstNeighbor(int v);//取顶点v的第一个邻接顶点
    virtual int GetNextNeightbor(int v1,int v2);//取邻接顶点v2的下一个邻接顶点
    virtual bool InsertVertex(NameType&vertex);//插入一个顶点vertex
    virtual bool InsertEdge(int v1,int v2,DistType weight);//插入边<v1,v2>,权为weight
    virtual bool RemoveVertex(int v);//删去顶点v和所有相关联边
    virtual bool RemoveEdge(int v1,int v2);//删去边<v1,v2>
};
