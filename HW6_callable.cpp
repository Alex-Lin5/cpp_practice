//CIS554 HW6 Due: 11:59pm, Monday, April 11.
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <functional>

using namespace std;

class myCompareClass {
public:
	myCompareClass() {}
	bool operator()(int i, int j) const { return i<=j; }

};

class myFunctorClass {
public:
	myFunctorClass() {}
	bool operator()(const list<int*>* L1, const list<int*>* L2) const;
	bool operator()(const map < list<int*>*, vector<int*>, myFunctorClass>& M1,
	 	const map < list<int*>*, vector<int*>, myFunctorClass>& M2) const;

};

void Sort(vector<int>& obj, function<bool(int, int)> callable);
bool f1(int i, int j);
bool myRegFunction(const map < list<int*>*, vector<int*>, myFunctorClass > M1,
	const map < list<int*>*, vector<int*>, myFunctorClass > M2);
template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const list<T>& L);
template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V);
template <typename T> ostream& operator<<(ostream& str, const list<T*>*& L);
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L);
template <typename T1, typename T2, typename T3> ostream& operator<<(
	ostream& str, const map<T1, T2, T3>& M);

int main() {
	/*
	Write a bubble_sort function, Sort, which takes two arguments:
	a reference to vector<int> and a callable. (See how Sort is called in code below.)
	When the callable is a lambda, the result of sorting is in descending order.
	When the callable is a functor, the result of sorting is in ascending order.
	When the callable is a regular function, the result of sorting is an ascending mod 5 sequence.
	Also see the sample screenshot.
	*/
	vector<int> a1{ 10,2,0,14,43,25,18,1,5,45 };
	for (const auto& i : a1) { cout << i << " "; }
	cout << endl;
    auto SomeLambda = [](int a, int b) {return a>=b;};
	Sort(a1, SomeLambda);//You need to implement the lambda
	for (const auto& i : a1) { cout << i << " "; }
	cout << endl;
	vector<int> a2{ 10,2,0,14,43,25,18,1,5,45 };
	for (const auto& i : a2) { cout << i << " "; }
	cout << endl;
	Sort(a2, myCompareClass{});
	for (const auto& i : a2) { cout << i << " "; }
	cout << endl;

	vector<int> a3{ 10,2,0,14,43,25,18,1,5,45 };
	for (const auto& i : a3) { cout << i << " "; }
	cout << endl;
	Sort(a3, f1);//You need to implement f1.
	for (const auto& i : a3) { cout << i << " "; }
	cout << endl;




	/*
	Remember that map will always sort elements by comparing the first part of each element (i.e., the key part).
	Implement functors in class myFunctorClass classes to allow the following map declaration to work.
	In both classes, when comparing two keys, count the sums of all int values at all levels, and compare the sums.
	*/
	map<map<list<int*>*, vector<int*>, myFunctorClass>, int, myFunctorClass> M1
	{

		{   {
				{ new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}}   },
				{ new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{100}}   }
			} , 50
		},


		{	{
				{ new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}}   },
				{ new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{200}}   }
			} , 100
		}
	};
	//Implement the needed overloading operator<< to support the following printing.
	cout << M1 << endl;
	cout << endl;


	///*
	//For the following, implement the functions used
	//in sorting the list elements using regular funciton, functor, and lambda in the three cases.
	//Similar to the case of map, we will compare the sums of int values at all levels.
	//In addition, you need to implement the needed overloaded operator<< to supporting the printing.
	//*/
	list<map < list<int*>*, vector<int*>, myFunctorClass >> L1{ {
	 			{
	 				new list<int*>{new int{10}, new int{20}, new int{30} } ,
	 				{new int{20}, new int{400}}
	 			},

	 			{
	 				new list<int*>{new int{40}, new int{20}, new int{30} }   ,
	 				{new int{20}, new int{40}, new int{100}}
	 			}
	 	} , {
	 			{
	 				new list<int*>{new int{10}, new int{20}, new int{30} } ,
	 				{new int{20}, new int{40}}
	 			},

	 			{
	 				new list<int*>{new int{40}, new int{20}, new int{30} }   ,
	 				{new int{20}, new int{40}, new int{200}}
	 			}
	 } };

	cout << L1 << endl;
	L1.sort(myRegFunction);//???: use a regular function
	cout << L1 << endl;
	cout << endl;

	list<map < list<int*>*, vector<int*>, myFunctorClass >> L2{ {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					{new int{20}, new int{400}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					{new int{20}, new int{40}, new int{100}}
				}
		} , {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					{new int{20}, new int{40}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					{new int{20}, new int{40}, new int{200}}
				}
	} };
	cout << L2 << endl;
	L2.sort(myFunctorClass());//???: use a functor 
	cout << L2 << endl;
	cout << endl;

	list<map < list<int*>*, vector<int*>, myFunctorClass >> L3{ {
					{
						new list<int*>{new int{10}, new int{20}, new int{30} } ,
						{new int{20}, new int{400}}
					},

					{
						new list<int*>{new int{40}, new int{20}, new int{30} }   ,
						{new int{20}, new int{40}, new int{100}}
					}
		} , {
					{
						new list<int*>{new int{10}, new int{20}, new int{30} } ,
						{new int{20}, new int{40}}
					},

					{
						new list<int*>{new int{40}, new int{20}, new int{30} }   ,
						{new int{20}, new int{40}, new int{200}}
					}
	} };

	cout << L3 << endl;
	auto myLambda = [](map < list<int*>*, vector<int*>, myFunctorClass> M1, 
		map < list<int*>*, vector<int*>, myFunctorClass> M2){
		int pool1{ 0 }, pool2{ 0 };
		for (const auto& i : M1) {
			for (auto& j : *(i.first)) { pool1 += *j; }
			for (auto& j : i.second) { pool1 += *j; }
		}
		for (const auto& i : M2) {
			for (auto& j : *(i.first)) { pool2 += *j; }
			for (auto& j : i.second) { pool2 += *j; }
		}
		return pool1 < pool2;
	};
	L3.sort(myLambda);//???: use a lambda 
	cout << L3 << endl;

	return 0;
}
//The following is a sample screenshot
//You must follow the exact format to avoid penalty in grading.
/*

10 2 0 14 43 25 18 1 5 45
45 43 25 18 14 10 5 2 1 0
10 2 0 14 43 25 18 1 5 45
0 1 2 5 10 14 18 25 43 45
10 2 0 14 43 25 18 1 5 45
10 0 25 5 45 1 2 18 43 14


{ { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 100 ] } 50 { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } 100 }

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )
*/

