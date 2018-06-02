//
// Created by liududu on 17-11-5.
//
#include <iostream>
#include "stack.h"

using namespace std;

int main(){
    try {
        Stack<int> s(5);
        cout << s.isEmpty() << endl;
        s.push(1);
        s.push(2);
        s.push(3);
        s.push(4);
        s.push(5);
        cout << s.isEmpty() << endl;
        cout << s.pop();
        cout << s.pop();
        cout << s.pop();
        cout << s.pop();
        cout << s.pop();
        cout << s.pop();
    }catch (StackOverflowException){
        cerr<<"栈溢出"<<endl;
    }catch (StackEmptyException){
        cerr<<"空栈"<<endl;
    }
    return 0;
}
