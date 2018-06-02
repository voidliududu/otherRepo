//
// Created by liududu on 17-10-23.
//

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H
//#ifdef CITY
#define FINISH 0;
//#endif
//#elif 1
//#define FINISH 0
//#endif
#include <iostream>
/**
 * 模板类需要重载 << >>  ==运算符
 * */
using namespace std;
class OutOfBound{};

template <class T>  class node;
/**
 * 实现单链表的操作(使用头节点)
 * @tparam T
 * */
template <class T>
class LinkList{
private:
    node<T>* head;
public:
    /**
     * 创建链表
     * */
    void createList(){
        T t;
        node<T> *p1, *p2;
        this->head =new  node<T>(t, NULL);
        p1 = head;
        cin>>t;
        while(t != 0){
            p2 = new node<T>(t, NULL);        //todo 异常处理
            p1->next = p2;
            p1 = p2;
            cin>>t;
        }
    }
    /**
     * 在第n个节点之后插入节点
     * @param n int
     * @param data T
     * @return LinkList<T>*
     * */
    LinkList<T>* insert(int n,T data){
        node<T> *p = this->head->next;
        for(int i = 1;i < n;i++ )
            p = p->next;
        if(n < 1 || p == NULL)
            throw OutOfBound();
        p->next = new node<T>(data,p->next);
        return this;
    }
    /**
     * 删除第n个节点之后的节点
     * @param n int
     * @return LinkList<T>*
     * */
    LinkList<T>* drop(int n){
        node<T> *p = this->head->next,*q = NULL;
        for(int i = 1;i < n;i++ )
            p = p->next;
        if(n < 0 || p == NULL)
            throw OutOfBound();
        q = p->next;
        p->next = p->next->next;
        delete q;
        return this;
    }
    /**
     * 查找，返回是否找到
     * @param k int
     * @param data T&
     * @return bool
     * */
    bool find(int k,const T& data) const {
        node<T> *p = this->head->next;
        for(int i = 1;i < k-1;i++ )
            p = p->next;
        if(k < 1 || p == NULL)
            throw OutOfBound();
        return p->next->data == data;
    }
    /**
     * 通过序号查找
     * */
    node<T>* searchById(int k){
        node<T> *p = this->head->next;
        for(int i = 1;i < k;i++ )
            p = p->next;
        if(k < 0 || p == NULL)
            throw OutOfBound();
        return p;
    }
    /**
     * 通过data域搜索，返回第一个满足条件的
     * @param const T&
     * @return node<T> *
     * */
    node<T>* search(const T& data){
        node<T> *p = this->head->next;
        while(p != NULL){
            if(p->data == data)
                return p;
            p = p->next;
        }
        return NULL;
    }
    /**
     * 统计链表长度
     * */
    int length(){
        int count = 0;
        node<T> *p = head->next;
        while(p != NULL){
            count ++;
            p = p->next;
        }
        return count;
    }
    /**
     * 追加
     * */
    void append(T data){
        int length = this->length();
        if(length == 0)
            head->next = new node<T>(data);
        else{
            insert(length,data);
        }
    }
    /**
     * dump当前链表的信息
     * */
    void dump(){
        //cout<<"length => "<<length();
        node<T> *p = this->head->next;
        int i = 1;
        while(p != NULL){
            cout<<" => "<<p->data;
            p = p->next;
            i++;
        }
    }
    /**
     * 析构
     * */
    ~LinkList(){
        node<T> *p = head,*q = NULL;
        while(p != NULL){
            q = p->next;
            delete p;
            p = q;

        }
    }
};

/**
 * 节点模板，实现对数据元素的操作
 * @tparam T
 * */
template <class T>
class node{
    friend class LinkList<T>;
private:
    T data;
    node<T>* next;
public:
    /**
     * 用指针初始化节点
     * @param node node<T>*
     * */
    node(node<T>* node){
        this->next = node;
    }
    /**
     * 用数据初始化节点
     * @param data T*
     * */
    node(const T& data,node<T>* next = NULL){
        this->data = data;
        this->next = next;
    }
    /**
     * 获取数据域
     * @return T
     * */
    T& getData(){
        return this->data;
    }
    /**
     * 获取指针域
     * @return node<T>
     * */
    node<T> getNext(){
        return this->next;
    }
    /**
     * 设置数据域
     * @param data const T&
     * */
    void setData(const T& data){
        this->data = data;
    }
    /**
     * 设置指针域
     * */
    void setNext(node<T>* next){
        this->next = next;
    }
};
#endif //DATASTRUCTURE_LINKLIST_H