// template <typename T> void Sort(vector<int> obj, T callable(int i, int j)) {
void Sort(vector<int>& obj, function<bool(int, int)> callable) {
    for(size_t i=0; i<obj.size()-1; i++){
		bool flag{0};
        for(size_t j=0; j<obj.size()-1; j++){
            //  cout << "i: " << i << ", " << "j: " << j << ". |" << obj;
            bool cmpv {callable(obj[j], obj[j+1])};
            if (!cmpv) {
				swap(obj[j], obj[j+1]);
				flag = 1;
			}
        }
		if (!flag) break;
    }

}

bool f1(int i, int j) {
	return i % 5 <= j % 5;
}

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (const T& ele : V) { str << ele << ' '; }
	//for (const& T ele : V) { str << ele << ' '; }
	str << "] ";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V) {
	str << "[ ";
	for (T* const& ele : V) { str << *ele << ' '; }
	//for (const& T ele : V) { str << *ele << ' '; }
	str << "] ";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "( ";
	//for (auto& ele : L) { str << ele << ' '; }
	for (const T& ele : L) { str << ele << " "; }
	str << ") ";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "( ";
	//for (auto& ele : L) { str << ele << ' '; }
	for (T* const& ele : L) { str << *ele << " "; }
	str << ") ";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const list<T*>*& L) {
	str << "( ";
	for (T* const& ele : *L) { str << *ele << ' '; }
	//for (const& T ele : *L) { str << *ele << ' '; }
	str << ") ";
	return str;
}
template <typename T1, typename T2, typename T3> ostream& operator<<(
	ostream& str, const map<T1, T2, T3>& M) {
	str << "{ ";
	for (auto& pr : M) {
		str << pr.first << "" << pr.second << "";
	}
	str << "} ";
	return str;
}
template <typename T1, typename T2, typename T3> ostream& operator<<(
	ostream& str, const map<T1*, T2, T3>& M) {
	str << "{ ";
	for (auto& pr : M) {
		str << *(pr.first) << "" << pr.second << "";
	}
	str << "} ";
	return str;
}
// 
//bool myRegFunction(map < list<int*>*, vector<int*>>& M1, map < list<int*>*, vector<int*>>& M2) {
bool myRegFunction(const map < list<int*>*, vector<int*>, myFunctorClass > M1,
	const map < list<int*>*, vector<int*>, myFunctorClass > M2) {

	int pool1{ 0 }, pool2{ 0 };
	for (auto& i : M1) {
		for (auto& j : *(i.first)) { pool1 += *j; }
		for (auto& j : i.second) { pool1 += *j; }
	}
	for (auto& i : M2) {
		for (auto& j : *(i.first)) { pool2 += *j; }
		for (auto& j : i.second) { pool2 += *j; }
	}
	return pool1 < pool2;
}

bool myFunctorClass::operator()(const list<int*>* L1, const list<int*>* L2) const {
	int pool1{0}, pool2{0};
	for (auto& i : *L1) { pool1 += *i; }
	for (auto& i : *L2) { pool2 += *i; }
	return pool1 < pool2;
}
 bool myFunctorClass::operator()(const map < list<int*>*, vector<int*>, myFunctorClass>& M1,
 	const map < list<int*>*, vector<int*>, myFunctorClass>& M2) const {
//bool myFunctorClass::operator()(const map < list<int*>*, vector<int*>>& M1,
//	const map < list<int*>*, vector<int*>>& M2) const {
	int pool1{ 0 }, pool2{ 0 };
	for (const auto& i : M1) {
		for (auto& j : *(i.first)) { pool1 += *j; }
		for (auto& j : i.second) { pool1 += *j; }
	}
	for (const auto& i : M2) {
		for (auto& j : *(i.first)) { pool2 += *j; }
		for (auto& j : i.second) { pool2 += *j; }
	}
	return pool1 < pool2;
}
