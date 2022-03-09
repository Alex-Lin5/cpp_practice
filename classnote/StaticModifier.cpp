//Static 
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

int global {0};//0 is default


class myClass {
public:
	static int Num_Objects;
	myClass() {
		++Num_Objects;
	}

	~myClass() {
		--Num_Objects;
	}

	static int get_Num_Objects() { return Num_Objects; }
};
int myClass::Num_Objects {0};


void f1(int k) {
	static int count{ 0 };
	count += k * k;

	cout << count << endl;
	//.....
}




int main() {

	myClass m1;
	myClass m2;

	cout << myClass::get_Num_Objects() << endl;
	cout << m1.get_Num_Objects() << endl;
	
	f1(1);//1
	f1(2);//1+2*2=5
	f1(3);//5+3*3 = 14
	f1(4);//14+4*4=30
	

	return 0;
}