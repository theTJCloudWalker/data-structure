#include <iostream>
#include <string>
#include"LinkedStack.h"
#include"BinaryTree.h"
#include"SinglyLinkedList.h"//存放后序串


List<std::string>* postfix(std::string exp)
{
	std::string token,useless;     //当前读取的字符 
	std::string s; //目标后缀表达式
	List<std::string>*postfixExp=new List<std::string>;
	LinkedStack<std::string>opStack;
	bool Sign = false;
	std::string sign;
	int length=exp.length();
	for (int i = 0; i < length; i++)
	{
		token = exp[i];
		if (token == "(") {
			opStack.Push(token); //是 ( 则放入栈中 
		}
		else if (token == ")") {
			while (opStack.getTop() != "(") //将与之匹配的（之前的所有元素出栈 
			{
				s = opStack.getTop();
				postfixExp->Insert(s, postfixExp->lenth());
				opStack.Pop(useless);
			}
			opStack.Pop(useless);
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/") {
			std::string former;
			char latter;
			if (i - 1 >= 0) {
				former = exp[i - 1];
			}
			latter = exp[i + 1];
			if ((i-1>=0)&&(former == "+" || former == "-" || former == "*" || former == "/")&&(latter<='9'&&latter>='0')) {
				Sign = true;
				sign = exp[i];
			}
			else if (i == 0) {
				Sign = true;
				sign = exp[i];
			}
			else {
				if (opStack.IsEmpty() || opStack.getTop() == "(" || ((token == "*" || token == "/") && (opStack.getTop() == "+" || opStack.getTop() == "-")))
				{
					opStack.Push(token);
				}
				else //若优先级低于栈顶元素  
				{
					s = opStack.getTop();
					postfixExp->Insert(s, postfixExp->lenth());
					opStack.Pop(useless);
					if (!opStack.IsEmpty() && (opStack.getTop() == "+" || opStack.getTop() == "-"))
					{
						s = opStack.getTop();
						postfixExp->Insert(s, postfixExp->lenth());
						opStack.Pop(useless);
					}
					opStack.Push(token);
				}
			}
		}
		else {
			s = token;
			while ((char(exp[i + 1]) <= '9' && char(exp[i + 1] >= '0'))|| char(exp[i + 1])=='.') {
				i++;
				token = exp[i];
				s = s + token;
			}
			if (Sign) {
				s = sign + s;
			}
			postfixExp->Insert(s, postfixExp->lenth());
			Sign = false;
		}

	}
	while (!opStack.IsEmpty())   //将栈中剩余的元素依次输出  
	{
		s = opStack.getTop();
		postfixExp->Insert(s, postfixExp->lenth());
		opStack.Pop(useless);
	}
	return postfixExp;
};

int main()
{
	std::string inOrderStr;//中缀串
	List<std::string>*post;//转化后的后序串

	std::cout << "请输入表达式:  ";
	std::cin>>inOrderStr;
	post = postfix(inOrderStr);
    BinaryTree<std::string>* test = new BinaryTree<std::string>("0");
	test->createWithPost(post);//根据后序串生成二叉树
    
	std::cout << "波兰表达式:    ";
	test->PreOrderTraverse();
	std::cout << std::endl;
	std::cout << "中缀表达式:    ";
	test->InOrderTraverse();
	std::cout << std::endl;
	std::cout << "逆波兰表达式:  " ;
	test->PostOrderTraverse();                                    
	std::cout << std::endl;

	system("pause");
	return 0;
}