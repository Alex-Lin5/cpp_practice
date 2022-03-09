
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
//#include <typeinfo>  optional for VS2022


using namespace std;


void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int>*>& DB2);//prototype
void DB2_to_DB3(list<vector<int>*>& DB2, list<list<int*>*>& DB3);
void DB2_to_DB4(list<vector<int>*>& DB2, vector<vector<int >*>* pDB4);

//ostream& operator<<(ostream& str, vector<list<int>>& v);
//ostream& operator<<(ostream& str, list<vector<int>*>& l);

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V);

template <typename T> ostream& operator<<(ostream& str, const list<T>& L);
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L);

void f1(int* p) {//call by value and call by reference gives 
	//same result in this case.

	*p = 200;
}


int main() {

	vector<list<int>> DB1{ {1,2,3}, {4,5}, {6,7,8,9} };
	cout << DB1 << endl;
	list<vector<int>*> DB2;
	DB1_to_DB2(DB1, DB2);
	cout << DB2 << endl;

	list<list<int*>*> DB3;
	DB2_to_DB3(DB2, DB3);
	cout << DB3 << endl;

	vector<vector<int >*>* pDB4{ new vector<vector<int>*>{} };
	DB2_to_DB4(DB2, pDB4);
	cout << *pDB4 << endl;



	/*initializer_list<initializer_list<int>>  I{ {1,2}, {3,4,5}, {6,7} };

	auto p1{ I.begin() };
	auto p2{ p1->begin() };
	cout << p1 << " " << p2 << endl;
	cout << typeid(p1).name() << "  " << typeid(p2).name() << endl;*/



	//p1 is of type:  intializer_list<int> *
	//p2 is of type :  const int * 



	int w{ 2 };
	int* p{ &w };
	f1(p);
	cout << w << endl;//200


	return 0;
}
template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (const auto& i : V) str << i << " ";
	str << "]";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V) {
	str << "< ";
	for (const auto& i : V) str << *i << " ";
	str << ">";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "< ";
	for (const auto& i : L) str << i << " ";
	str << ">";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "[ ";
	for (const auto& i : L) str << *i << " ";
	str << "]";
	return str;
}



void DB2_to_DB4(list<vector<int>*>& DB2, vector<vector<int >*>* pDB4) {
	//Clean up DB4
	for (auto& i : *pDB4) {
		delete i;//delete vector<int> *
	}
	pDB4->clear();

	//Copying DB2 to DB4
	for (auto& i : DB2) {
		vector<int>* p1{ new vector<int> {} };
		for (auto& j : *i) {//*i is vector<int>
			p1->push_back(j);
		}
		pDB4->push_back(p1);//p1 is of type vector<int> *
	}
}
void DB2_to_DB3(list<vector<int>*>& DB2, list<list<int*>*>& DB3) {
	//clean up dB3
	for (auto& i : DB3) {
		for (auto& j : *i) {
			delete j;//delete int *
		}
		delete i;//delete list<int *> *
	}
	DB3.clear();
	//copying from DB2 to DB3
	for (auto& i : DB2) {
		list<int*> * p1{ new list<int*>{} };
		for (auto& j : *i) {
			p1->push_back(new int{ j });
		}
		DB3.push_back(p1);
	}
}

void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int>*>& DB2) {
	//empty DB2
	for (auto& i : DB2) { delete i; }//dynamic objects need to be removed
	DB2.clear();

	for (auto& i : DB1) {
		vector<int>* p1 = new vector<int>;
		for (auto& j : i) {
			p1->push_back(j);
		}
		DB2.push_back(p1);//DB2.emplace_back(p1); is faster
	}
}