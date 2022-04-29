
#include <iostream>
#include <list>
#include <vector>

using namespace std;



int main() {

	//assign
	//no return value
	list<int> L1{ 10, 20, 30 };
	vector<int> V1{ 1,2,3,4,5 };
	L1.assign(V1.begin(), V1.begin() + 3);
	for (auto& i : L1) cout << i << " ";//1 2 3
	cout << endl;
	L1.assign(5, 100);
	for (auto& i : L1) cout << i << " ";//100 100 100 100 100
	cout << endl;
	list<int> L2{ 10,20, 30, 40, 50 };
	auto it{ ++L2.begin() };
	L1.assign(L2.begin(), ++it);
	for (auto& i : L1) cout << i << " ";//10 20
	cout << endl;
	int A[]{ 7,8, 9, 10, 11, 12 };
	L1.assign(A + 1, A + 5);
	for (auto& i : L1) cout << i << " ";//8 9 10 11
	cout << endl;

	//cbegin and cend
	list<int>::const_iterator cit{ L1.begin() };
	//equivalent to const int * p;  object pointd by p is const
	cout << *cit << endl;//8
	//*cit = 25;   Error.
	*L1.begin() = 25;

	auto cit2{ L1.cend() };
	cout << *(--cit2) << endl;

	//emplace_front  emplace_back
	//Simiarly to push_front and push_back except faster

	L1.emplace_back(50);
	for (auto& i : L1) cout << i << " ";// 25 9 10 11 50
	cout << endl;

	//insert and emplace: return value:  an interator pointing to the first of newly added
	L1.insert(L1.begin(), A, A + 3);
	for (auto& i : L1) cout << i << " ";//7 8 9 25 9 10 11 50
	cout << endl;

	L1.insert(L1.end(), 4, 1000);
	for (auto& i : L1) cout << i << " ";//7 8 9 25 9 10 11 50 1000 1000 1000 1000
	cout << endl;
	L1.insert(++L1.begin(), 1); //7 1 8 ....
	vector<int> V2{4, 5, 6};
	L1.insert(L1.begin(), V2.begin(), V2.end());

	for (auto& i : L1) cout << i << " ";//4 5 6 7 1 8 9 25 9 10 11 50 1000 1000 1000 1000
	cout << endl;

	auto it3{ L1.emplace(++L1.begin(), 11) };//4 11 5 ...
	for (auto& i : L1) cout << i << " ";//4 11 5 6 7 1 8 9 25 9 10 11 50 1000 1000 1000 1000
	cout << endl;
	cout << *it3 << endl; //11
	//it2 points to 11

	//erase
	//Return value: An iterator pointing to the element that followed the last element erased by the function call. 
	auto it5{ L1.begin() };
	advance(it5, 5);//it5 points to 1
	L1.erase(L1.begin(), it5);//1 8 9 
	for (auto& i : L1) cout << i << " ";//1 8 9 25 9 10 11 50 1000 1000 1000 1000
	cout << endl;
	auto it6{ L1.erase(it5) };
	cout << *it6 << endl;//8
	for (auto& i : L1) cout << i << " ";// 8 9 25 9 10 11 50 1000 1000 1000 1000
	cout << endl;

	//max_size: maximum number of list int elements

	cout << L1.max_size() << endl;

	L1.sort();
	for (auto& i : L1) cout << i << " ";// 
	cout << endl;
	list<int> L3{ 5,3,1,7,8 };
	L3.sort();
	for (auto& i : L3) cout << i << " ";//

	cout << endl;
	L1.merge(L3);
	for (auto& i : L1) cout << i << " ";// 1 3 5 7 8 8 9 9 10 11 25 50 1000 1000 1000 1000
	cout << endl;
	cout << L3.size() << endl;

	//operator=
	list<int> L4;
	L4 = L1;

	//remove: delete all elements of certain value
	//remove_if: remove all elements satifying the predicate (callable which returns bool)

	L1.remove(9);
	for (auto& i : L1) cout << i << " ";// 1 3 5 7 8 8 10 11 25 50 1000 1000 1000 1000
	cout << endl;

	L1.remove_if([](int i) { return  i % 5 == 0;    });

	for (auto& i : L1) cout << i << " ";// 1 3 7 8 8 11
	cout << endl;

	list<int>::reverse_iterator rit{ L1.rbegin() };
	for (auto rit = L1.rbegin(); rit != L1.rend(); ++rit) cout << *rit << " ";
	cout << endl;

	//crbegin, crend

	list<int>::const_reverse_iterator crit{ L1.crbegin() };
	cout << *crit << endl;
	//*crit = 200;
	*L1.rbegin() = 200;

	L1.reverse();
	for (auto& i : L1) cout << i << " ";// 200 8 8 3 2 1
	cout << endl;
	cout << "*********" << endl;
	L1.unique();//remove adjacent duplicates
	for (auto& i : L1) cout << i << " ";// 200 8 7 3 1
	cout << endl;
	L1.unique([](int i, int j) {  return i % 3 == j %3; });
	for (auto& i : L1) cout << i << " ";// 200 7 3 1
	cout << endl;

	list<int> L101{ 1, 2, 2, 2, 3, 4, 5,5,5,5, 6,6, 7, 8, 9, 1,2,3 };

	auto it101{ ++L101.begin()};//it101 points to first 2
	L101.unique();//1 2 3 4 5 6 7 8 9 1 2 3
	for (auto& i : L101) cout << i << " ";
	cout << endl;
	cout << *it101 << endl;

	//splice

	list<int> L102{ 1,2,3,4,5 }, L103{ 6, 7, 8, 9 };

	L102.splice(++L102.begin(), L103, --L103.end());
	for (auto& i : L102) cout << i << " ";//1 9 2 3 4 5
	cout << endl;
	for (auto& i : L103) cout << i << " ";//6 7 8
	cout << endl;
	L103.emplace_back(11);//6 7 8 11
	auto it103{ L103.begin() };
	advance(it103, 2);//it103 point to 8
	L102.splice(L102.begin(), L103, L103.begin(), it103);
	for (auto& i : L102) cout << i << " ";//6 7 1 9 2 3 4 5
	cout << endl;
	for (auto& i : L103) cout << i << " ";//8 11
	cout << endl;

	auto it104{ --L102.end() };
	L102.splice(++L102.begin(), L102, --it104, L102.end());
	for (auto& i : L102) cout << i << " ";//6 4 5 7 1 9 2 3
	cout << endl;

	list<int> L51{ 2,3,4,5 }, L52{ 3 };
	if (L51 < L52) cout << "L52 is greater" << endl;

	swap(L51, L52);
	for (auto& i : L51) cout << i << " ";
	cout << endl;
	for (auto& i : L52) cout << i << " ";

	L51.swap(L52); //L52.swap(L51); is the same. This is faster than swap (L51, L52);

	return 0;
}