//链表栈
#include<iostream>
#include<assert.h>

template<class T>class LinkedStack;

//链表结点              
template<class T>
class LinkNode{
public:
        friend class LinkedStack<T>;
        T data;
        LinkNode<T>*link;
        LinkNode(LinkNode<T>*ptr=NULL){
                link=ptr;
        }
        LinkNode(const T&item,LinkNode<T>*ptr=NULL){
                data=item;
                link=ptr;
        }
};

template<class T>
class LinkedStack {
public:
        LinkedStack():top(NULL){}
        ~LinkedStack(){
                MakeEmpty();
        }

        void Push(const T&x);
        bool Pop(T&x);
        bool getTop(T&x)const;
        bool IsEmpty()const{
                return (top==NULL)?true:false;
        }
        bool IsFull()const{
                return false;
        }
        int getSize()const;
        void MakeEmpty();
        template<class  TypeName>friend std::ostream& operator <<(std::ostream& os,LinkedStack<TypeName>&s);
private:
        LinkNode<T>*top;
};

template<class T>
void LinkedStack<T>::MakeEmpty(){
        LinkNode<T>*p;
        while(top!=NULL){
                p=top;
                top=top->link;
                delete p;
        }
}

template<class T>
void LinkedStack<T>::Push(const T& x){
        top=new LinkNode<T>(x,top);
        assert(top!=NULL);//断言 
}

template<class T>
bool LinkedStack<T>::Pop(T &x){
        if(IsEmpty()==true){
                return false;
        }
        LinkNode<T>*p=top;
        top=top->link;
        x=p->data;
        delete p;
        return true;
}

template<class T>
bool LinkedStack<T>::getTop(T&x)const{
        if(IsEmpty()==true){
                return false;
        }
        x=top->data;
        return true;
}

template<class T>
int LinkedStack<T>::getSize()const{
        LinkNode<T>*p=top;
        int count =0;
        while(p!=NULL){
                p=p->link;
                count++;
        }
        return count;
}

template<class TypeName>
std::ostream& operator<<(std::ostream& os,LinkedStack<TypeName>&s){
        os<<"栈中元素个数="<<s.getSize()<<std::endl;
        LinkNode<TypeName>*p=s.top;
        int i=0;
        while(p!=NULL){
                os<<++i<<":"<<p->data<<std::endl;
                p=p->link;
        }
        return os;
}

