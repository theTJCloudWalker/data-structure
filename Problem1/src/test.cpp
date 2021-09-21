#include <iostream>

#include "SinglyLinkedList.h"
#include"Examinee.h"

int  main(){
    Examinee t;
    DataSystem l;
    for(int i=0;i<4;i++){
        std::cin>>t;
        l.Insert(i,t);
    }
    l.DeleteWithID(1);
    l.DeleteWithID(3);
    l.output();
    int ID=4;
    
    Examinee temp=l.SearchWithID(ID);
    l.modify(temp);
   std::cout<<temp<<std::endl;
    /*List<int>t;
     for(int  i=0; i<10;i++){
        t.Insert(10+i,i);
    } 
    t.output();
    ListNode<int> *x=t.Find(5);
    std::cout<<x->GetData()<<"#"<<t.Get(5)<<std::endl;
    t.Remove(9);
    t.Remove(0);
    t.Remove(15);
    t.output();
    t.Insert(18,9);
    t.Insert(50,0);
    t.output();
    std::cout<<std::endl<<t.lenth();
    t.MakeEmpty();
    std ::cout<<"*";
    t.output();
    std ::cout<<"*";
    std::cout<<std::endl;*/
    return 0;
}