#pragma once
#include <iostream>
#include <string>
#include <iomanip>//格式化输出
#include <fstream>
#include "SinglyLinkedList.h"

template<class T>
void InputWithCorrection(T& data) {
    while (!(std::cin >> data) || (std::cin.peek() != '\n' && std::cin.peek() != 32)) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        std::cout << "输入错误，请重新输入." << std::endl;
    }
}

class Student {
public:
    friend std::istream& operator>>(std::istream& in, Student& x) {
        InputWithCorrection(x.ID);
        InputWithCorrection(x.name);
        in>>x.gender;
        InputWithCorrection(x.age);
        in>>x.major;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, Student& x) {
        //out<<x.ID<<"        "<<x.name<<"        "<<x.gender<<"        "<<x.age<<"        "<<x.major;
        out << std::setiosflags(std::ios::left) << std::setw(5) << x.ID << std::setw(10) << x.name <<
            std::setw(10) << x.gender << std::setw(5) << x.age << x.major;
        out << std::endl;
        return out;
    }

    friend bool operator==(Student& x1, Student& x2) {
        if (x1.ID == x2.ID) {
            return true;
        }
        return false;
    }

    friend bool operator!=(Student& x1, Student& x2) {
        if (x1.ID != x2.ID) {
            return true;
        }
        return false;
    }

    //get certain data
    int GetID() {
        return ID;
    }
    std::string GetName() {
        return name;
    }
    std::string GetGender() {
        return gender;
    }
    short int GetAge() {
        return age;
    }
    std::string GetMajor() {
        return major;
    }

    //modify certain data
    void ModifyID(int newID) {
        ID = newID;
        return;
    }
    void ModifyName(std::string newName) {
        name = newName;
        return;
    }
    void ModifyGender(std::string newGender) {
        gender = newGender;
        return;
    }
    void ModifyAge(unsigned newAge) {
        age = newAge;
        return;
    }
    void ModifyMajor(std::string newMajor) {
        major = newMajor;
        return;
    }
private:
    int ID;
    std::string name;
    unsigned int age;
    std::string major;
    std::string gender;
};

class DataSystem {
public:
    bool Insert(int i, Student& x);
    Student DeleteWithID(int ID);
    bool SearchWithID(int ID, Student& ptr);
    Student* GetCertainData(int ID);
    void modify(Student* target);
    void output() {
        informationList.output();
        return;
    }

    void SaveData();
    void ReadFile();
    void revocation();//取消上次操作
    int Size() {
        return informationList.lenth();
    }
    void init();
    void run();

    void Statistics();

    void WelcomeMenu();
    void ModifyMenu();
    void InputMenu();
    void TitleMap();
private:
    List<Student>  informationList;
};

