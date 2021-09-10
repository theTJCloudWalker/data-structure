#include<iostream>

#include"SeqList.h"

template<class T>
SeqList<T>::SeqList(int sz) {
    if (sz > 0) {
        maxSize = sz;
        last = -1;
        data = new T[maxSize];
        if (data == NULL) {
            cerr << "´æ´¢·ÖÅä´íÎó£¡" << endl;
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
        cerr << "´æ´¢·ÖÅä´íÎó£¡" << endl;
        exit(1);
    }
    for (int i = 0; i <= last + 1; i++) {
        L.getData(i, value);
        data[i - 1] = value;
    }
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