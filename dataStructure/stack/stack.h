//
// Created by liududu on 17-11-5.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H
class StackEmptyException{};
class StackOverflowException{};
template <class T>
class Stack{
private:
    T* stack;
    int top;
    int maxsize;
//    todo 优化判断
    bool isFull(){
        return this->top == (maxsize - 1);
    }
public:
    /**
     * 构造函数，初始化栈空间
     * @param maxsize 最大栈空间
     * todo add exception handler
     * */
    Stack(int maxsize = 20){
        this->stack = new T[maxsize];
        this->maxsize = maxsize;
        this->top = -1;
    }
    /*×
     * 判断栈是否为空
     * @return bool
     * */
    bool isEmpty(){
        return this->top == -1;
    }
    int length(){
        return top + 1;
    }
    /**
     * 进栈
     * @param data
     * @return bool
     * */
    void push(T data) {
        if (isFull())
            throw StackOverflowException();
        stack[++top] = data;
    }
    /**
     * 出栈
     * @return T
     * */
    T pop(){
        if(isEmpty())
            throw StackEmptyException();
        return stack[top--];
    }
    T getTop(){
        if(isEmpty())
            throw StackEmptyException();
        return stack[top];
    }
    /**
     * 析构
     * */
    ~Stack(){
        delete[] stack;
    }
};
#endif //DATASTRUCTURE_STACK_H
