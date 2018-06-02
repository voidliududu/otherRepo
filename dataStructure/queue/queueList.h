//
// Created by liududu on 17-11-8.
//

#ifndef DATASTRUCTURE_QUEUELIST_H
#define DATASTRUCTURE_QUEUELIST_H
class QueueEmptyException{};
template <class T> class QueueList;
template <class T>
class node{
    friend class QueueList<T>;
private:
    node<T> *pre;
    node<T> *next;
public:
    T data;
    node(){
        T data();
        pre = NULL;
        next = NULL;
    }
    node(T data){
        this->data = data;
        pre = NULL;
        next = NULL;
    }
};

template <class T>
class QueueList{
private:
    node<T>* head;
    node<T>* tail;
public:
    QueueList(){
        head = new Node<int>();
        tail = head;
    }
    /**
     * 判断队列是否为空
     * @return bool
     * */
    bool isEmpty(){
        return head == tail;
    }
    /**
     * 入队
     * @param data
     * */
    void enqueue(T data){
        tail->next = new node<T>(data);
    }
    /**
     * 出队
     * @param void
     * @return T
     * */
    T dequeue(){
        if(isEmpty())
            throw QueueEmptyException();
        node<T> *temp = head->next;
        delete head;
        head = temp;
        return head->data;
    }
};

#endif //DATASTRUCTURE_QUEUELIST_H
