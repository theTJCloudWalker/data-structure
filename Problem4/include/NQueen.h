#pragma once
#include<iostream>
#include"math.h"
#include"LinkedStack.h"
#define MaxSize 100

const int MaxN=30;

int N=0;//num of the queen 
long long totalSolutions=0;//num of the total solutions
bool curVisited[MaxN];//if the cur is occupied by a queen
bool diagonal_vis[2][2*MaxN-1];
int q[MaxN];

void dfs(int cur){
    if(cur==N){
        totalSolutions++;
        //print here of needed
        return;
    }
    for(int i=1;i<=N;i++){

    }
}

void printSolution(int q[]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(j==q[i]){
                printf("x ");
            }
            else{
                printf("0 ");
            }
        }
        std::cout<<std::endl;
    }
}

void Queen(int cur){
    if(cur==N){
        totalSolutions++;

        printSolution(q);               
        std::cout<<std::endl;
        return;
    }
    for(int i=0;i<N;i++){
        if(!curVisited[i]&&!diagonal_vis[1][N+cur-i-1]&&!diagonal_vis[0][cur+i]){
            curVisited[i]=diagonal_vis[1][N+cur-i-1]=diagonal_vis[0][cur+i]=true;
            q[cur]=i;
            Queen(cur+1);
            curVisited[i]=diagonal_vis[1][N+cur-i-1]=diagonal_vis[0][cur+i]=false;
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

            printf("第%d个解：",totalSolutions);
            for(int i=1;i<=N;i++){
                std::cout<<Q.data[i]<<" ";
            }
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

typedef struct
{
	int data[MaxSize];//data[i]存放第i个皇后的列号
	int top;			
} StType;				
int count = 0;
int place(StType st, int i, int j)//测试(i,j)是否与1～i-1皇后有冲突
{
	int k = 1;
	while (k <= i - 1)//j=1到k-1是已放置了皇后的列
	{
		if ((st.data[k] == j) || (fabs(j - st.data[k]) == fabs(i - k)))
		{
			return 0;
		}
		else
			k++;
	}
	return 1;
}
void queen(int n)					
{
	int i, j, k;
	int find = 0;
	StType st;						
	st.top = 0;	//top=0时栈为空					
	st.top++;//将(1,1)进栈
	st.data[st.top] = 1;
	while (st.top>0)//栈不空时循环
	{
		i = st.top;//当前皇后为第i个皇后
		if (st.top == n)			
		{
            totalSolutions++;
			printf("第%d个解：", ++count);
			for (k = 1; k <= st.top; k++)
				printf("(%d,%d) ", k, st.data[k]);
			printf("\n");
		}
		find = 0;//每次退栈时重新检查是否能放
		for (j = 1; j <= n; j++)
			if (place(st, i + 1, j))//在i+1行找到一个放皇后的位置(i+1,j)
			{
				st.top++;
				st.data[st.top] = j;
				find = 1;
				break;
			}
		if (find == 0)//找不到放皇后的位置,回溯
		{
			while (st.top>0)
			{
				if (st.data[st.top] == n)//本列没有可放位置,退栈
					st.top--;
				for (j = st.data[st.top] + 1; j <= n; j++)//在本列找下一个位置
					if (place(st, st.top, j))
					{
						st.data[st.top] = j;
						break;
					}
				if (j>n)//当前皇后在本列没有可放的位置
					st.top--;
				else//本列找到一个位置后退出回溯
					break;
			}
		}
	}
}