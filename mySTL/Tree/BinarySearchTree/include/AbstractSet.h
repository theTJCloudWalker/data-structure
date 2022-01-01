//useless so dar:2021/11/1
#pragma once

template<class T>
class AbstractSet{
    Set(int MaxSetSize):MaxSize(MaxSetSize);
    void MakeEmpty(Set&s);
    int AddMember(Set&s,const T x);
    int DeleteMember(Set&s,const T&x);
    void Assign(Set&s1,Set&s2);
    void Union(Set&s1,Set&s2);
    void Intersection(Set&s1,Set&s2);
    void Difference(Set&s1,Set&s2);
    int Contains(Set&s,const T&x);
    int Equal(Set&s1,Set&s2);
    int SubSet(Set&s1,Set&s2);
};