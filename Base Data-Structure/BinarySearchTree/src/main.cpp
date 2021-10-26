#include <iostream>
//#include"Set.h"
#include "BinaryTree.h"

int main()
{
	/*Set s1,s2,s3,s4,s5;
	int index,equal;
    for(int k=0;k<10;k++){
		s1.AddMember(k);
		s2.AddMember(k+7);
	}
	s3=s1+s2;
	s4=s1*s2;
	s5=s1-s2;
	index=s1.SubSet(s4);
	std::cout<<index<<std::endl;
	equal=s1==s2;
	std::cout <<equal<<std::endl;*/
	BinaryTree<int> test1;
	std::cin>>test1;
	std::cout<<test1;
	std::cout<<std::endl;
	BinaryTree<int> test2(test1);
	std::cout << "Hello world!" << std::endl;
	std::cout<<test2;
	BinaryTreeNode<int> *p=test2.Find(1);
	std::cout<<p->GetData()<<std::endl;
	std::cout << "Hello world!" << std::endl;
	system("pause");
}