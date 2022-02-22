//template
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;

template <class T = int> class ThreeD {//defualt T is int
	//template <typename T = int> will alos work
public:
	T ht;
	T wid;
	T dep;
	ThreeD(T i, T j, T k) { ht = 2 * i; wid = 2 * j; dep = 2 * k; }
	ThreeD() { ht = wid = dep = 0; }
	T vol() const { return ht * wid * dep; }
	T area() const;



	ThreeD operator+(ThreeD& t);
	T& operator[](int k);//return by reference (return the object not value)
	ThreeD operator++();//prefix
	ThreeD operator++(int NeverUsed);//postfix
	bool operator<(const ThreeD& t) const { return vol() < t.vol(); }
	//the first const protect t and the seocnd const protect *this.

	bool operator==(const ThreeD& t) const { return vol() == t.vol(); }

	 template <class X> friend ostream& operator<<(ostream& str, const ThreeD<X>& t);
	 template <class X> friend istream& operator>>(istream& str, ThreeD<X>& t);

};

template <class T> T ThreeD<T>::area() const {

	return 2(ht * wid + wid * dep + dep * ht);
}



template <class X> ostream& operator<<(ostream& str, const ThreeD<X>& t);

template <class X> istream& operator>>(istream& str, ThreeD<X>& t);


template <class X> ostream& operator<<(ostream& str, const vector<X>& V);
template <class X> ostream& operator<<(ostream& str, const vector<X *>& V);
template <class X> ostream& operator<<(ostream& str, const list<X>& L);
template <class X> ostream& operator<<(ostream& str, const list<X *>& L);

int main() {
	ThreeD<int> t1{ 2,3,4 };
	ThreeD<double> t2{ 1., 2.3, 9.1 };

	ThreeD<> t3{ 1,1,1 };//default is int

	cout << t1 << " " << t2 << " " << t3 << endl;


	vector<ThreeD<int>> V1{ ThreeD<int> {2,3,4}, ThreeD<int> {1,2,3}, ThreeD<int>{5,1,3}, ThreeD<int>{4,2,2} };
	cout << V1 << endl;
	vector<int> V2{ 1,2,3,4,5 };
	cout << V2 << endl;


	list<ThreeD<int>> L1{ ThreeD<int> {2,3,4}, ThreeD<int> {1,2,3}, ThreeD<int>{5,1,3}, ThreeD<int>{4,2,2} };
	cout << L1 << endl;
	list<int> L2{ 1,2,3,4,5 };
	cout << L2 << endl;





	vector<list<int>> V3{ {1,2,3}, {4,5},{6,7,8,9} };
	cout << V3 << endl;


	list<vector<int>*> L4{ new vector<int>{1,2, 3}, new vector<int>{ 4,5}, new vector<int>{6,7,8,9} };
	cout << L4 << endl;

	vector<list<int>*> V4{ new list<int>{1,2, 3}, new list<int>{ 4,5}, new list<int>{6,7,8,9} };
	cout << V4 << endl;


	vector<int*> V5{ new int {7}, new int {2}, new int {4} };
	cout << V5 << endl;


	//vector<list<vector<ThreeD<double>>>>> V6;
	//cout << V6 <<endl;


	return 0;
}

template <class X> ostream& operator<<(ostream& str, const list<X*>& L) {
	str << "< ";
	for (auto& i : L) str << *i << " ";
	str << ">";
	return str;

}

template <class X> ostream& operator<<(ostream& str, const vector<X *>& V) {
	str << "[ ";
	for (auto& i : V) str << *i << " ";
	str << "]";
	return str;
}


template <class X> ostream& operator<<(ostream& str, const vector<X>& V) {
	str << "[ ";
	for (auto& i : V) str << i << " ";
	str << "]";
	return str;
}

template <class X> ostream& operator<<(ostream& str, const list<X>& L) {
	str << "< ";
	for (auto& i : L) str << i << " ";
	str << ">";
	return str;
}

template <class X> ostream& operator<<(ostream& str, const ThreeD<X>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

template <class X> istream& operator>>(istream& str, ThreeD<X>& t) {
	str >> t.ht >> t.wid >> t.dep;
	return str;
}