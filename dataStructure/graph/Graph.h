//
// Created by liududu on 17-12-26.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include <iostream>
class Graph;
using namespace std;

class EdgeNode {
public:
    int data;
    EdgeNode* next;
    EdgeNode(int data,EdgeNode* t = NULL){
        this->data = data;
        this->next = t;
    }
};
template <typename T>
class Node {
    T data;
    EdgeNode* next;
public:
    friend class Graph<T>;
    Node(T data = 0,EdgeNode *next = NULL) {
        this->data = data;
        this->next = next;
    }

    void setData(T data){
        this->data = data;
    }

    void setNext(EdgeNode* next) {
        this->next = next;
    }
};
template <typename T>
class Graph{
    Node<T>* t;
public:
    Graph(){
        t = NULL;
    };
    void Create(int count) {
        this->t = new Node<T>[count];
        T data;
        while(count > 0) {
            cin>>data;
            t[count-1].setData(data);
            count --;
        }
    }
    void setEdge(int num1,int num2) {
        EdgeNode* it = this->t[num1].next;
        while(it -> next != NULL)
            it = it->next;
        it->next = new EdgeNode(num2);
        it = this->t[num2].next;
        while(it -> next != NULL)
            it = it->next;
        it->next = new EdgeNode(num1);
    }
    void DFS() {

    }

    void BFS() {

    }
    ~Graph(){

    }
};


#endif //DATASTRUCTURE_GRAPH_H
