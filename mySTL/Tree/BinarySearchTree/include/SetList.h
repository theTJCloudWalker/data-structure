template<class T>class SetList;

template<class T>
class SetNode{
    friend class SetList<T>;
public:
    SetNode(const T&item) : data(item),link(NULL){}
private:
    T data;
    SetNode<T>*link;
};

template<class T>
class SetList{
private:
    SetNode<T>*first,*last;
public:
    SetList();
    void MakeEmpty();
    int AddMember(const T&x);
    int DeleteMember(const T&x);

    SetList<T>&operator=(SetList<T>&right);
    SetList<T>&operator+(SetList<T>&right);
    SetList<T>&operator-(SetList<T>&right);
    SetList<T>&operator*(SetList<T>&right);
    int operator==(SetList<T>&right);

    int Contains(const T&x);
    T&Min();
    T&Max();

};

template<class T>
SetList<T>::SetList(){
    SetNode<T>*first=*last=new SetNode<T>(0);
}

template<class T>
int SetList<T>::Contains(const T&x){
    SetNode<T>*ptr=first->link;
    while(ptr!=NULL&&ptr->data<x){
        ptr=ptr->link;
    }
    if(ptr!=NULL&&ptr->data==x){
        return 1;
    }
    else{
        return 0;
    }
}

template<class T>
int SetList<T>::AddMember(const T&x){
    SetNode<T>*ptr=first->link,*q=first;
    while(ptr!=NULL&&ptr->data<x){
        q=ptr;
        ptr=ptr->link;
    }
    if(ptr!=NULL&&ptr->data==x){
        return 0;
    }
    SetNode<T>*s=new SetNode(x);
    s->link=ptr;
    q->link=s;
    if(ptr==NULL){
        last=s;
    }
    delete s;
    return 1;
}

template<class T>
int SetList<T>::DeleteMember(const T&x){
    SetNode<T>*ptr=first->link,*q=first;
    while(ptr!=NULL&&p.data<x){
        q=ptr;
        ptr=ptr->link;
    }
    if(ptr!=NULL&&ptr->data==x){
        q->link=ptr->link;
        if(ptr==last){
            last=q;
        }
        delete ptr;
        return 1;
    }
    else{
        return 0;
    }
}

template<class T>
SetList<T>&SetList<T>::operator=(SetList<T>&right){
    SetNode<T>*pb=right.first->link;
    SetNode<T>*pa=first=new SetNode<T>;
    while(pb!=NULL){
        pa->link=new SetNode<T>(pb->data);
        pa=pa->link;
        pb=pb->link;
    }
    pa->link=NULL;
    last=pa;
    return *this;
}

template<class T>
SetList<T>&SetList<T>::operator+(SetList<T>&right){
    SetNode<T>*pb=right.first->link;
    SetNode<T>*pa=first->link;
    SetNode<T>*pc=first;
    while(pa!=NULL&&pb!=NULL){
        if(pa->data==pb->data){
            pc->link=pa;
            pa=pa->link;
            pb=pb->link;
        }
        else if(pa->data<pb->data){
            pc->link=pa;
            pa=pa->link;
        }
        else{
            pc->link=new SetNode<T>(pb->data);
            pb=pb->link;
        }
        pc=pc->link;
    }
    if(pa!=NULL){
        pc->link=pa;
    }
    else{
        while(pb!=NULL){
            pc->link=new SetNode<T>(pb->data);
            pc=pc->link;
            pb=pb->link;
        }
        pc->link=NULL;
        last=pc;
    }
    return *this;
}

template<class T>
SetList<T>&SetList<T>::operator*(SetList<T>&right){
    SetNode<T>*pb=right.first->link;
    SetNode<T>*pa=first->link;
    SetNode<T>*pc=first;
    while(pa!=NULL&&pb!=NULL){
        if(pa->data==pb->data){
            pc=pc->link;
            pa=pa->link;
            pb=pb->link;
        }
        else if(pa->data<pb->data){
            pc->link=pa->link;
            delete pa;
            pa=pc->link;
        }
        else{
            pb=pb->link;
        }
    }
    while(pa!=NULL){
        pc->link=pa->link;
        delete pa;
        pa=pc->link;
    }
    last=pc;
    return *this;
}

template<class T>
SetList<T>&SetList<T>::operator-(SetList<T>&right){
    SetNode<T>*pb=right.first->link;
    SetNode<T>*pa=first->link;
    SetNode<T>*pc=first;
    while(pa!=NULL&&pb!=NULL){
        if(pa->data==pb->data){
            pc->link=pa->link;
            delete pa;
            pa=pc->link;
            pb=pb->link;
        }
        else if(pa->data<pb->data){
            pc=pc->link;
            pa=pa->link;
        }
        else{
            pb=pb->link;
        }
    }
    if(pa==NULL){
        last=pc;
    }
    return *this;
}

template<class T>
int SetList<T>::operator==(SetList<T>&right){
    SetNode<T>*pb=right.first->link;
    SetNode<T>*pa=first->link;
    while(pa!=NULL&&pb!=NULL){
        if(pa->data==pb->data){
            pa=pa->link;
            pb=pb->link;
        }
        else{
            return 0;
        }
    }
    if(pa!=NULL||pb!=NULL){
        return 0;
    }
    return 1;
}

