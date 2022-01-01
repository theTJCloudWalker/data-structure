#pragma once
#include<iostream>
#include<stdlib.h>

const int defaultSize = 100;
template<class T>
class SeqList{
protected:
	T* data;                                  //save array
	int maxSize;                              //max size of the list
	int last;
	void reSize(int newSize);                 //change the size of the data array
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);
	~SeqList() { 
		delete []data; 
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
	bool IsEmpty() const{
		return last == -1 ? true : false;
	}
	bool IsFull() const{
		return last == maxSize - 1 ? true : false;
	}
	void input();
	void output();
	void selectSort();
	void bubbleSort();

	void Union(SeqList<T> &LA,SeqList<T>&LB);
	void Intersection(SeqList<T>& LA, SeqList<T>& LB);
	SeqList<T>operator=(SeqList<T>& L);
};

template<class T>
SeqList<T>::SeqList(int sz) {
    if (sz > 0) {
        maxSize = sz;
        last = -1;
        data = new T[maxSize];
        if (data == NULL) {
            std::ostream::cerr << "存储分配错误！" << endl;
            exit(1);
        }
    }
}

template<class T>
SeqList<T>::SeqList(SeqList<T>& L) {
    maxSize = L.Size();
    last = L.Lenth() - 1;
    T value;
    data = new T[maxSize];
    if (data == NULL) {
        std::ostream::cerr << "存储分配错误！" << endl;
        exit(1);
    }
    for (int i = 1; i < last+1 ; i++) {
        L.getData(i, value);
        data[i - 1] = value;
    }
}

template<class T>
void SeqList<T>::reSize(int newSize) {
	if (newSize <= 0) {
		std::ostream::cerr << "无效的数组大小" << endl;
		return;
	}
	if (newSize != maxSize) {
		T* newArray = new T[newSize];
		if (newArray == NULL) {
			std::ostream::cerr << "存储分配错误" << endl;
			exit(1);
		}
		int n = last + 1;
		T* srcptr = data;
		T* desptr = newArray;
		while (n--) {
			*desptr++ = *srcptr++;
		}
		delete[]data;
		data = newArray;
		maxSize = newSize;
	}
	return;
}

template<class T>
int SeqList<T>::Search(T& x)const {
    for (int i = 0; i <= last; i++) {
        if (x == data[i]) {
            return i+1;
        }
    }
    return 0;
}

template<class T>
int SeqList<T>::Locate(int i)const {
    if (i >= 1 && i <= last + 1) {
        return i;
    }
    else {
        return 0;
    }
}

template<class T>
bool SeqList<T>::Insert(int i, T& x) {
	//full list,can't insert
	if (last == maxSize - 1) {
		return false;
	}
	//wrong number i
	if (i<0 || i>last + 1) {
		return false;
	}
	//整体后移，空出data[i]
	for (int j = last; j >= i; j--) {
		data[j + 1] = data[j];
	}

	data[i] = x;

	last++;//list lenth +1

	return true;
}

template<class T>
bool SeqList<T>::Remove(int i, T& x) {
	//empty list,nothing to remove
	if (last == -1) {
		return false;
	}
	//wrong i
	if (i<0 || i>last + 1) {
		return false;
	}

	for (int j = i; j <= last; j++) {
		data[j - 1] = data[j];
	}
	last--;
	return true;
}

template<class T>
void SeqList<T>::input() {
	std::cout << "开始建立顺序表，请输入表中元素个数：";
	while (1) {
		cin >> last;
		if (last <= maxSize - 1) {
			break;
		}
		std::cout << "表元素个数输入有误，范围不能超过" << maxSize - 1 << ":";
	}

	for (int i = 0; i < last; i++) {
		cin >> data[i];
		std::cout <<"#"<< i + 1 << endl;
	}
}

template<class T>
void SeqList<T>::output() {
	std::cout << "顺序表当前元素的最后位置为：" << last << endl;
	for (int i = 0; i < last; i++) {
		std::cout << "#" << i + 1 << ":" << data[i] << endl;
	}
}

template<class T>
void SeqList<T>::selectSort() {
	int minimum;
	for (int i = 0; i <= last; i++) {
		minimum = i;
		for (int j = i; j < last; j++) {
			if (data[j] < data[minimum]) {
				minimum = j;
			}
		}
		if (minimum != i) {
			int temp = data[i];
			data[i] = data[minimum];
			data[minimum] = temp;
		}
	}
	return;
}

template<class T>
void SeqList<T>::bubbleSort() {
	T temp;
	for (int i = 0; i <= last; i++) {
		for (int j = 0; j < last-i-1; j++) {
			if (data[j] > data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}
	return;
}

template<class T>
SeqList<T> SeqList<T>::operator=(SeqList<T>& L) {
	maxSize = L.maxSize;
	last = L.last;
	T value;
	//data = new T[maxSize];

	for (int i = 1; i <= last; i++) {
		L.getData(i, value);
		data[i-1] = value;
	}
	//return this;
}

template<class T>
void SeqList<T>::Union(SeqList<T>& LA, SeqList<T>& LB) {
	int n = LA.Lenth() - 1, m = LB.Lenth() - 1, i, k, x;
	for (int i = 1; i <= m; i++) {
		LB.getData(i, x);
		k = LA.Search(x);
		if (k == 0) {
			LA.Insert(n, x);
			n++;
		}
	}
}

template<class T>
void SeqList<T>::Intersection(SeqList<T>& LA, SeqList<T>& LB) {
	int n = LA.Lenth()-1, m = LB.Lenth()-1, i = 1, k, x;
	while (i <= n) {
		LA.getData(i, x);
		k = LB.Search(x);
		if (k == 0) {
			LA.Remove(i, x);
			n--;
		}
		else {
			i++;
		}
	}
}
