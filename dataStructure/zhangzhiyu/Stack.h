//
// Created by liududu on 17-11-7.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

template<class Object>
class Stack
{
	public:
		Stack(int capacity);
		bool IsEmpty() const;
		bool IsFull() const;
		const Object & Top() const;

		void MakeEmpty() {top=-1;};
		void Pop();
		void Push(const Object &x);
		Object TopAndPop();
	protected:
		int MaxSize;
		int top;
		Object *theArray;
};

//栈的构造
template <class Object>
Stack<Object>::Stack(int capacity)
{
	MaxSize=capacity;
	top=-1;
 }

//判栈空
template<class Object>
bool Stack<Object>::IsEmpty() const
 {
 	return top==MaxSize-1;//如果满了则返回TRUE
  }

//入栈
template<class Object>
void Stack<Object>::Push(const Object &x)
{
	//当栈非满时插入x到栈顶，否则抛出异常
	if(IsFull())
		throw "overflow";
	theArray[++top]=x;
}

//出栈
 template <class Object>
 void Stack<Object>::Pop()
 {
 	if(IsEmpty())
 	throw "underflow";
 	//栈非空时删除栈顶，否则抛出异常
 	top--;

   }

//当栈为非空时返回栈顶元素并且出栈，否则抛出异常
template<class Object>
Object Stack<Object>::TopAndPop()
{
	if(IsEmpty())
	{
		throw "underflow";
	}
	return theArray[top--];
 }

template<class Object>
const Object & Stack<Object>::Top() const
{
	if(IsEmpty)
		throw "underflow";
	return theArray[top];
}


#endif //DATASTRUCTURE_STACK_H
