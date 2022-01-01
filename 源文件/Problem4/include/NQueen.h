#pragma once
#include<iostream>
#include"math.h"
//#include"LinkedStack.h"
#define MaxSize 100

const int MaxN=30;

int N=0;//num of the queen 
long long totalSolutions=0;//num of the total solutions
bool curVisited[MaxN];//if the cur is occupied by a queen
bool diagonal_vis[2][2*MaxN-1];//对角线上是否存在queen
int q[MaxN];

void printSolution(int q[]){
    for(int i=1;i<N+1;i++){
        for(int j=1;j<N+1;j++){
            if(j==q[i]){
                printf("X ");
            }
            else{
                printf("# ");
            }
        }
        std::cout<<std::endl;
    }
}

void print(int q[]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(j==q[i]){
                printf("X ");
            }
            else{
                printf("# ");
            }
        }
        std::cout<<std::endl;
    }
}

//n皇后递归算法
void Queen(int cur){
    if(cur==N){
        totalSolutions++;//解决方法计数

        print(q);//打印解法               
        std::cout<<std::endl;
        return;
    }
    for(int i=0;i<N;i++){
        //满足条件时递归
        if(!curVisited[i]&&!diagonal_vis[1][N+cur-i-1]&&!diagonal_vis[0][cur+i]){
            curVisited[i]=diagonal_vis[1][N+cur-i-1]=diagonal_vis[0][cur+i]=true;
            q[cur]=i;
            Queen(cur+1);
            curVisited[i]=diagonal_vis[1][N+cur-i-1]=diagonal_vis[0][cur+i]=false;//相应的判断标识修改
        } 
    }
}

struct QueenStack{
    int cur;
    int data[MaxN];//data[0]不存位置
};

bool seekNextPos(QueenStack Q,int i,int j){
    for(int k=1;k<=i-1;k++){
        if(Q.data[k]==j||(fabs(j-Q.data[k]))==fabs(i-k)){
            return false;
        }
    }
    return true;
}

void Solution(int n){
    QueenStack Q;
    int currentCur;
    bool findSign=false;//决定是否退栈

    Q.cur=0;
    Q.cur++;

    Q.data[Q.cur]=1;//初始化栈，第一cur 1号位置进栈

    while(Q.cur>0){
        //找到一解
        if(Q.cur==n){
            totalSolutions++;
            /*printf("第%lld个解：",totalSolutions);
            for(int i=1;i<=N;i++){
                std::cout<<Q.data[i]<<" ";
            }*/
            printSolution(Q.data);
            std::cout<<std::endl;

        }
        currentCur=Q.cur;
        findSign=false;
        //新的cur判断8个位置
        for(int i=1;i<=N;i++){
            if(seekNextPos(Q,currentCur+1,i)){
                findSign=true;
                Q.cur++;
                Q.data[Q.cur]=i;
                break;
            }
        }
        //退栈
        if(findSign==false){
            while(Q.cur>0){
                //该cur遍历结束，退栈
                if(Q.data[Q.cur]==n){
                    Q.cur--;
                }
                int currentPos;
                //验证该cur中未遍历的位置
                for(currentPos=Q.data[Q.cur]+1;currentPos<=n;currentPos++){
                    if(seekNextPos(Q,Q.cur,currentPos)){
                        Q.data[Q.cur]=currentPos;
                        break;
                    }
                }
                //遍历结束未找到合适位置，退栈
                if(currentPos>n){
                    Q.cur--;
                }
                else{
                    //找到合适位置，
                    break;
                }
            }
        }
    }
}

