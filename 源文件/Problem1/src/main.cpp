#include <iostream>
#include"SinglyLinkedList.h"
#include"Student.h"

int  main() {
    #ifdef WIN32
    system("chcp 65001");
    #endif
    Student t;
    DataSystem l;
    
   
    l.init();
    l.output();
    l.run();
    return 0;
}