//
// Created by liududu on 17-11-5.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H
class QueueEmptyException{};
class QueueOverFlowException{};
template <class T>
class Queue{
private:
    int head;
    int tail;
    int maxSize;
    T* queue;
public:
    /**
     * 初始化队列
     * */
    Queue(int maxSize = 20){
        this->queue = new T[maxSize + 1];
        this->head = 1;
        this->tail = 1;
        this->maxSize = maxSize + 1;
    }
    /**
     * 判断队列为空
     * @return bool
     * */
    bool isEmpty(){
        return head == tail;
    }
    /**
     * 判断队列为满
     * @return bool
     * */
    bool isFull(){
        return (head % maxSize) == ((tail + 1) % maxSize);
    }
    int length(){
        return tail - head;
    }
    /**
     * 入队
     * @param T data
     * @return bool
     * */
    void enqueue(T data){
        if(isFull())
            throw QueueOverFlowException();
        queue[(tail ++) % maxSize] = data;
    }
    /**
     * @return T
     * */
    T dequeue(){
        if(isEmpty())
            throw QueueEmptyException();
        return queue[(head ++) % maxSize];
    }
    ~Queue(){
        delete[] queue;
    }
};
#endif //DATASTRUCTURE_QUEUE_H
