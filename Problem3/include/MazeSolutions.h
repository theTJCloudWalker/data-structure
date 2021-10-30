#pragma once
#include<iostream>
#include"LinkedStack.h"

int Maze[7][7]={1,1,1,1,1,1,1,
                1,0,1,0,0,0,1,
                1,0,1,0,1,1,1,
                1,0,0,0,1,0,1,
                1,0,1,0,0,0,1,
                1,0,1,0,1,0,1,
                1,1,1,1,1,1,1};

int mark[7][7];

int targetX=5,targetY=5;

struct offsets{
        int x,y;
        std::string direction;
};
const offsets move[4]={ {-1, 0,"N"},
                        { 0, 1,"E"},
                        { 0,-1,"W"},
                        { 1, 0,"S" }};


bool SeekPath(int x,int y){
        if(x==targetX&&y==targetY){
                return 1;
        }
        int m,n;//coordinate of the next position
        std::string direction;
        for(int i=0;i<4;i++){
                m=x+move[i].x;
                n=y+move[i].y;
                direction=move[i].direction;

                if(Maze[m][n]==0&&mark[m][n]==0){
                        mark[m][n]=1;
                        if(SeekPath(m,n)){
                                std::cout<<"("<<m<<","<<n<<"),"<<"Direction: "<<direction<<","<<std::endl;
                                mark[m][n]=2;
                                return true;
                        }
                }
        }
	
	return false;
	
}

void PrintMaze(){
        std::cout<<"迷宫地图："<<std::endl;
        std::cout<<"          ";//10 spaces
        for(int i=0;i<7;i++){
                std::cout<<i<<"列       ";//7 spaces
        }
        std::cout<<std::endl;
        for(int i=0;i<7;i++){
                std::cout<<i<<"行       ";
                for(int j=0;j<7;j++){
                        if(1==Maze[i][j]){
                                std::cout<<"#         ";
                        }
                        else if(0==Maze[i][j]&&(0==mark[i][j]||1==mark[i][j])){
                                std::cout<<"0         ";
                        }
                        else if(0==Maze[i][j]&&2==mark[i][j]){
                                std::cout<<"x         ";
                        }
                }
                std::cout<<std::endl;
        }
}