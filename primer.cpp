#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <math.h>
#include <typeinfo>
#include <algorithm>
#include <functional>
using namespace std;


class A {
public:
	A(int var = -1) {
		
	}
	int m_nPub;
protected:
	int m_nPtd;
private:
	int m_nPrt;
};

class B: public A {
public:
	int GetPub() {
		return m_nPub;
	}
	int GetPtd() {
		return m_nPtd;
	}
	/*int GetPrt() {
	return m_nPrt;
	}*/
};

class C: protected A {
public:
	int GetPub() {
		return m_nPub;
	}
	int GetPtd() {
		return m_nPtd;
	}
	/*int GetPrt() {
		return m_nPrt;
	}*/
};

class D: private A {
public:
	void set() {
		m_nPub = 0;
		m_nPtd = 1;
	}
	int GetPub() {
		return m_nPub;
	}
	int GetPtd() {
		return m_nPtd;
	}
	/*int GetPrt() {
		return m_nPrt;
	}*/
};

int main() {
	D d;
	d.set();
	cout << d.GetPtd() << endl;
	cout << d.GetPub() << endl;

}
//class A
//{ 
//protected:
//	int m_data;
//public:
//	A(int data = 0){m_data = data;} //构造函数
//	int GetData(){ return doGetData();}
//	virtual int doGetData(){return m_data;}
//	virtual void test() {cout << "dddd" << endl;}
//};
//
//class B : public A
//{
//protected:
//	int m_data;
//public:
//	B(int data =1){m_data = data;}//构造函数
//	int doGetData(){return m_data;}
//};
//
//class C:public B
//{
//protected:
//	int m_data;
//public:
//	C(int data = 2){m_data = data;}//构造函数
//};
//
//
//int main() {
//	A a;
//	a.test();
//	C c(10);
//	cout<<c.GetData()<<endl;
//	cout<<c.A::GetData()<<endl;
//	cout<<c.B::GetData()<<endl;
//	cout<<c.C::GetData()<<endl;
//
//	cout<<c.doGetData()<<endl;
//	cout<<c.A::doGetData()<<endl;
//	cout<<c.B::doGetData()<<endl;
//	cout<<c.C::doGetData()<<endl;
//}
//class Point {
//private:
//	double point_x;
//	double point_y;
//public:
//	Point(): point_x(0.0), point_y(0.0) {}
//	Point(double x, double y): point_x(x), point_y(y) {}
//	Point(const Point &rhs): point_x(rhs.point_x), point_y(rhs.point_y) {}
//	Point& operator=(const Point& rhs) {
//		point_x = rhs.point_x;
//		point_y = rhs.point_y;
//	}
//
//	double get_point_x() {
//		return this->point_x;
//	}
//	void set_point_x(double x) {
//		this->point_x = x;
//	}
//
//	double get_point_y() {
//		return this->point_x;
//	}
//	void set_point_y(double y) {
//		this->point_y = y;
//	}
//
//	friend double points_distance(Point &lhs, Point &rhs);
//};
//
//double points_distance(Point &lhs, Point &rhs) {
//	return sqrt((lhs.point_x - rhs.point_x) * (lhs.point_x - rhs.point_x) +
//		(lhs.point_y - rhs.point_y) * (lhs.point_y - rhs.point_y));
//}
////int main() {
////	Point p1;
////	cout << p1.get_point_x() << endl;
////
////	Point p2(2.0, 3.0);
////	cout << p2.get_point_y() << endl;
////
////	Point p3(3.0, 4.0);
////	printf("%lf\n", points_distance(p3, p2));
////}
//
//class Employee {
//public:
//	Employee(): name("Noname") {
//		set_id();
//	}
//	Employee(string employee_name): name(employee_name) {
//		set_id();
//	}
//	Employee(const Employee& other): name(other.name) {
//		set_id();
//	}
//	Employee& operator= (const Employee& rhs) {
//		name = rhs.name;
//		return *this;
//	}
//private:
//	string name;
//	string id;
//	static int counter;
//	void set_id() {
//		string id = string();
//		if (counter < 10)
//			id += "0000";
//		else if (counter < 100)
//			id += "000";
//		else if (counter < 1000)
//			id += "00";
//		else if (counter < 10000)
//			id += "0";
//		else {
//			cerr << "invalid employee id." << endl;
//		}
//		char buffer[5];
//		itoa(counter, buffer, 10);
//		id += buffer;
//		++counter;
//	}
//};
//int Employee::counter = 1;
//
//
//
//class A {
//	int data;
//public:
//	A() {
//		static const char sss[] = "sss";
//		cout << "\tA()" << endl;
//	}
//	A(const A & a) {
//		data = a.data;
//		cout << "\t复制构造函数" << endl;
//	}
//	~A() {
//		cout << "\t~A()" << endl;
//	}
//};
//
//A global;                     //调用构造函数
//
//A foo(A arg) { 
//	unique_ptr<string> ps(new string);
//	//调用复制构造函数，用arg初始化局部对象local
//	cout << "2---------------" << endl;
//	A local = arg;
//
//	//这里是复制初始化方式：先调用指定构造函数创建临时对象，然后
//	//用复制构造函数将临时对象复制到正在创建的对象。
//	//但是编译器一般会优化，直接跳过复制构造函数直接创建对象，
//	//所以这里并没有调用复制构造函数
//	cout << "3---------------" << endl;
//	A local2 = A();
//	cout << "4---------------" << endl;
//
//	A *heap = new A(global); //调用复制构造函数，根据全局对象global创建新的A对象
//
//	cout << "5---------------" << endl;
//	*heap = local;           //这句没有调用(复制)构造函数
//	cout << "6---------------" << endl;
//
//	// 这里两次调用复制构造函数，两次调用构造函数
//	//
//	A pa[4];// = {local, *heap};
//	cout << "7---------------" << endl;
//
//	return *heap;            //调用复制构造函数，从函数返回A对象*heap的副本
//}
//
//void func1(A &obj) {}
//
//void func2(A &myobj, A obj) {
//	A a1(myobj), b1(obj);
//}
//
////int main() {
////	A aa;        //调用构造函数
////	//foo(aa);     //调用复制构造函数，复制一个对象，将其作为实参传递给一个函数
////	A bb;
////	
////	cout << "81----------------" << endl;
////	//func1(aa);     //形参为类类型的引用，因此无需调用复制构造函数
////	cout << "82----------------" << endl;
////
////	//使用了五次默认构造函数和复制构造函数，先使用A的默认构造函数创建临时值
////	//来初始化avec，然后使用复制构造函数将临时值复制到avec的每个元素。
////	vector<A> avec(5);  
////	cout << "9----------------" << endl;
////	return 0;
////}