void DataSystem::run(){
    Student t;
   
    bool quit = false;
    int operationSign;
    while (!quit) {
        std::cout << std::endl;
        std::cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，6存储数据,7退出系统(不保存数据)，0为取消操作）" << std::endl;
        while (!(std::cin >> operationSign) || (std::cin.peek() != '\n' && std::cin.peek() != 32)) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cout << "输入错误，请重新输入：." << std::endl;
        }
        switch (operationSign) {
        case 1: {
            SaveData();
            std::cout << "请输入你要插入的位置：（输入小于0时插入表头，大于总长时插入表尾）" << std::endl;
            int pos;
            while (!(std::cin >> pos)
                || (std::cin.peek() != '\n' && std::cin.peek() != 32)) {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "输入错误类型数据，请重新输入：" << std::endl;
            }
            Student* temp = new Student();
            std::cout << "请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别：" << std::endl;
            std::cin >> *temp;
            std::cout<<*temp;
            Student* ptr = new Student();
            if(SearchWithID(temp->GetID(),*ptr)){
                std::cout<<"已存在对应该考号的考生!"<<std::endl;
                std::cout<<"其信息如下:";
                std::cout<<*ptr<<std::endl;
            }
            else{
                if (pos < 0) {
                    Insert(0, *temp);
                }
                else if (pos > Size()) {
                    Insert(Size(), *temp);
                }
                else {
                    Insert(pos, *temp);
                }
            }
            //****************************
            output();
            //****************************
            delete temp;
            delete ptr;
            break;
        }
        case 2: {
            SaveData();
            int id;
            std::cout << "请输入要删除的考生的考号：" << std::endl;
            while (!(std::cin >> id) || (std::cin.peek() != '\n' && std::cin.peek() != 32)) {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "输入错误，请重新输入：" << std::endl;
            }
           Student temp;

            if (SearchWithID(id, temp)) {
                DeleteWithID(id);
                std::cout << "你要删除的考生信息是：" << temp << std::endl;
                output();
            }
            else {
                std::cout << "查无此人！" << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "请输入你要查找的学生考号." << std::endl;
            int id;
            while (!(std::cin >> id) || (std::cin.peek() != '\n' && std::cin.peek() != 32)) {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "输入错误，请重新输入:" << std::endl;
            }
           Student temp;

            if (SearchWithID(id, temp)) {
                TitleMap();
                std::cout << temp << std::endl;
            }
            else {
                std::cout << "查无此人！" << std::endl;
            }
            break;

        }
        case 4: {
            SaveData();
            std::cout << "请输入你要修改的学生考号." << std::endl;
            int id;
            while (!(std::cin >> id) || (std::cin.peek() != '\n' && std::cin.peek() != 32)) {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "输入错误，请重新输入：" << std::endl;
            }
           Student temp;

            if (SearchWithID(id, temp)) {
               Student* p = GetCertainData(id);
                // std::cout<<temp->GetData()<<std::endl;
                 //Examinee*p=temp->NextNode()->GetDataAddress();
                modify(p);
                //std::cout<<*temp<<std::endl;
            }
            else {
                std::cout << "查无此人！" << std::endl;
            }
            output();
            break;
        }
        case 5:{
            Statistics();
            break;
        }
        case 6:{
            SaveData();
            break;
        }
        case 7:{
            quit=true;
            break;
        }
        case 0: {
            revocation();
            break;
        }
        }
    }
    output();
}

void DataSystem::Statistics(){
    std::cout<<"当前数据库内共有"<<informationList.lenth()<<"条数据."<<std::endl;

    ListNode<Student>* p = informationList.GetFirst();
    int male,female;
    int age[100]={0};
    male=female=0;
    while(p->NextNode() != NULL){
        p=p->NextNode();
        if(p->GetData().GetGender()=="男"){
            male++;
        }
        else{
            female++;
        }
        age[p->GetData().GetAge()]++;
    }

    std::cout<<"性别统计:"<<std::endl;
    std::cout<<"male:"<<male<<std::endl;
    std::cout<<"female:"<<female<<std::endl;

    std::cout<<"年龄统计:"<<std::endl;
    for(int i=0; i<100;i++){
        if(age[i]!=0){
            std::cout<<"Age:"<<i+1<<"---"<<age[i]<<"人"<<std::endl;
        }
    }

}

void DataSystem::SaveData() {
    if (informationList.GetFirst()->NextNode() == NULL) {
        std::cout << "Nothing to save!" << std::endl;
        return;
    }
    std::ofstream fp;
    fp.open("data.txt", std::ios::out);
    if (!fp.is_open()) {
        std::cout << "文件打开失败！" << std::endl;
        return;
    }
    ListNode<Student>* p = informationList.GetFirst();
    while (p->NextNode() != NULL) {
        fp << p->NextNode()->GetData().GetID() << " " << p->NextNode()->GetData().GetName() << " " << p->NextNode()->GetData().GetGender() << " "
            << p->NextNode()->GetData().GetAge() << " " << p->NextNode()->GetData().GetMajor() << std::endl;
        p = p->NextNode();
    }
    
    fp.close();
}

void DataSystem::ReadFile() {
    //std::ofstream fp("test.txt", std::fstream::out);
    std::ifstream fp;
    fp.open("data.txt", std::ios::in);
    if (!fp.is_open()) {
        std::cout << "文件打开失败！" << std::endl;
        return;
    }

    int id;
    std::string name;
    std::string gender;
    unsigned int age;
    std::string major;
    Student temp;

    int count = informationList.lenth();

    while (fp.peek()!=EOF){
        fp >> id >> name >> gender >> age >> major;
        temp.ModifyID(id);
        temp.ModifyName(name);
        temp.ModifyGender(gender);
        temp.ModifyAge(age);
        temp.ModifyMajor(major);
        if (informationList.FindWithCertainData(temp) == NULL) {
            informationList.Insert(temp, count);
            count++;
        }
    }
    fp.close();
    informationList.Remove(count);
}

