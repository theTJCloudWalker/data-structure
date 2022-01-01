#include <iostream>

#include "BinaryTree.h"

int main()
{
	//system("chcp 65001");
	BinaryTree<int> tree;
	/*for (int i = 0; i < 20; i++) {
		tree.Insert(i);
	}*/
	std::cin >> tree;
	std::cout << tree << std::endl;
	std::cout << "*******************" << std::endl;
	//PrintBinaryTree(tree.GetRoot());
	std::cout << "Hello world!" << std::endl;
}