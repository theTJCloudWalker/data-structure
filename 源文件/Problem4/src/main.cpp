#include <iostream>
#include"NQueen.h"

int main()
{
	std::cout << "现在有NxN的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上！"<< std::endl;
	std::cout << "请输入皇后的个数："<< std::endl;
	std::cin>>N;
	while(std::cin.fail() || (std::cin.peek() != '\n')||N<=0){
		std::cin.clear();
		std::cin.ignore(1024,'\n');
		std::cout<<"错误输入，请重新输入"<< std::endl;
		std::cin>>N;
	}
	for(int i=0;i<N;i++){
		q[i]=0;
		curVisited[i]=false;
	}
	for(int i=0;i<2*N-1;i++){
		diagonal_vis[1][i]=false;
		diagonal_vis[0][i]=false;
	}
	std::cout<<"皇后摆法"<<std::endl;

	//Queen(0);
	Solution(N);
	
	std::cout<<totalSolutions<<std::endl;
}