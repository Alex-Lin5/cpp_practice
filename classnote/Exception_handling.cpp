//exception handling
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <string>

using namespace std;


void test(double x) {

	cout << "Enter test" << endl;
	if (x == 0) throw "Error";
}

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() {}
	ThreeD(int i, int j, int k) : ht(i), wid(j), dep(k) {}
	int vol() const {
		cout << typeid(this).name() << endl;
		const_cast<ThreeD*>(this)->ht = 100;;
		return ht * wid * dep;
	}


};
struct MyException : public exception {
	const char* what() const throw () {
		return "C++ Exception";
	}
};

class MyError : public runtime_error {
public:
	MyError(const string& msg = "") : runtime_error(msg) {}
};

int main() {
	/*char C[] = "ABCD";
	const char* C2 = "ABCD";
	char const* C3 = "EFGH";*/



	try {
		int dadsage = 35, sonsage = 20;
		if (dadsage < sonsage) throw 99; //will be caught by catch (int x)
		else cout << "OK" << endl;

		double i = 32.5, j = 0;
		if (j == 0) throw "Error"; //will be caught by catch(char const* s)
		cout << i / j;
	}
	catch (int x) {
		//catch all int message thrown in the try block
		cout << "Son can't be older than Dad!" << "Error code : " << x << endl;
	}
	catch (string s) { cout << "cannot divide by 0" << endl; } //string s does not work.
	//Catch all string message thrown

	catch (...) {}; //Catch all messages not caught by earlier catch blocks.
			//Note that "..." is official keyword

	try { //we can invoke a function in a try block and throw exception in the function
		double jj = 45.2, k = 0;
		test(k);
		cout << "OK";
	}
	catch (const char* s) { cout << "New cannot divide by 0" << endl; }

	try {
		throw out_of_range("Vector V out of range");

	}
	catch (exception& e) {

		cout << e.what() << endl;
	}


	try {
		throw MyException();
	}
	catch (MyException& e) {
		std::cout << "MyException caught" << std::endl;
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		//Other errors
	}


	try {
		throw MyError("my message");
	}
	catch (MyError& x) {
		cout << x.what() << endl;
	}


	return 0;

}






/*
Some error message used by the system

1
std::exception

An exception and parent class of all the standard C++ exceptions.

2
std::bad_alloc

This can be thrown by new.

3
std::bad_cast

This can be thrown by dynamic_cast.

4
std::bad_exception

This is useful device to handle unexpected exceptions in a C++ program.

5
std::bad_typeid

This can be thrown by typeid.

6
std::logic_error

An exception that theoretically can be detected by reading the code.

7
std::domain_error

This is an exception thrown when a mathematically invalid domain is used.

8
std::invalid_argument

This is thrown due to invalid arguments.

9
std::length_error

This is thrown when a too big std::string is created.

10
std::out_of_range

This can be thrown by the 'at' method, for example a std::vectorand std::bitset<>::operator[]().

11
std::runtime_error

An exception that theoretically cannot be detected by reading the code.

12
std::overflow_error

This is thrown if a mathematical overflow occurs.

13
std::range_error

This is occurred when you try to store a value which is out of range.

14
std::underflow_error

This is thrown if a mathematical underflow occurs.

*/

/*
logic_error
	invalid_argument
	domain_error
	length_error
	out_of_range
	future_error(C++11)
bad_optional_access(C++17)
runtime_error
	range_error
	overflow_error
	underflow_error
	regex_error(C++11)
	system_error(C++11)
		ios_base::failure(C++11)
		filesystem::filesystem_error(C++17)
	tx_exception(TM TS)
	nonexistent_local_time(C++20)
	ambiguous_local_time(C++20)
	format_error(C++20)
bad_typeid
bad_cast
	bad_any_cast(C++17)
bad_weak_ptr(C++11)
bad_function_call(C++11)
bad_alloc
	bad_array_new_length(C++11)
bad_exception
ios_base::failure(until C++11)
bad_variant_access(C++17)
*/