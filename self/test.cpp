#include<iostream>

#include"SeqList.cpp"
//#include"LinerList.h"
using namespace std;

int main()
{
	SeqList<int> A;
	A.input();
    SeqList<int> B = A;
	B.selectSort();
	B.output();
	cout << "END";
	//A.output();
	return 0;
}