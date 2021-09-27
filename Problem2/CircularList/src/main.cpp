#include <iostream>
#include"CircularLIst.h"

using namespace std;

//this function is not that safe 
void SafeInput(int &Data){
	cin>>Data;
	while(cin.fail()||Data<=0){
		cout<<"请重新输入正确的数据："<<endl;
		cin.clear();
		cin.ignore(1024,'\n');
		cin>>Data;
	}
	cin.clear();
}

template <typename T>
void Josephus(CircularList<T>&Js,int n,int m){
	CircularListNode<T>*p=Js.Find(0),*pre=NULL;
	for(int i=0;i<n;i++){
		for(int j=1;j<m;j++){
			pre=p;
			p=p->link;
			if(p->link==Js.getHead()&&j!=m-1){
				p=p->link;
			}
		}
		cout<<"第"<<i+1<<"个死者的位置是："<<p->data<<endl;
		pre->link=p->link;
		delete p;
		if(pre->link==Js.getHead()){
			pre=pre->link;
		}
		p=pre->link;
	}
}

int main( )
{
	CircularList<int> test;
	/*int x=100;
	test.Insert(x,1);
	test.Remove(0);
	test.output();
	std::cout << "Hello world!" << std::endl;
	std::cout << "Hello world!" << std::endl;*/
	int N,S,M,K;
	cout<<"现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一个人开始报数，如此循环，直至剩下K个人为止"<<endl;
	cout<<"请输入生死游戏的总人数N:"<<endl;
	SafeInput(N);
	cout<<"请输入游戏开始的位置S："<<endl;
	SafeInput(S);
	cout<<"请输入死亡数字M："<<endl;
	SafeInput(M);
	cout<<"请输入剩余的生者人数K："<<endl;
	SafeInput(K);
	for (int i = 0; i < N; i++) {
		test.PushBack(i+1);
	}
	test.output();
	Josephus(test,N-K,M);
	test.output();
	//test.output();
	//CircularListNode<int>*p=test.Find(0);
	//cout<<p->data<<endl;
	//cout<<"N"<<endl;
	return 0;
}