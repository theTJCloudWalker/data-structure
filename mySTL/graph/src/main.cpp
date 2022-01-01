#include <iostream>
#include"Graphmtx.h"


int main()
{
	Graphmtx<char, int> p;
	std::cin >> p;
	//p.RemoveVertex(2);
	int x = 2;
	p.Prim('a');


	std::cout << p;
	std::cout << "Hello world!" << std::endl;
	system("pause");
	return 0;
}