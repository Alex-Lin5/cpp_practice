//Operator Overloading
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k) { ht = 2 * i; wid = 2 * j; dep = 2 * k; }
	ThreeD() { ht = wid = dep = 0; }
	int vol() const { return ht * wid * dep; }
	ThreeD operator+(ThreeD& t);
	int& operator[](int k);//return by reference (return the object not value)
	ThreeD operator++();//prefix
	ThreeD operator++(int NeverUsed);//postfix
	bool operator<(const ThreeD& t) const { return vol() < t.vol(); }
	//the first const protect t and the seocnd const protect *this.

	bool operator==(const ThreeD& t) const { return vol() == t.vol(); }

	friend ostream& operator<<(ostream& str, const ThreeD& t);
	friend istream& operator>>(istream& str, ThreeD& t);

};


ThreeD ThreeD::operator++(int NeverUsed) {//postfix
	ThreeD temp{ *this };
	ht++;
	wid++;
	dep++;
	return temp;

}

ThreeD  ThreeD::operator++() {//prefix
	++ht;
	++wid;
	++dep;
	return *this;//this is a pointer pointing to the current object

}


ThreeD ThreeD::operator+(ThreeD& t) {
	ThreeD temp;
	temp.ht = ht + t.ht;
	temp.wid = wid + t.wid;
	temp.dep = dep + t.dep;
	return temp;
}

int& ThreeD::operator[](int k) {//
	switch (k) {
	case 0: return ht;
	case 1: return wid;
	case 2: return dep;
	}
}


void f2(const int& k) {//k will be read only pass by reference

	cout << k * k << endl;
	//k++;  Error!
}


ostream& operator<<(ostream& str, const ThreeD& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

istream& operator>>(istream& str, ThreeD& t) {
	str >> t.ht >> t.wid >> t.dep;
	return str;
}




int main() {

	ThreeD t1{ 1,2,3 };
	ThreeD t2{ 3,4,5 };
	ThreeD t3;
	//system("pause");
	/*cout << "Enter anything to continue" << endl;
	cin.get();*/

	t3 = t1 + t2;//
	/*
	Compiler will change it into:

	t3 = t1.operator+(t2);
	*/

	cout << t3[2] << endl;//return the dep of t3
	t3[1] = 25;// t3.wid = 25;
	/*compiler will change it to
	cout << t3.operator[](2) << endl;
	*/
	ThreeD t5;
	t5 = ++t1;//prefix
	cout << t1 << "  " << t5 << endl;

	t5 = t1++;//postfix
	cout << t1 << "  " << t5 << endl;


	//string s1, s2;
	//int k3;
	//cin >> s1 >> k3 >> s2;
	//cout << s1 << " " << k3 << " " << s2 << endl;


	/*cin >> t5;
	cout << t5 << endl;*/




	int w1{ 2 };
	const int* p1{ &w1 };//int const * p1 {w2};
	cout << *p1 << endl; //2
	//*p1 = 4;  Error!  The object pointed by p1 is const, but p1 is not const
	w1 = 5;

	int w2{ 9 };
	p1 = &w2;

	int* const p2{ &w2 };
	cout << *p2 << endl;//9
	*p2 = 29;
	//p2 = &w1; Erro!  p2 is const, but not the object pointed by p2.

	const int* const p3{ &w1 };
	//p3 = &w2;  Error. p3 is const.
	//*p3 = 55;  Erroir. object pointed by p3 is also const.


	int& x{ w1 };//x is a nickname of w1
	//Only one object.  This object has two names: x and w1.

	w1 = 100;
	x = 100;

	const int& y{ w2 };
	w2 = 45;
	//y = 55;  Error  object reference through y is const

	int w3{ 44 };
	//ThreeD t7 {3,4,5}

	set<ThreeD> S5{ ThreeD{3,4,5}, ThreeD{4,4,4}, ThreeD{2,3,4}, ThreeD{5,1,9}, ThreeD{3,3,3} };
	//anonymous ThreeD objects

	for (auto& i : S5) cout << i << " ";
	cout << endl;

	map<ThreeD, int> M5{ {ThreeD{3,4,5},10}, {ThreeD{4,4,4},12}, {ThreeD{2,3,4},5},
		{ThreeD{5,1,9},21}, {ThreeD{3,3,3},4} };

	for (auto& i : M5) cout << i.first << " " << i.second << "  ";
	cout << endl;

	auto it8{ M5.find(ThreeD{1,4,6}) };
	if (it8 != M5.end()) cout << it8->first << " " << it8->second << endl;//(4,6,8) 5
	return 0;

	/*
	->    select
	cout <<  put to  output;   << : left shift
	cin  >>   get from  input   >> : right shift
	*/
}