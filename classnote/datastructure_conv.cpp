
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>


using namespace std;


void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int>*>& DB2);//prototype

//ostream& operator<<(ostream& str, vector<list<int>>& v);
//ostream& operator<<(ostream& str, list<vector<int>*>& l);

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const vector<T *>& V);

template <typename T> ostream& operator<<(ostream& str, const list<T>& L);
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L);



int main() {

	vector<list<int>> DB1{ {1,2,3}, {4,5}, {6,7,8,9} };
	cout << DB1 << endl;
	list<vector<int>*> DB2;
	DB1_to_DB2(DB1, DB2);
	cout << DB2 << endl;



	initializer_list<initializer_list<int>>  I{ {1,2}, {3,4,5}, {6,7} };
	
	auto p1{ I.begin() };
	auto p2{ p1->begin() };
	//p1 is of type:  intializer_list<int> *
	//p2 is of type :  const int * 

	return 0;
}
template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (const auto& i : V) str << i << " ";
	str << "]";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const vector<T *>& V) {
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

//ostream& operator<<(ostream& str, list<vector<int>*>& l) {
//	for (auto& i : l) {
//		for (auto& j : *i) {
//			str << j << " ";
//		}
//		str << endl;
//	}
//	return str;
//}
//
//
//ostream& operator<<(ostream& str, vector<list<int>>& v) {
//	for (auto& i : v) {
//		for (auto& j : i) {
//			str << j << " ";
//		}
//		str << endl;
//	}
//	return str;
//}

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