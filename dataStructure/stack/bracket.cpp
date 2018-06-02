//
// Created by liududu on 17-11-7.
//
#include <iostream>
#include "stack.h"
using namespace std;

bool isMatch(char m, char n){
    return (m == '(' && n == ')') || (m == '[' && n == ']');
}

int main (){
    Stack<char> bracket;
    int flag = 1;
    string str;
    char t;
    cin>>str;
    unsigned long length = str.length();
    for(unsigned long i = 0; i < length; i++){
        if(str[i] == '(' || str[i] == '[') {
            bracket.push(str[i]);
            continue;
        }
        if(isMatch(bracket.getTop(),str[i])) {
            bracket.pop();
            continue;
        }
        cout<<"不合法"<<endl;
        flag = 0;
        break;
    }
    if(flag) cout<<"合法"<<endl;
}
