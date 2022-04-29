//Source.cpp


#include <iostream>
#include "Header.h"//cooy the code from Header.h
/*
Header files will be copied into calling source files during compile time.
All cpp files will be compiled independently into object files.
During run time, those object files will be combined together by linker to form an excuteable file.
*/

//Incremental compilation:
using namespace std;

extern int f1(int i);//for function extern is optional
extern int E; //extern is required



int main() {

	myClass m1{ 3,4 };
	cout << m1.Product() << endl;
	cout << f1(10, 20) << endl;
	cout << E * E << endl;


	return 0;
}


//Header.h
//header file usually only contains declaration of functions and classes (i.e., only prototype)
int f1(int i, int j);//funciton prototype
class myClass {//class prototype
public:
	int A;
	int B;
	int Product() const;
};

//Source1.cpp

#include <iostream>
#include "Header.h"

using namespace std;

static int  f2(int i, int j) {//static means f2 only to be used within current file
	return i * 8 + j * 10 + 100;
}

 int  f1(int i, int j) {//static means only to be used within current file
	return i * 8 + j * 10 + 100;
}
int myClass::Product() const {

	return A * B;
}

int E{ 100 };
