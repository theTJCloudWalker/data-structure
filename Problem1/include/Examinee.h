#pragma once

#include <iostream>
#include <string>
#include"SinglyLinkedList.h"

class Examinee{
public:
    friend std::istream  &operator>>(std::istream &in,Examinee &x){
        in>>x.ID>>x.name>>x.gender>>x.age>>x.major;
        return in;
    }
    friend std::ostream  &operator<<(std::ostream &out,Examinee &x){
        out<<x.ID<<"        "<<x.name<<"        "<<x.gender<<"        "<<x.age<<"        "<<x.major;
        out<<std::endl;
        return out;
    }

    //get certain data
    int GetID(){
        return ID;
    }
   std::string GetName(){
       return name;
   }
   std::string GetGender(){
       return gender;
   }
   short int GetAge(){
       return age;
   }
   std::string GetMajor(){
       return major;
   }

   //modify certain data
  void ModifyID(int newID){
      ID=newID;
      return;
  }
  void ModifyName(std::string newName){
      name=newName;
      return;
  }
  void ModifyGender(std::string newGender){
      gender=newGender;
      return;
  }
  void ModifyAge(short newAge){
      age=newAge;
      return;
  }
  void ModifyMajor(std::string newMajor){
      major=newMajor;
      return ;
  }
private:
    int ID;
    std::string name;
    std::string gender;
    short int age;
    std::string major;
};

class DataSystem{
public:
    bool Insert(int i,Examinee& x);
    Examinee  DeleteWithID(int ID);
    Examinee SearchWithID(int ID);
    void modify(Examinee&target);
    void output(){
        informationList.output();
        return;
    }
    void modifyMenu();
 private:
    List<Examinee>  informationList;
};
 
bool DataSystem::Insert(int i,Examinee& x) {
    return informationList.Insert(x,i);
}

Examinee DataSystem::DeleteWithID(int ID){
    ListNode<Examinee>*p= informationList.GetFirst();
    while(p!=NULL){
        if(p->NextNode()->GetData().GetID()==ID){
            return p->RemoveAfter()->GetData();
        }
        else{
            p=p->NextNode();
        }
    }
}

Examinee DataSystem::SearchWithID(int ID){
    ListNode<Examinee>*p=informationList.GetFirst();
    while(p!=NULL){
        if(p->NextNode()->GetData().GetID()==ID){
            return p->NextNode()->GetData();
        }
        else{
            p=p->NextNode();
        }
    }
}

void DataSystem::modifyMenu(){
     std::cout<<"输入数字以选择你想修改的内容:"<<std::endl;
     std::cout<<"1.修改考号        2.修改姓名"<<std::endl;
     std::cout<<"3.修改性别        4.修改年龄"<<std::endl;
     std::cout<<"5.修改报考类别"<<std::endl;
}

void DataSystem::modify(Examinee&target){
    modifyMenu();
    int sign;//judge which to modify
    while(!(std::cin>>sign)||std::cin.peek()!='\n'){
        std::cin.clear();
        std::cin.ignore(1024,'\n');    
        std::cout<<"输入错误，请重新输入："<<std::endl;
    }

    switch(sign){
        case 1: {
            std::cout<<"将考号修改为："<<std::endl;
            int id;
            std::cin>>id;
            target.ModifyID(id);
            break;
        }
        case 2: {
            std::cout<<"将姓名修改为："<<std::endl;
            std::string name;
            std::cin>>name;
            target.ModifyName(name);
            break;
        }
        case 3: {
            std::cout<<"将性别修改为："<<std::endl;
           std::string gender;
            std::cin>>gender;
            target.ModifyGender(gender);
            break;
        }
      case 4: {
            std::cout<<"将年龄修改为："<<std::endl;
            short age;
            std::cin>>age;
            target.ModifyAge(age);
            break;
        }
          case 5: {
            std::cout<<"将报考类别修改为："<<std::endl;
           std::string major;
            std::cin>>major;
            target.ModifyMajor(major);
            break;
        }
    }
 }
    


