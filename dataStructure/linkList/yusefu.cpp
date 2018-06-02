//
// Created by liududu on 17-10-25.
//
#include <iostream>
//#include "LinkList.h"
using namespace std;
/**
 * 参与约瑟夫问题的人
 * */
class Person{
private:
    string name;
    int token;
    Person* next;
public:
    Person(string name,int token,Person* next = NULL){
        this->name = name;
        this->token = token;
        this->next = next;
    }
    /**
     * 交互创建对象
     * */
    Person(bool flag = false){
        if(flag){
            cout<<"=输入名称=>";
            cin>>this->name;
            cout<<"=输入口令=>";
            cin>>this->token;
            next = NULL;
        }
    }
    /**
     * 出列
     * */
     int quit(){

    }
};

int main(){

}
