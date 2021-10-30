#include <iostream>
#include <fstream>
#include <vector>
#include"Trie.h"



int IsPunction(const char ch) {
	//不是字母就是标点
	if ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')) {
		return 0;
	}
	else if(ch=='^') {
		return 2;//sign of EOF
	}
	return 1;
}

void SearchPunction(std::string str, std::vector<std::string>&words) {
	int head = 0,wordLen=0;
	bool Eof = false, punction = false;
	words.clear();
	for (int i = 0; i < str.size()&&!Eof; i++) {
		//是标点
		switch(IsPunction(str[i])) {
		    case 0: {
				//不是标点
				wordLen++;
				if (i == str.size()-1&&!punction) {
					words.push_back(str.substr(head, wordLen));
				}
				break;
			}
			case 1: {
				//不是EOF
				if (wordLen != 0) {
					words.push_back(str.substr(head, wordLen));//将以head为首，长度为的string压入vector
					head += wordLen;
					head++;
					wordLen = 0;
				}
				std::string punction = str.substr(i,1);
				words.push_back(punction);
				break;
			}
			case 2: {
				//EOF
				if (wordLen != 0) {
					words.push_back(str.substr(head, wordLen));//将以head为首，长度为的string压入vector
				}
				words.push_back("^");
				Eof = true;//结束读取
				break;
			}
		}
	}
	return ;
}

int main()
{
	system("chcp 65001");
	std::cout << "关键字检索系统:" << std::endl;
	std::cout << "请输入文件名:";
	std::string name,wordstr,key;
	Trie system;
	std::cin >> name;
	std::ofstream fp(name);
	std::vector<std::string> words;
	std::cout << "请输入一段英文:" << std::endl;
	/*while (std::cin >> wordstr) {
		SearchPunction(wordstr, words);
		for (int i = 0; i < words.size(); i++) {
			if (1 != words[i].size()) {
				fp << words[i]<<" ";
			}
			else {
				fp << words[i];
			}
			system.Insert(words[i]);
		}
		if (!words.empty()&&words.back() == "^") {
			break;
		}
	}*/
	fp.close();
	std::cout << "本段文字已保存在文本文件\""<<name<<"\"中"<<std::endl;
	std::ifstream ReadFile(name);
	while (!ReadFile.eof()) {
		ReadFile >> wordstr;
		if (wordstr.size() != 1) {
			std::cout <<" "<< wordstr;
		}
		else {
			std::cout<< wordstr;
		}
	}
	std::cout << std::endl;
	std::cout << system.Search("Web") << std::endl;
	return 0;
}