#pragma once
#include"FamilyTree.h"

class ManageSystem{
public:
    ManageSystem(){init();};
    ~ManageSystem() {  };
    
    void init();
    void run();
    void PrintMenu();

    void AddFamily();
    void AddChild();
    void RemoveFamily();
    void ModifyName();

private:
    FamilyTree* ancestor;
};

void ManageSystem::init(){
    std::cout<<"首先建立一个家谱!"<<std::endl;
    std::cout<<"请输入祖先的姓名:"<<std::endl;

    std::string name;
    std::cin>>name;
    ancestor=new FamilyTree(name);
    std::cout<<"此家谱的祖先是:"<<name<<std::endl;
    return;
}

void ManageSystem::run() {
    PrintMenu(); 
    char opSign;
    std::cout << "请输入要选择的操作:";
    std::cin >> opSign;
    while (opSign != 'E') {
        switch (opSign) {
            case 'A': {
                //完善家谱
                AddFamily();
                break;
            }
            case 'B': {
                //添加家庭成员
                AddChild();
                break;
            }
            case 'C': {
                //解散局部家庭
                RemoveFamily();
                break;
            }
            case 'D': {
                //更改家庭成员姓名
                ModifyName();
                break;
            }
        }
        std::cout << "请输入要选择的操作:";
        std::cin >> opSign;
    }
}

void ManageSystem::PrintMenu() {
    std::cout << "**                  家谱管理系统                  **" << std::endl;
    std::cout << "====================================================" << std::endl;
    std::cout << "**              请选择要执行的操作:               **" << std::endl;
    std::cout << "**                  A --- 完善家庭                **" << std::endl;
    std::cout << "**                  B --- 添加家庭成员            **" << std::endl;
    std::cout << "**                  C --- 解散局部家庭            **" << std::endl;
    std::cout << "**                  D --- 更改家庭成员姓名        **" << std::endl;
    std::cout << "**                  E --- 推出程序                **" << std::endl;
}

void ManageSystem::AddFamily() {
    std::string name;
    std::cout<< "请输入要建立家庭的人的姓名:" << std::endl;
    std::cin >> name;
    FamilyNode* ptr = ancestor->SearchByName(name);
    if (ptr == NULL) {
        std::cout << "could not find " << name << std::endl;
        return;
    }

    int num;
    std::cout << "请输入" << name << "的儿女人数: " << std::endl;
    std::cin >> num;
    std::cout << "请依次输入" << name << "的儿子(女儿)的姓名: " << std::endl;
    std::string tempName;
    for (int i = 0; i < num; i++) {
        std::cout << "Input name here" << std::endl;
        std::cin >> tempName;
        FamilyNode* child = new FamilyNode(tempName);
        ptr->InsertJunior(child);
    }
    //std::cout << name << "的第一代子孙是:";
    //顺序输出name的第一代子孙
    ptr->PrintJunior();
    return;
}

void ManageSystem::AddChild() {
    std::cout << "请输入要添加儿子(或女儿)的人的姓名:";
    std::string name;
    std::cin >> name;
    FamilyNode* ptr = ancestor->SearchByName(name);
    if (ptr == NULL) {
        std::cout << "could not find " << name << std::endl;
        return;
    }

    std::cout << "请输入" << name << "新添加的儿子(或女儿)的姓名:";
    std::string child;
    std::cin >> child;
    FamilyNode* newChild = new FamilyNode(child);
    ptr->InsertJunior(newChild);
    ptr->PrintJunior();

    return;
}

void ManageSystem::RemoveFamily() {
    std::string name;
    std::cout << "请输入要解散家庭的人的姓名:";
    std::cin >> name;
    ancestor->RemoveByName(name);
    return;
}

void ManageSystem::ModifyName() {
    std::string name,newName;
    std::cout << "请输入要更改姓名的人的目前姓名:";
    std::cin >> name;
    FamilyNode* ptr = ancestor->SearchByName(name);
    if (ptr != NULL) {
        std::cout << "请输入更改后的姓名:";
        std::cin >> newName;
        ptr->SetName(newName);
        std::cout << name << "已改名为" << newName << std::endl;
    }
    return;
}