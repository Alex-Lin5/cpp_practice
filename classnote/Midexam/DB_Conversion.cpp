
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

//Implement the following function
void DB1_to_DB2(list<vector<list<int>*>* >& DB1, vector<list<list<int*> >*>* pDB2);
template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const vector<T *>& V);

template <typename T> ostream& operator<<(ostream& str, const list<T>& L);
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L);
int main() {

	list<vector<list<int>*>* > DB1{ new vector<list<int>*> { new list<int> {1,2,3}, new list<int>{4,5,6,7}, new list<int>{8, 9}},
	new vector<list<int>*> { new list<int> {11,12,13}, new list<int>{14,15,16,17}, new list<int>{18, 19}},
		new vector<list<int>*> { new list<int> {21,22,23}, new list<int>{24,25,26,27}, new list<int>{28, 29}}
	
	};
	cout << DB1 << endl;
	vector<list<list<int*> >*>* pDB2{ new vector<list<list<int*> >*> {} };
	DB1_to_DB2(DB1, pDB2);
	cout << *pDB2 << endl;

	return 0;
}

void DB1_to_DB2(list<vector<list<int>*>* >& DB1, vector<list<list<int*> >*>* pDB2) {
	for (auto& i : *pDB2) {
		for (auto& j : *i) {
			for (auto& k : j) {
				delete k;
			}
		}
		delete i;
	}
	pDB2->clear();
	for (auto& i : DB1) {
		list<list<int*>>* p1{ new list<list<int*>> };
		for (auto& j : *i) {
			list<int*> L1;
			for (auto& k : *j) {
				L1.push_back(new int{ k });
			}
			p1->push_back(L1);
		}
		pDB2->push_back(p1);
	}




}

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto& i : V) str << i << " ";
	str << "]";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const vector<T *>& V) {
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