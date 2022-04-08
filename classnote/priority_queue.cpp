
//functor, set, map, multimap, priority_queue

#include <iostream>
#include <set>
#include <map>
#include <functional>//to use the key word function
#include <queue> //priority_queue -- heap
#include <string>
#include <vector>
#include <list>
#include <algorithm>


using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	ThreeD() { ht = wid = dep = 0; }
	int vol() const { return ht * wid * dep; }
	bool operator<(const ThreeD& t) const { return vol() < t.vol(); }
};

ostream& operator<< (ostream& str, const ThreeD& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}


bool f1(int i, int j) { return i < j; }
bool f2(string s1, string s2) {
	return s1 < s2;
}

int min1(int a, int b, bool (*func)(int i, int j)) {//function pointer
	return func(a, b) ? a : b;
}

int min2(int a, int b, function<bool(int a, int b)> func) {//handles all callables
	return func(a, b) ? a : b;
}

template <typename T> int min3(int a, int b, T func) {//handles all callables; most commonly used
	return func(a, b) ? a : b;
}
class myCompareClass {
public:
	string s1;
	myCompareClass(string s) { s1 = s; }
	myCompareClass() {}
	bool operator()(int i, int j) const { return i % 3 < j % 3; }
	bool operator()(const string& s2) const { return s2 < s1; }
	bool operator()(const ThreeD& t1, const ThreeD& t2) const { return t1.ht + t1.wid + t1.dep < t2.ht + t2.wid + t2.dep; }
	bool operator()(const vector<int>& V1, const vector<int>& V2) const;
};
bool myCompareClass::operator()(const vector<int>& V1, const vector<int>& V2) const {
	
	//return V1.size() < V2.size();
	int num1{ 0 }, num2{ 0 };
	for (auto& i : V1) num1 += i;
	for (auto& i : V2) num2 += i;
	return num1 < num2;

}

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const list <T>& L);
int main() {
	myCompareClass m1;
	cout << m1(3, 5) << endl;//1  true
	cout << min1(3, 5, f1) << " " << min1(3, 5, [](int a, int b) {return a < b; }) << endl;
	cout << min2(3, 5, f1) << " " << min2(3, 5, [](int a, int b) {return a < b; }) << " " << min2(3, 5, m1) << endl;//functor is also supported
	cout << min3(3, 5, f1) << " " << min3(3, 5, [](int a, int b) {return a < b; }) << " " << min3(3, 5, m1) << endl;//functor is also supported
	string s1{ "CIS554" };
	myCompareClass m2{ "CIS554" };
	cout << f2("MAT295", "CIS554") << " " << [s1](string s2) {return s2 < s1; }("MAT295") << " " << m2("MAT395") << endl;
	//lambda can capture variables in the scope and functor can access local data members; thus, both are considered to have state.
	//regular functions do not contain state.

	set<int> S1{ 3,4, 1, 2, 5 };//1,2,3,4,5
	for (auto& i : S1) cout << i << " ";
	cout << endl;
	//the same as 
	//set<int, less<int>> S1{3,4,1,2,5};


	/*
	template <typename T> class less {

	public:

	bool operator()(T a, T b) {return a<b;  }



	template <typename T> class greater {

	public:

	bool operator()(T a, T b) {return a>b;}




	*/


	set<int, myCompareClass> S2{ 3,4, 1, 2, 5 };//3 1 2
	for (auto& i : S2) cout << i << " "; // only 3 1 2 got printed 4, 5 are the same as 1 and 2 after %5 operation
	cout << endl;
	ThreeD t1{ 3,4, 5 }, t2{ 3, 3, 3 }, t3{ 4, 4, 4 }, t4{ 2,3,4 };

	set<ThreeD> S3{ t1, t2, t3, t4 };//compare using vol to sort
	for (auto& i : S3) cout << i << " ";
	cout << endl;
	cout << "*************" << endl;
	set<ThreeD, myCompareClass> S4{ t1, t2, t3, t4 };//use the compare functor to sort

	for (auto& i : S4) cout << i << " ";
	cout << endl;

	map< ThreeD, int, myCompareClass> M1{ {t1, 1}, {t2, 2}, {t3, 3}, {t4, 4} };//use the compare functor to sort

	for (auto& i : M1) {
		cout << i.first << " " << i.second << "  ";
	} //note that only two elements got printed; the other two have the same values and thus be removed from M1
	cout << endl;
	cout << "&&&&&&&&&&&&&&&" << endl;
	priority_queue<int> PQ1;
	for (auto& i : { 3,2,5,4,1 }) { PQ1.push(i); }

	while (!PQ1.empty()) {
		cout << PQ1.top() << " ";
		PQ1.pop();
	}//5 4 3 2 1   a max heap
	cout << endl;
	priority_queue<int, vector<int>, greater<int> > PQ2;//default is less<int>
	for (auto& i : { 3,2,5,4,1 }) { PQ2.push(i); }

	while (!PQ2.empty()) {
		cout << PQ2.top() << " ";
		PQ2.pop();
	}//1 2 3 4 5   a min heap

	cout << "\n";
	map<vector<int>, list<int>, myCompareClass> M10{
		{  {1,2,3,4,5,6,7}, {11,11,12} }, {{7,8,9,10},{33,44,55,66,77}  }, { {99,101,74},{ 3,4,5,6,7}  }
	};

	//map< map<vector<int *> *, list<vector<int *>,   >>>    
	for (auto& i : M10) cout << i.first << " " << i.second << "   ";
	//for (auto [i, j] : M10) cout << i << " " << i << "   "; // Need C++ 2017
	cout << endl;
	multiset<int> MS1{ 3,2,4,7,4,2,1,7 };//1 2 2 4 4 7 7 ; sorted and allows duplicates

	auto ret{ MS1.equal_range(4) };//return a pair of itertors for the matched range  pointing to the first 4 and the first 7
	for_each(ret.first, ret.second, [](auto i) {cout << i << " "; });

	multiset<ThreeD, myCompareClass> MS2{ t1,t2,t3, t4, t1,t4 };
	for (auto& i : MS2) cout << i << " ";
	cout << endl;
	//equal_range applis to multimap as well.



	bool (*fp1)(int i, int j);//fp1 is a function pointer
	fp1 = f1;//function name without argument is the address of function in memory
	fp1 = &f1;//The same; address of f1;  older usage
	fp1 = *f1;//the same; address of f1;
	fp1 = ********f1; //the same;  OK but don't use it.
	//fp1 = && f1; //error.
	int A[]{ 3,4,5 };
	cout << A[2] << " " << 2[A] << endl; //ok but don't use 2[A]

	return 0;
}


template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto& i : V) str << i << " ";
		str << "]";
		return str;
}
template <typename T> ostream& operator<<(ostream& str, const list <T>& L) {

	str << "< ";
	for (auto& i : L) str << i << " ";
	str << ">";
	return str;
}