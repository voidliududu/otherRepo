//
// Created by liududu on 17-11-8.
//
#include <iostream>
#include <cstdlib>
#include "stack.h"
using namespace std;

//商品货架和临时栈
Stack<string> cart;
Stack<string> temp;

/**
 * 商品进货架
 * @param item string
 * */
void shop_push(string item);
/**
 * 商品出货架
 * @param
 * */
string shop_pop();

int main (){
    string command;
    while(true){
        cin>>command;
        if(command == "push"){
            cout<<"please input the name of the item"<<endl;
            cin>>command;
            shop_push(command);
            cout<<"success"<<endl;
        }else if(command == "pop"){
            shop_pop();
            cout<<"success"<<endl;
        }else if(command == "print"){
            while(!cart.isEmpty())
                cout<<cart.pop()<<endl;
            exit(0);
        }
    }
}

void shop_push(string item){
        while(!cart.isEmpty()){
            temp.push(cart.pop());
        }
        cart.push(item);
        while(!temp.isEmpty()){
            cart.push(temp.pop());
        }
}

string shop_pop(){
    return cart.pop();
}