bool DataSystem::Insert(int i, Student& x) {
    return informationList.Insert(x, i);
}

Student DataSystem::DeleteWithID(int ID) {
    ListNode<Student>* p = informationList.GetFirst();
    while (p != NULL) {
        if (p->NextNode()->GetData().GetID() == ID) {
            return p->RemoveAfter()->GetData();
        }
        else {
            p = p->NextNode();
        }
    }
    return p->GetData();
}

bool DataSystem::SearchWithID(int ID, Student& ptr) {
    ListNode<Student>* p = informationList.GetFirst();
    while (p->NextNode() != NULL) {
        if (p->NextNode()->GetData().GetID() == ID) {
            ptr = p->NextNode()->GetData();
            return true;
        }
        else {
            p = p->NextNode();
        }
    }
    return false;
}

//make sure the data is existent,or never use this 
Student* DataSystem::GetCertainData(int ID) {
    ListNode<Student>* p = informationList.GetFirst();
    while (p->NextNode() != NULL) {
        if (p->NextNode()->GetData().GetID() == ID) {
            break;
        }
        else {
            p = p->NextNode();
        }
    }
    return p->NextNode()->GetDataAddress();
}

void DataSystem::WelcomeMenu() {
    std::cout << "首先请建立考生信息系统！" << std::endl;
}

void DataSystem::TitleMap() {
    std::cout << "学号 姓名      性别      年龄  报考类别." << std::endl;
}

void DataSystem::ModifyMenu() {
    std::cout << "输入数字以选择你想修改的内容：" << std::endl;
    std::cout << "1.修改考号      2.修改姓名" << std::endl;
    std::cout << "3.修改性别      4.修改年龄" << std::endl;
    std::cout << "5.修改报考类别." << std::endl;
}

void DataSystem::InputMenu() {
    std::cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别：" << std::endl;
}

void DataSystem::modify(Student* target) {
    ModifyMenu();
    int sign;//judge which to modify
    while (!(std::cin >> sign) || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        std::cout << "输入错误，请重新输入：" << std::endl;
    }
    //clear 
    std::cin.clear();
    std::cin.ignore(1024, '\n');
    // 
    switch (sign) {
    case 1: {
        std::cout << "将考号修改为：" << std::endl;
        int id;
        std::cin >> id;
        target->ModifyID(id);
        break;
    }
    case 2: {
        std::cout << "将姓名修改为：" << std::endl;
        std::string name;
        std::cin >> name;
        target->ModifyName(name);
        break;
    }
    case 3: {
        std::cout << "将性别修改为：" << std::endl;
        std::string gender;
        std::cin >> gender;
        target->ModifyGender(gender);
        break;
    }
    case 4: {
        std::cout << "将年龄修改为：" << std::endl;
        short age;
        std::cin >> age;
        target->ModifyAge(age);
        break;
    }
    case 5: {
        std::cout << "将报考类别修改为：" << std::endl;
        std::string major;
        std::cin >> major;
        target->ModifyMajor(major);
        break;
    }
    }
}

void DataSystem::init() {
    WelcomeMenu();
    char option = '0';
    std::cout<<"请选择初始化数据库的方法:"<<std::endl;
    std::cout<<"1.从文件data.txt中读取;"<<std::endl;
    std::cout<<"2.手动输入;"<<std::endl;
    while(option != '2'&& option != '1') {
        InputWithCorrection(option);
    }
    if(option == '1'){
        ReadFile();
    }
    else if(option == '2'){
         std::cout << "请输入考生人数：" << std::endl;
        int stduentNum = 0;
        InputWithCorrection(stduentNum);
        while (stduentNum <= 0) {
            std::cout << "请输入合理的考生人数" << std::endl;
            InputWithCorrection(stduentNum);
        }
        //std::cout<<stduentNum<<"***"<<std::endl;
        InputMenu();
        Student t;
        for (int i = 0; i < stduentNum; i++) {
            std::cin >> t;
            Insert(i, t);
        }
    }
}

void DataSystem::revocation() {
    ReadFile();
}