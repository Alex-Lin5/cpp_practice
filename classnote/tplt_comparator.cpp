//template specialization
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>

using namespace std;

class myFunctorClass {
public:
	bool operator()(const vector< int>& V1, const vector<int>& V2) const { return V1.size() < V2.size(); }


};

//less<T>
template<>
class less<vector<int>> {

public:
	bool operator()(const vector< int>& V1, const vector<int>& V2) const { return V1.size() < V2.size(); }

};


//hash
template<>
class hash<vector<int>> {
public:
	size_t operator()(const vector<int>& V) const {
		return hash<int>{}(V.size());
	}
};

//equal_to
template<>
class equal_to<vector<int>> {
public:
	bool operator()(const vector<int>& V1, const vector<int>& V2) const { return V1.size() == V2.size(); }

};



int main() {

	//default  map<key_type, value_type, less<key_type>

	map<vector<int>, int> M1;

	unordered_map<vector<int>, int>  UM1;//Will not need classes for hash and equal_to





	return 0;
}