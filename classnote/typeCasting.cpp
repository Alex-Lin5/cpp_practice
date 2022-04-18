//dynamic casting
#include <iostream>
#include <string>
using namespace std;


class B {//base class

	int b1 = 1;
protected:
	int b2 = 2;
public:
	int b3 = 3;
	void f1() {
		cout << "B::f1" << endl;
	}
	virtual void f2() { //virtual member function can be redefined in the derived class
		cout << "B::f2" << endl;
		cout << b3 * b3 << endl;
	}
};

class D : public B {

	int d1 = 4;
protected:
	int d2 = 5;
public:
	int d3 = 6;
	void f2() {
		cout << "D::f2" << endl;
		cout << d3 * d3 << endl;
	}
};


class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k): ht(i), wid(j), dep(k){}
	ThreeD() { ht = wid = dep = 0; }
	int vol() const{
		if (ht == 25) { const_cast<ThreeD *>(this  )->ht = 30; }
		//wid = 15;
		return ht * wid * dep;
	
	}
	//type of this is  const ThreeD* 

	explicit operator int() { return ht + wid + dep; }
	//with explicit keyword, only explict casting is allowed
	//Without explicit keyword, both explicit and implicit casting allowed
	operator string() { return "this is a ThreeD object"; }
};



int main() {

	//C raw typecasting
	float f1{ 3.15 };    //Implicitly casting 3.15, which is double to float  3.15f is float
	float f2{ (float)3.15 }; //explicitly casting 3.15 to float.
	float f3{ static_cast<float>(3.15) }; //explicitly casting 3.15 to float using C++ static casting


	//Note that static_cast should replace the raw type casting from C
	//They are both performed in compile time.  However, static_cast is safer; it will check more
	//possible problems.  See the following example.

	//In most cases, static cast of C++ work just like raw casting in C.
	//Only in some rare cases, difference can be found.  The following is one such case.

	short* p100 = new short{ 100 }; //short is 2 bytes
	short* p200 = new short{ 200 };
	int* p300 = (int*)p100; //No error detected, but is wrong.
	//int* p400 = static_cast<int*>(p100); Error.





	D o1;
	B* p3 = static_cast<B*>(&o1); //upcasting
	D* p4 = dynamic_cast<D*>(p3); //downcasting
	if (!p4) cout << "p4 is nullptr" << endl; //p4 is not nullptr; 
	else { //This else part will be executed
		//p4 has access to b3, d3, f1 and f2
		p4->f1();//prints B::f1
		p4->f2();//prints B::f2 and, in the next line, 9
		cout << p4->d3 << endl;//prints 12515912 (just something arbitrary)
	}

	//const_cast

	ThreeD t1{ 5,6,7 }, t2{25,8,1};
	cout << t1.vol() << " " << t2.vol() << endl;//5*6*7  30*8*1


	double d3{  2.15f };//implicit casting from float to double
	double d4{ static_cast<double>(2.15f) };//explcit casting from float to double
	double d5{ (double)2.15f };//explict casting using raw C casting format

	//User defined type casting

	//int i5 = t1;//5+6+7  Error! implict casting from ThreeD to int
	int i5 = (int)t1;//explicit
	cout << i5 << endl;

	string s3;
	s3 = t1;
	cout << s3 << endl;



	double d5 = 35;//no error. no warning
	int i10 = 3.567;//no error, but warning

	int* p = new int(65);
	char* ch = reinterpret_cast<char*>(p);
	cout << *p << endl;
	cout << *ch << endl;
	cout << p << endl;
	cout << ch << endl; //Note that *ch and ch give the same results



	return 0;
}