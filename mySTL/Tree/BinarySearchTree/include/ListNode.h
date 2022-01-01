#pragma once
#include<iostream>

class ListNode{
    friend void equivalence();
private:
    int data;
    ListNode *link;
    ListNode (int d){data=d;link=NULL;}
};

typedef ListNode* ListNodePtr;