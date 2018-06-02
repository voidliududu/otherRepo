//
// Created by liududu on 17-12-4.
//
#include <iostream>
#include <cstdlib>
#include "binary.h"
using namespace std;
BinaryTree<char> tree;
void createTree();
void postOrder();
void preOrder();
void middleOrder();

void print(char t){
    cout<<t;
}

int main () {
    int command;
    cout<<"";
    cout<<"tree>>";
    cin>>command;
    while(1) {
        switch (command) {
            case 1:
                createTree();
                break;
            case 2:
                preOrder();
                break;
            case 3:
                postOrder() ;
                break;
            case 4:
                middleOrder();
                break;
            case 0:
                exit(0);
                break;
        }
        cout << "tree>>";
        cin >> command;
    }
}

void createTree() {
    cout<<"正在创建树"<<endl;
    tree.createTree();
    cout<<"创建树结束"<<endl;
}
void postOrder() {
    cout<<"后序序列：";
    tree.postOrder(print);
    cout<<endl;
}
void preOrder() {
    cout << "前序序列：";
     tree.preOrder(print);
    cout << endl;
}
void middleOrder()
{
    cout << "中序序列：";
    tree.middleOrder(print);
    cout << endl;
}