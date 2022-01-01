/*haven't finished yet
2021.10.23*/
#pragma once
#include<iostream>

template<class T>class DataLists;

template<class T>
class Node{
    friend class DataList<T>;
public:
    Node(const T&value):key(value){}
    T getKey() const {return key;}
    void setKey(T k){key=k;}
private:
    T key;
};

template<class T>
class DataList{
public:
    DataList(int sz=10):ArraySize(sz),elems(new Node<T>[sz]){}
    virtual ~DataList(){delete[] elems;}
    friend std::ostream& operator<<(std::ostream&out,const DataList<T>&OutList);
    friend std::istream& operator>>(std::istream&in,const DataList<T>&InList);
protected:
    T*elems;
    int ArraySize,CurrentSize;
};

template<class T>
class SearchList:public DataList<T>{
public:
    SearchList(int sz=10):DataList<T>(sz){}
    virtual ~SearchList(){}
    virtual int Search(const T&x)const;
};

template<class T>
std::istream&operator>>(std::istream&in,const DataList<T>&InList){
    std::cout <<"输入当前数组大小：";
    in>>InList.CurrentSize;
    std::cout<<"输入数组元素值:"<<std::endl;
    for(int i=0;i<InList.CurrentSize;i++){
        std::cout<<"元素"<<i<<":";
        in>>InList.elems[i];
    }
    return in;
}

template<class T>
std::ostream&operator<<(std::ostream&out,const DataList<T>&OutList){
    out<<"数组内容："<<std::endl;
    for(int i=0;i<OutList.CurrentSize;i++){
        out<<OutList.elems[i]<<" ";
    }
    out<<std::end;
    out<<"当前数组大小："<<OutList.CurrentSize<<std::endl;
    return out;
}

template<class T>
int SearchList<T>::Search(const T&x)const{
    elems[0].
}