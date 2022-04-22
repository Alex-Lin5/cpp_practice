//HW7. Due: Wednesday, April 20 at 11:59pm
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
	myCompareClass(){}
	bool operator()(int* p1, int* p2) const { return *p1<*p2;}
};

 template<> 
 class less<map<list<set<int*, myCompareClass>*>, vector<int*>*>> {
 public:
 	bool operator()(const map<list<set<int*, myCompareClass>*>, vector<int*>*>& M1,
 		const map<list<set<int*, myCompareClass>*>, vector<int*>*>& M2) const {
 		int left{ 0 }, right{ 0 };
 		for (auto& pr : M1) {
 			for (auto& S : pr.first) {
 				for (auto& i : *S)
 					left += *i;
 			}
 		}
 		for (auto& pr : M2) {
 			for (auto& S : pr.first) {
 				for (auto& i : *S)
 					right += *i;
 			}
 		}
 		return left < right;
 	}
 };

 template<> 
 class equal_to<map < list<set<int*, myCompareClass>*>, vector<int*>* >> {
 public:
 	bool operator()(const map < list<set<int*, myCompareClass>*>, vector<int*>* >& M1,
 		const map < list<set<int*, myCompareClass>*>, vector<int*>* >& M2) const {
 		int left{ 0 }, right{ 0 };
        for (auto& pr : M1) {
            for (auto& S : pr.first) {
                for (auto& i : *S)
                    left += *i;
            }
            for (auto& i : *(pr.second))
                left += *i;
        }
        for (auto& pr : M2) {
            for (auto& S : pr.first) {
                for (auto& i : *S)
                    right += *i;
            }
            for (auto& i : *(pr.second))
                right += *i;
        }

 		return left == right;

 	}
 };

 template<>
 class hash< map < list<set<int*, myCompareClass>*>, vector<int*>* >>{
 public:
 	size_t operator()(const  map < list<set<int*, myCompareClass>*>, vector<int*>*> & M) const {
 		int source{ 0 };
        for (auto& pr : M) {
            for (auto& S : pr.first) {
                for (auto& i : *S)
                    source += *i;
            }
            for (auto& i : *(pr.second))
                source += *i;
        }
        return hash<int>{}(source);
 	}
 };

// ostream& operator<<(ostream& str, const unordered_map< map < list<set<int*, myCompareClass>*>, vector<int*>* >, vector<int>> UM);

template <typename T> ostream& operator<<(ostream& str, const set<T*, myCompareClass>* Spt);
template <typename T> ostream& operator<<(ostream& str, const vector<T*>& Vpt);
template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const list<T*>& Lpt);
template <typename T1, typename T2> ostream& operator<<(ostream& str, const map <T1, T2*>& M);
template <typename T1, typename T2> ostream& operator<<(ostream& str, const unordered_map<T1, T2>& UM);

