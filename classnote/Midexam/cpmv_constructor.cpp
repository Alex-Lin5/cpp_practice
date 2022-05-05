#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;
class myClass {
public:
	vector<list<int*>*> Data;
	myClass() {}
	myClass(const initializer_list<initializer_list<int>>& I);
	myClass(const myClass& M);//Copy Constructor
	void operator=(const myClass& M); //Copy Assignment
	myClass(myClass&& M);//Move Constructor
	void operator=(myClass&& M); //move assignment
	~myClass();//Destructor
	myClass ThreeTimes();


};

myClass myClass::ThreeTimes() {
	myClass temp{ *this };
	for (auto& i : temp.Data) {
		for (auto& j : *i) {
			*j *= 3;
		}
	}
	cout << "ThreeTimes" << endl;
	return temp;
}

myClass::~myClass() {
	for (auto& i : Data) {
		for (auto& j : *i) {
			delete j;
		}
		delete i;
	}
	Data.clear();
	cout << "Destructor" << endl;
}

void myClass::operator=(myClass&& M) { //move assignment
	for (auto& i : Data) {
		for (auto& j : *i) {
			delete j;
		}
		delete i;
	}
	Data.clear();

	for (auto& i : M.Data) {
		Data.push_back(i);
		i = nullptr;
	}
	M.Data.clear();
	cout << "Move Assignment" << endl;
}


myClass::myClass(myClass&& M) {//Move Constructor
	for (auto& i : M.Data) {
		Data.push_back(i);
		i = nullptr;
	}
	M.Data.clear();
	cout << "Move Constructor" << endl;
}

void myClass::operator=(const myClass& M) { //Copy Assignment
	for (auto& i : Data) {
		for (auto& j : *i) {
			delete j;
		}
		delete i;
	}
	Data.clear();

	for (auto& i : M.Data) {
		list<int*>* p{ new list<int*> };
		for (auto& j : *i) {
			p->push_back(new int{ *j });
		}
		Data.push_back(p);
	}
	cout << "Copy Assignment" << endl;
}

myClass::myClass(const myClass& M) {//Copy Constructor
	for (auto& i : M.Data) {
		list<int*>* p{ new list<int*> };
		for (auto& j : *i) {
			p->push_back(new int{ *j });
		}
		Data.push_back(p);
	}
	cout << "Copy Constructor" << endl;
}

myClass::myClass(const initializer_list<initializer_list<int>>& I) {
	auto p1{ I.begin() };
	while (p1 != I.end()) {
		list<int*>* p{ new list<int*> {} };
		auto p2{ p1->begin() };
		while (p2 != p1->end()) {
			p->push_back(new int{ *p2 });
			++p2;
		}
		Data.push_back(p);
		++p1;
	}
	cout << "Initializer List" << endl;
}

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V);

template <typename T> ostream& operator<<(ostream& str, const list<T>& L);
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L);



int main() {
	myClass m1{ {1,2,3}, {4,5,6,7}, {8, 9, 10, 11, 12} };//Will call initializer list
	cout << m1.Data << endl;
	myClass m2{ m1 };
	cout << m2.Data << endl;
	myClass m3;
	m3 = m2;
	cout << m3.Data << endl;
	myClass m4;
	m4 = m3.ThreeTimes();
	cout << m4.Data << endl;



	//...


	return 0;
}



template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto& i : V) str << i << " ";
	str << "]";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V) {
	str << "[ ";
	for (auto& i : V) str << *i << " ";
	str << "]";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "< ";
	for (auto& i : L) str << i << " ";
	str << ">";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "< ";
	for (auto& i : L) str << *i << " ";
	str << ">";
	return str;
}