//
// Created by liududu on 17-12-26.
//
#include <cstdlib>
#include "LinkList.h"

void createList();
void deleteNode();
void addNode();
void findNode();
void printList();
LinkList<int> list;

int main() {
    cout<<"功能菜单"<<endl
        <<"1.创建链表"<<endl
        <<"2.删除节点"<<endl
        <<"3.添加节点"<<endl
        <<"4.查找节点"<<endl
        <<"5.打印链表"<<endl
        <<"0.退出"<<endl;
    int command;
    cin>>command;
    while(command != 0) {
        switch (command){
            case 1:
                createList();
                break;
            case 2:
                deleteNode();
                break;
            case 3:
                addNode();
                break;
            case 4:
                findNode();
                break;
            case 5:
                printList();
                break;
            case 0:
                exit(0);
            default:
                exit(0);
        }
        cout<<"list>>";
        cin>>command;
    }
}

void createList(){
    cout<<"开始创建链表"<<endl;
    list.createList();
    cout<<"创建链表结束"<<endl;
}

void deleteNode() {
    int  num ;
    cout<<"请输入要删除的节点"<<endl;
    cin>>num;
    list.drop(num);
}

void addNode() {
    try {
        int number, data;
        cout << "请输入要添加的节点的位置" << endl;
        cin >> number;
        cout << "请输入要添加节点的数据" << endl;
        cin >> data;
        list.insert(number, data);
        cout<<"添加成功"<<endl;
    } catch( OutOfBound e){
        cout<<"添加失败"<<endl;
        exit(0);
    }
}

void findNode() {
    int number;
    cout<<"请输入要查找的节点的序号"<<endl;
    cin>>number;
    node<int>* n = list.searchById(number);
    cout<<"该节点的数据为"<<n->getData()<<endl;
}
void printList() {
    cout<<"该链表为"<<endl;
    list.dump();
    cout<<endl;
}