int main() {
//The following won't run. Fix it.
//In addition, create your initialized values. For each STL container, at least three elements are required.
//Overload operator<< to allow "cout << H1 << endl;"
	unordered_map< map < list<set<int*, myCompareClass>*>, vector<int*>* >, vector<int>> UM{
        //pair<map<list<set<int*>*, myCompareClass>, vector<int*>*>, vector<int>>
       {
            //map<list<set<int*>*, myCompareClass>, vector<int*>*>
            {
               //pair<list<set<int*>*, myCompareClass>, vector<int*>*>
               {
                    //list<set<int*>*, myCompareClass>
                    {
                        new set<int*, myCompareClass>{new int{9}, new int{22}, new int{15}},
                        new set<int*, myCompareClass>{new int {42}, new int{29}, new int {82}},
                        new set<int*, myCompareClass>{new int{93}, new int{3}, new int{90}}
                    },
                    new vector<int*>{new int{2}, new int{3}, new int{62}}
                }

            },
        //vector<int>
        {35, 66, 20}
    	},
        //pair<map<list<set<int*>*, myCompareClass>, vector<int*>*>, vector<int>>
       {
            //map<list<set<int*>*, myCompareClass>, vector<int*>*>
            {
               //pair<list<set<int*>*, myCompareClass>, vector<int*>*>
               {
                    //list<set<int*>*, myCompareClass>
                    {
                        new set<int*, myCompareClass>{new int{9}, new int{22}, new int{15}},
                        new set<int*, myCompareClass>{new int {2}, new int{0}, new int {82}},
                        new set<int*, myCompareClass>{new int{93}, new int{3}, new int{9}}
                    },
                    new vector<int*>{new int{2}, new int{3}, new int{2}}
                }

            },
        //vector<int>
        {35, 6, 22}
    	},
        //pair<map<list<set<int*>*, myCompareClass>, vector<int*>*>, vector<int>>
       {
            //map<list<set<int*>*, myCompareClass>, vector<int*>*>
            {
               //pair<list<set<int*>*, myCompareClass>, vector<int*>*>
               {
                    //list<set<int*>*, myCompareClass>
                    {
                        new set<int*, myCompareClass>{new int{99}, new int{22}, new int{15}},
                        new set<int*, myCompareClass>{new int {42}, new int{9}, new int {82}},
                        new set<int*, myCompareClass>{new int{3}, new int{3}, new int{90}}
                    },
                    new vector<int*>{new int{2}, new int{1}, new int{62}}
                }

            },
        //vector<int>
        {35, 663, 20}
    	},
    };
	cout << UM << endl;
	return 0;
}
/*
The following is a possible output.
Depending on the initialization values you select, the output values will be different.
However, do follow the same format for set, map, vector and list.
{
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 19 13 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 1 7 13 > < 1 2 15 > < 6 16 20 > ]
( 5 19 4 ) } ( 7 8 9 )
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 11 3 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 3 4 5 > < 2 5 18 > < 2 6 13 > ] ( 5 11
13 ) } ( 1 2 3 )
{ [ < 5 6 13 > < 3 4 5 > < 3 9 11 > ] ( 4 14 3 ) [ < 5 7 13 > < 1 11 15 > < 3 6 8 > ] ( 5 12 3 ) [ < 3 4 13 > < 2 5 12 > < 2 13
16 > ] ( 5 17 2 ) } ( 3 5 7 )
}
*/
ostream& operator<<(ostream& str, const unordered_map< map < list<set<int*, myCompareClass>*>, vector<int*>* >, vector<int>>& UM) {
    str << "{\n";
    for (auto& pr1 : UM) {
        str << "{ ";
        for (auto& pr2 : pr1.first) {
            str << "[ ";
            for (auto& S : pr2.first) {
                str << "< ";
                for (auto& i : *S)
                    str << *i << " ";
                str << "> ";
            }
            str << "] ( ";
            for (auto& i : *(pr2.second))
                str << *i << " ";
            str << ") ";
        }
        str << "} ( ";
        for (auto& i : pr1.second)
            str << i << " ";
        str << ")\n";
    }
    str << "}\n";
    return str;
}

template <typename T> ostream& operator<<(ostream& str, const set<T*, myCompareClass>& S) {
	str << "< ";
	for (auto& i : S)
		str << *i << " ";
	str << "> ";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const set<T*, myCompareClass>* Spt) {
	str << "< ";
	for (auto& i : *Spt)
		str << *i << " ";
	str << "> ";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const vector<T*>& Vpt) {
	str << "( ";
	for (auto& i: Vpt)
		str << *i << " ";
	str << ") ";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "( ";
	for (auto& i: V)
		str << i << " ";
	str << ") ";
	return str;
}
template <typename T> ostream& operator<<(ostream& str, const list<T*>& Lpt) {
	str << "[ ";
	for (auto& i: Lpt)
		str << *i << " ";
	str << "] ";
	return str;
}
 template <typename T1, typename T2> ostream& operator<<(ostream& str,
 	const map <T1, T2*>& M) {
 	str << "{ ";
 	for (auto& pr : M) {
 		str << pr.first << " " << *(pr.second) << " ";
 	}
 	str << "}";
 	return str;
 }
template <typename T1, typename T2> ostream& operator<<(ostream& str,
	const unordered_map<T1, T2>& UM) {
	str << "{\n";
	for (auto& pr: UM)
		str << pr.first << " " << pr.second << "\n";
	str << "}";
	return str;
}
