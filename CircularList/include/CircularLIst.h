template <typename T>
class CircularList;

template <typename T>
class CircularListNode
{
public:
    friend class CircularList<T>;
     CircularListNode(CircularListNode<T>*next=NULL):link(next){}
     CircularListNode(T d,CircularListNode<T>*next=NULL):data(d),link(next){}
//private:
    T data;
    CircularListNode<T> *link;
};

template <typename T>
class CircularList
{
public:
    CircularList(){first=new CircularListNode<T>;first->link=first;}
    CircularList(const T&x){first=new CircularListNode<T>(x);first->link=first;}
    CircularList(CircularList<T>&L);
    ~CircularList();
    void MakeEmpty();
    int Lenth() const { 
	CircularListNode<T>*p=first->link;
	int count=0;
	while(p!=first){
		p=p->link;
		count++;
	}
	return count;
}
    bool IsEmpty() const {
        return((first->link) == first);
    }
    CircularListNode<T>*getHead()const{
        return first;
    }//return the address of the head node
    void SetHead(CircularListNode<T>*p);
    CircularListNode<T>*Find(int pos);
    CircularListNode<T>*Search(T x);
    CircularListNode<T>*Locate(int pos);
    T getData(int pos);
    void setData(int pos,T&x);
    bool Insert(T& value,int pos);
    T* Remove(int pos);
    void remove(T value);

    void PushBack(T data){
        Insert(data,Lenth());
    }

    void PushFront(T data){
        Insert(data,0);
    }

    void output();
private:
    CircularListNode<T> *first;
};

template<class T>
CircularList<T>::CircularList(CircularList<T>& L) {
	T value;
	CircularListNode<T>* srcptr = L.getHead();
	CircularListNode<T>* destptr = first = new CircularListNode<T>;
	while (srcptr->link != first) {
		value = srcptr->link->data;
		destptr->link = new CircularListNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link =first;
}

/*template<class T>
bool CircularList<T>::Insert(T &value,int pos) {
	CircularListNode<T>*p=Find(pos-1);
	if(p==NULL){
		return false;
	}
	CircularListNode<T>* newNode=new CircularListNode<T>;
	newNode->data=value;
	newNode->link=p->link;
	p->link=newNode;
	return true;
}*/


/*template<class T>
CircularListNode<T>* CircularListNode<T>::RemoveAfter(){
	ListNode<T>*temp=link;
	if(link==NULL){
		return NULL;
	}
	link=temp->link;
	return temp;
}*/

template<class T>
T CircularList<T>::getData(int pos){
    if(IsEmpty()||pos<0){
        return -1;
    }
    int i=0;
    CircularListNode<T>* temp=first->link;
    while(temp!=first){
        if(i==pos){
            break;
        }
        temp=temp->link;
    }
    return temp->data;
}

template<class T>
CircularList<T>::~CircularList(){
	MakeEmpty();
	delete first;
}

template<class T>
void CircularList<T>::MakeEmpty(){
    if(IsEmpty()){
        return;
    }
	CircularListNode<T>*p;
	while(first->link!=first){
		p=first->link;
		first->link=p->link;
		delete p;
	}
}

/*template<class T>
int CircularList<T>::Lenth() const { 
	CircularListNode<T>*p=first->link;
	int count=0;
	while(p!=first){
		p=p->link;
		count++;
	}
	return count;
}*/

/*template<class T>
CircularListNode<T>*CircularList<T>::FindWithCertainData(T value){
	CircularListNode<T>*p=first->link;
	while(p!=NULL&&p->data!=value){
		p=p->link;
	}
	return p;
}*/

/*template<class T>
ListNode<T>* List<T>::FindWithCertainData(const std::string& dataType,T& x){
	ListNode<T>*p=first->link;
	while(p!=NULL){
		
	}
}*/

template<class T>
CircularListNode<T>*CircularList<T>::Find(int pos){
    int maxSize=Lenth();
	if(pos<-1||pos>maxSize){
		return NULL;
	}
	else if(pos==-1){
		return first;
	}
	else{
		CircularListNode<T>* p=first->link;
		int j=0;
		while(p!=first&&j<pos){
			p=p->link;
			j++;
		}
		return p;
	}
}

template<class T>
bool CircularList<T>::Insert(T& value,int pos) {
    int maxSize=Lenth();
    if(pos<0||pos>maxSize){
        return false;
    }
	CircularListNode<T>*p=Find(pos-1);
	if(p==NULL){
		return false;
	}
	CircularListNode<T>* newNode=new CircularListNode<T>(value);
	newNode->link=p->link;
	p->link=newNode;
	return true;
}

template<class T>
T* CircularList<T>::Remove(int pos){
	CircularListNode<T>* p=Find(pos-1),*q;
	if((p==NULL)||(p->link==NULL)){
		return NULL;
	}
	q=p->link;//memory the link to the next node
	p->link=q->link;
	T* value=new T(q->data);
	delete q;
	return value;
} 

/*template<class T>
T*CircularList<T>::Get(int i){
	CircularListNode<T>*p=Find(i);
	if(p==NULL||p==first){
		return NULL;
	}
	else{
		return &p->data;
	}
}*/

template<class T>
void CircularList<T>::output(){
    if(IsEmpty()){
        std::cout<<"The CircularList is empty!"<<std::endl;
        return;
    }
	CircularListNode<T>*p=first->link;
	int count=1;
	while(p!=first){
		std::cout<<"#"<<count++<<" "<<p->data<<"  "<<std::endl;;
		p=p->link;
	}
} 