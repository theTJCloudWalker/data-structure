#include <iostream>
#include"MazeSolutions.h"

int main()
{
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			mark[i][j]=0;
		}
	}
	if(SeekPath(1,1)){
		mark[1][1]=2;
		std::cout<<"("<<1<<","<<1<<"),"<<"Direction: "<<"E"<<std::endl;
	}
	PrintMaze();
	std::cout << "Hello world!" << std::endl;
}