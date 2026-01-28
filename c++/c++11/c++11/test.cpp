#include"c++11.h"

void Fun(int& x) { cout << "左值引用:&x"<<endl; }
void Fun(int&& x) { cout << "右值引用:&&x"<<endl;}
void Fun(const int& x) { cout << "const 左值引用" << endl; }
void Fun(const int&& x) { cout << "const 右值引用" << endl; }

template<class T>
void Func(T&& t) { Fun(forward<T>(t)); }
int main()
{
	//c++11支持{}任何类型的初始化
		//int x1 = { 2 };
		//int x2 = 2;
		//string str = { "1111" };
		////甚至可以省略赋值符号=
		//int x3{ 12 };
		//string str{ "qq" };
		//int x1{ 10 };
		//int& x2{ x1 };
		//int&& x3{ 10 };
		//int&& x4{ move(x2) };
		//int& x7{ x3 };
	string s1{ "111212212" };
	const string& r1 = s1 + s1;
	string&& s2{ s1 + s1 };
	string s11 = "qweer";
	//右值引用不能引用左值，左值引用也是，但是左值引用加上const，右值引用加上move()可以
	/*string&& s3{ s11 };*/
	string s3{ move(s11) };

	return 0;
}