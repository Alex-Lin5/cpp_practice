
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;
//For all comparisons, compare the sums of all int objects in the key parts of structures.
//For all hashing, use h(sum of all int objects in the key parts of structures), where hash<int> h;

class myCompareClass {
public:
	bool operator()(const int* I1, const int* I2) const;
	
};

bool myCompareClass :: operator()(const int* I1, const int* I2) const {
	return *I1 < *I2;
}



template<class T, class J>ostream& operator<<(ostream& str, const map < T, J*>& M);
template<class T>ostream& operator<<(ostream& str, const list<T*>& L);
template<class T>ostream& operator<<(ostream& str, const vector<T>& V);
template<class T>ostream& operator<<(ostream& str, const vector<T*>* V);
template<class T>ostream& operator<<(ostream& str, const set<T*, myCompareClass>* S);
template<class T, class J>ostream& operator<<(ostream& str, const unordered_map<T, J>& UM);

template<>
class less<list<set<int*, myCompareClass>*>> {
public:
	bool operator()(const list<set<int*, myCompareClass>*>& L1,const list<set<int*, myCompareClass>*>& L2) const {
		int num1{ 0 }, num2{ 0 };
		for (auto& i : L1) {
			for (auto j : *i) 	num1 += *j;
		}
		for (auto& i : L2) {
			for (auto& j : *i) 	num2 += *j;
		}
		return num1 < num2;
	}

};


template<>
class hash<map < list<set<int*, myCompareClass>*>, vector<int*>* >> {
public:
	size_t operator()(const map <list<set<int*, myCompareClass>*>, vector<int*>*>& M) const {
		
		int num1 = 0;
		for (auto& i : M) {
			for(auto& j : i.first){
				for (auto& k : *j) num1 = num1 + *k;
			}
			for (auto& j : *i.second) num1 += *j;
		}
		return hash<int>{}(num1);
	}
};

template<>
class equal_to<map <list<set<int*, myCompareClass>*>, vector<int*>*>> {
public:
	bool operator()(const map <list<set<int*, myCompareClass>*>, vector<int*>*>& M1, const map <list<set<int*, myCompareClass>*>, vector<int*>*>& M2) const {
		int num1 = 0,num2=0;
		for (auto& i : M1) {
			for (auto& j : i.first) {
				for (auto& k : *j) num1 = num1 + *k;
			}
			for (auto& j : *i.second) num1 += *j;
		}


		for (auto& i : M2) {
			for (auto& j : i.first) {
				for (auto& k : *j) num2 = num2 + *k;
			}
			for (auto& j : *i.second) num2 += *j;
		}
		return num1 == num2;
	}

};



int main() {
	//The following won't run. Fix it.
	//In addition, create your initialized values. For each STL container, at least three elements are required.
	//Overload operator<< to allow "cout << H1 << endl;"
	unordered_map< map < list<set<int*, myCompareClass>*>, vector<int*>* >, vector<int>> UM{
{
{{
{ new set<int*, myCompareClass>{ new int{3},new int{5},new int{7} } ,new set<int*, myCompareClass>{ new int(2),new int(5),new int(8) } ,new set<int*, myCompareClass>{ new int(3),new int(6), new int(11) } }
, new  vector<int*> { new int(7) ,new int(19),new int(13) }
}
,
{
{ new set<int*, myCompareClass>{ new int(3),new int(5),new int(17) } ,new set<int*, myCompareClass>{ new int(3),new int(5),new int(8) } ,new set<int*, myCompareClass>{ new int(1),new int(3), new int(6) } }
, new  vector<int*> { new int(4) ,new int(14),new int(3) }
}
,
{
{ new set<int*, myCompareClass>{ new int(1),new int(7),new int(13) } ,new set<int*, myCompareClass>{ new int(1),new int(2),new int(15) } ,new set<int*, myCompareClass>{ new int(6),new int(16), new int(20) } }
, new  vector<int*> { new int(5) ,new int(19),new int(4) }
}}
, {7 ,8, 9 }
}


,
{
{{
{ new set<int*, myCompareClass>{ new int(3),new int(5),new int(7) } ,new set<int*, myCompareClass>{ new int(2),new int(5),new int(8) } ,new set<int*, myCompareClass>{ new int(3),new int(6), new int(11) } }
, new vector<int*> { new int(7) ,new int(11),new int(3) }
}
,
{
{ new set<int*, myCompareClass>{ new int(3),new int(5),new int(17) } ,new set<int*, myCompareClass>{ new int(3),new int(5),new int(8) } ,new set<int*, myCompareClass>{ new int(1),new int(3), new int(6) } }
, new vector<int*> { new int(4) ,new int(14),new int(3) }
}
,
{
{ new set<int*, myCompareClass>{ new int(3),new int(4),new int(5) } ,new set<int*, myCompareClass>{ new int(2),new int(5),new int(18) } ,new set<int*, myCompareClass>{ new int(2),new int(6), new int(13) } }
, new vector<int*> { new int(5) ,new int(11),new int(13) }
}}
, {1, 2 ,3 }
}

,
{
{{
{ new set<int*, myCompareClass>{ new int(5),new int(6),new int(13) } ,new set<int*, myCompareClass>{ new int(3),new int(4),new int(5) } ,new set<int*, myCompareClass>{ new int(3),new int(9), new int(11) } }
, new  vector<int*> { new int(4) ,new int(14),new int(3) }
}
,
{
{ new set<int*, myCompareClass>{ new int(5),new int(7),new int(13) } ,new set<int*, myCompareClass>{ new int(1),new int(11),new int(15) } ,new set<int*, myCompareClass>{ new int(3),new int(6), new int(8) } }
, new  vector<int*> { new int(5) ,new int(12),new int(3) }
}
,
{
{ new set<int*, myCompareClass>{ new int(3),new int(4),new int(13) } ,new set<int*, myCompareClass>{ new int(2),new int(5),new int(12) } ,new set<int*, myCompareClass>{ new int(2),new int(13), new int(16) } }
, new  vector<int*> { new int(5) ,new int(17),new int(2) }
}}
, {3, 5 ,7 }
}
	}	;
	cout << UM << endl;
	return 0;
}


//unordered_map< map < list<set<int*, myCompareClass>*>, vector<int*>* >, vector<int>> UM

template<class T, class J>ostream& operator<<(ostream& str, const map < T, J*>& M) {
	str << "\n{ ";
	for (auto& i : M) str << i.first << " " << i.second << " ";
	str << "\n}";
	return str;
}
template<class T, class J>ostream& operator<<(ostream& str,const unordered_map<T, J>& UM) {
	str << "{";
	for (auto& i : UM) str << i.first << " " << i.second << " ";
	str << "\n}";
	return str;
}
template<class T>ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "[ ";
	for (auto& i : L) str << i << " ";
	str << " ]";
	return str;
}
template<class T>ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "( ";
	for (auto& i : V) str << i << " ";
	str << " )";
	return str;
}
template<class T>ostream& operator<<(ostream& str, const vector<T*>* V) {
	str << "( ";
	for (auto& i :  *V) str << *i<<" ";
	str << " )";
	return str;
}
template<class T>ostream& operator<<(ostream& str, const set<T*, myCompareClass>* S) {
	str << "< ";
	for (auto& i : *S) str << *i << " ";
	str << " >";
	return str;
}