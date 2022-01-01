#include <iostream>
#include"SinglyLinkedList.h"
//#include"CircularList.h"

using namespace std;

//this function is not that safe 
void SafeInput(int& Data) {
	cin >> Data;
	while (cin.fail() || Data <= 0) {
		cout << "请重新输入正确的数据：" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		cin >> Data;
	}
	cin.clear();
}

template <typename T>
void Josephus(List<T>& Js, int n, int m) {
	ListNode<T>* p = Js.GetFirst()->NextNode();
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (p->NextNode() == NULL) {
				p = Js.GetFirst()->NextNode();
			}
			else {
				p = p->NextNode();
			}
		}
		cout << "出列的人是" << p->GetData() << endl;
		ListNode<T>* pre = p->NextNode();
		if (pre == NULL) {
			pre = Js.GetFirst()->NextNode();
		}
		Js.remove(p->GetData());
		p = pre;
	}
}

int main()
{
	List<int> test;
	
	int N, S, M, K;
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一个人开始报数，如此循环，直至剩下K个人为止" << endl;
	cout << "请输入生死游戏的总人数N:" << endl;
	SafeInput(N);
	cout << "请输入游戏开始的位置S：" << endl;
	SafeInput(S);
	cout << "请输入死亡数字M：" << endl;
	SafeInput(M);
	cout << "请输入剩余的生者人数K：" << endl;
	SafeInput(K);
	for (int i = 0; i < N; i++) {
		test.Insert(i + 1, i );
	}
	//test.output();
	Josephus(test, N - K, M);
	std::cout << "最后剩下" << test.Length() << "人" << endl;
	std::cout << "幸存者的位置是:";
	test.output();
	std::cout << std::endl;
#ifdef WIN32
	system("pause");
#endif
	return 0;
}