//栈和队列之间相互模拟，jianzhioffer第59页
#ifndef QSTACK_TEST_H
#define QSTACK_TEST_H

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
class Qstack {
private:
	queue<T> queue1;
	queue<T> queue2;
public:
	void display();
	void push(const T& value);
	void pop();
};

template<class T>
void Qstack<T>::display() {
	if (queue1.size() > 0) {
		queue<T> q1(queue1);
		while (q1.size() > 0) {
			cout << q1.front() << " ";
			q1.pop();
		}
	}
	if (queue2.size() > 0) {
		queue<T> q2(queue2);
		while (q2.size() > 0) {
			cout << q2.front() << " ";
			q2.pop();
		}
	}
	cout << endl;
}


//注意这里在类模板外定义其成员函数的写法
template<class T>
void Qstack<T>::push(const T& value) {
	if (queue2.empty())
		queue1.push(value);
	else if (queue1.empty())
		queue2.push(value);
	else {}
}

template<class T>
void Qstack<T>::pop() {
	if (queue1.size() > 0) {
		while (queue1.size() > 1) {
			queue2.push(queue1.front());
			queue1.pop();
		}
		queue1.pop();
	}
	else if (queue2.size() > 0) {
		while (queue2.size() > 1) {
			queue1.push(queue2.front());
			queue2.pop();
		}
		queue2.pop();
	}
	else {}
	return;
}


template <typename T> 
class CQueue
{
public:
	void display();
	// 在队列末尾添加一个结点
	void appendTail(const T& node);

	// 删除队列的头结点
	void deleteHead();

private:
	stack<T> stack1;
	stack<T> stack2;
};

template<typename T>
void CQueue<T>::display() {
	stack<T> sq1(stack1);
	stack<T> sq2(stack2);
	while (sq2.size() > 0) {
		cout << sq2.top() << " ";
		sq2.pop();
	}
	while (sq1.size() > 0) {
		T data = sq1.top();
		sq1.pop();
		sq2.push(data);
	}
	while (sq2.size() > 0) {
		cout << sq2.top() << " ";
		sq2.pop();
	}
	cout << endl;
}
template<typename T>
void CQueue<T>::appendTail(const T& element)
{
	stack1.push(element);
} 

template<typename T>
void CQueue<T>::deleteHead()
{
	if(stack2.size()<= 0)
	{
		while(stack1.size()>0)
		{
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}
	if (stack2.size() > 0)
		stack2.pop();
	return;
}

#endif
