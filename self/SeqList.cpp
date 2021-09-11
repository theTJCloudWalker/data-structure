#include<iostream>

#include"SeqList.h"

using namespace std;

template<class T>
SeqList<T>::SeqList(int sz) {
    if (sz > 0) {
        maxSize = sz;
        last = -1;
        data = new T[maxSize];
        if (data == NULL) {
            cerr << "存储分配错误！" << endl;
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
        cerr << "存储分配错误！" << endl;
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
		cerr << "无效的数组大小" << endl;
		return;
	}
	if (newSize != maxSize) {
		T* newArray = new T[newSize];
		if (newArray == NULL) {
			cerr << "存储分配错误" << endl;
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
	return true;
}

template<class T>
void SeqList<T>::input() {
	cout << "开始建立顺序表，请输入表中元素个数：";
	while (1) {
		cin >> last;
		if (last <= maxSize - 1) {
			break;
		}
		cout << "表元素个数输入有误，范围不能超过" << maxSize - 1 << ":";
	}

	for (int i = 0; i < last; i++) {
		cin >> data[i];
		cout << i + 1 << endl;
	}
}

template<class T>
void SeqList<T>::output() {
	cout << "顺序表当前元素的最后位置为：" << last << endl;
	for (int i = 0; i < last; i++) {
		cout << "#" << i + 1 << ":" << data[i] << endl;
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

