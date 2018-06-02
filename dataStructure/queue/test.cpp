//
// Created by liududu on 17-11-6.
//
#include <iostream>
#include "queue.h"
using namespace std;

int main (){
    Queue<int> q(5);
    //cout<<q.isEmpty();
    try {
        cout<<q.length();
        q.enqueue(4);
        cout<<q.length();
        q.enqueue(3);
        cout<<q.length();
        q.enqueue(2);
        cout<<q.length();
        q.enqueue(1);
        cout<<q.length();
        q.enqueue(5);
        cout<<q.length();
        cout<<endl;
        //q.enqueue(6);
        cout << q.isEmpty();
        cout << q.dequeue();
        q.enqueue(9);
        cout << q.dequeue();
        cout << q.dequeue();
        cout << q.dequeue();
        cout << q.dequeue();
        cout << q.dequeue();
    }catch (QueueEmptyException){
        cerr<<"队列为空"<<endl;
    }catch (QueueOverFlowException){
        cerr<<"队列已满"<<endl;
    }
}
