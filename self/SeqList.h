#pragma once
#include<iostream>
#include<stdlib.h>

#include"LinerList.h"

const int defaultSize = 100;
template<class T>
class SeqList :public LinerList<T> {
protected:
	T* data;                                  //save array
	int maxSize;                              //max size of the list
	int last;
	void reSize(int newSize);                 //change the size of the data array
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);
	~SeqList() { 
		delete[]data; 
	}
	int Size()const{
		return maxSize;
	}
	int Lenth()const{ 
		return last + 1;
	}
	int Search(T& x)const;
	int Locate(int i)const;
	bool getData(int i, T& x)const{
		if (i > 0 && i <= last + 1){
			x = data[i - 1];
			return true;
		}
		else{
			return false;
		}
	}
	void setData(int i, T& x) {
		if (i > 0 && i <= last + 1) {
			data[i - 1] = x;
		}
	}
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty() {
		return last == -1 ? true : false;
	}
	bool IsFull() {
		return last == maxSize - 1 ? true : false;
	}
	void input();
	void output();
	SeqList<T>operator=(SqList<T>& L);
};
