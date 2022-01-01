#include <iostream>
#include"AVL.h"

void Menu(){
	std::cout<<"**                二叉排序树                 **"<< std::endl;
	std::cout<<"=============================================="<< std::endl;
	std::cout<<"**              1 --- 建立二叉排序树          **"<< std::endl;
	std::cout<<"**              2 --- 插入元素               **"<< std::endl;
	std::cout<<"**              3 --- 查询元素               **"<< std::endl;
	std::cout<<"**              4 --- 退出程序               **"<< std::endl;
	std::cout<<"=============================================="<< std::endl;
}

int main()
{
	Menu();
	AVLTree<int> test;
	int option=0;
	while(option!=4){
		std::cout<<"Please select:"<<std::endl;
		std::cin>>option;
		switch(option){
			case 1:{
				std::cin >> test;
				std::cout<<"Bsort_Tree is:"<<std::endl;
				std::cout<<test;
				break;
			}
			case 2:{
				std::cout<<"Please input the key which inserted:"<<std::endl;
				int key;
				std::cin >> key;
				if(true==test.Insert(key)){
					std::cout<<"Bsort_Tree is:"<<std::endl;
					std::cout<<test;
				}
				else{
					std::cout<<"The Input Key("<<key<<") is already in!"<< std::endl;
				}
				break;
			}
			case 3:{
				std::cout<<"Please input the key which searched:"<<std::endl;
				int key;
				std::cin >> key;
				if(test.Find(key)==NULL){
					std::cout<<"could not find key "<<key<<std::endl;
				}
				else{
					std::cout<<"Search Success"<<std::endl;
				}
				break;
			}
			case 4:{
				break;
			}
			default:{
				std::cout<<"Error: Unknown input"<<std::endl;
				break;
			}
		}
	}
	system("pause");
	return 0;
}