//
// Created by liududu on 17-11-7.
//
#include <iostream>
#include "stack.h"

using namespace std;
int main(){
    Stack<int> oct;
    int dec;
    cin>>dec;
    while(dec != 0){
        while (dec >= 8){
            oct.push(dec % 8);
            dec = dec / 8;
        }
        oct.push(dec);
        while(oct.length()){
            cout<<oct.pop();
        }
        cout<<endl;
        cin>>dec;
    }
}

