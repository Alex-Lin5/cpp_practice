
//Smart pointers: 2 lectures
//Function Pointers, Callables (regular functions, lambda, functors): 2 lectures
//Class inheritance, virtual functions, etc. : 1-2 lectures
//Type casting: 1- 2 lectures
//Hash Table 1-2 lectures (unordered map, unorderer set)
//More STL, multi-file program, etc.

#include <iostream>
#include <memory> //smart pointers:  no delete allowed
#include <vector>
#include <list>

using namespace std;


int main() {
	int* p1{ new int{45} };//p1: raw pointers
	//Smart Pointers:  Unique pointers, Shared pointers, Weak pointers
	//All smart pointers will have default value of nullptr
	//delete function is not supported
	unique_ptr<int> up1{ make_unique<int>(10) };//faster; you should always use this.
	unique_ptr<int> up2{ new int{15} };//slower


	//unique_ptr<int> up3{ up1 }; //Error!  A unique object can only be pointed by one unique pointer.
	cout << *up1 << endl;//10
	up1.reset();//the same as up1 = nullptr;
	//Object 10 will be deleted automatically.
	//Object whose reference count (the number of pointers pointing at this object) is 0 will
	//be automatically deleted.

	up1.reset(new int{ 20 });

	shared_ptr<int> sp1{ make_shared<int>(5) };
	{
		shared_ptr<int> sp2{ sp1 };
		cout << sp1.use_count() << endl;//reference count is 2 (both sp1 and sp2)
	}
	//sp2 is out of scope
	cout << sp1.use_count() << endl;//reference count is 1; only sp1
	sp1.reset(new int{ 3 });
	//object 5 with reference count 0 will be automatically deleted.

	int* p2{ new int{22} };//p2 a raw pointer
	shared_ptr<int> sp3{ p2 };//both sp3 and p2 point to object 22.
	if (sp3.get() == p2) cout << "sp3 and p2 point to the same object" << endl;
	cout << *p2 << " " << *sp3 << " " << *sp3.get() << endl;//22 22 22
	sp3.reset(new int{ 11 });
	//Object 22 will be automatically deleted.  Raw pointers do not contribute to reference count.
	//cout << *p2 << endl;  Error!



	sp1.reset(); //sp1 = nullptr;

	weak_ptr<int> wp1{ sp3 };//wp1 and sp3 both point to object 11
	cout << sp3.use_count() << endl;//RC=1; weak pointers do not contribute to reference count.
	cout << *sp3 << endl;//11
	//cout << *wp1 << endl;  Error!  Weak pointers do not support * or -> operators
	cout << *wp1.lock() << endl;
	//lock() returns a temporary shared pointer pointing to the object wp1 points to.
	//sp1 = wp1;  Error.
	sp1 = wp1.lock();

	weak_ptr<int> wp3{ make_shared<int>(250) };
	//What does this do?
	//The object 250 pointed by wp3 will be immediatley deleted with RC=0;

	shared_ptr<list<int>> sp10{ make_shared<list<int>>(initializer_list<int>{1,2,3,4,5}) };
	for (auto& i : *sp10) cout << i << " ";
	cout << endl;

	shared_ptr<list< shared_ptr<int>>> sp11 {

	make_shared<list<shared_ptr<int>>>(initializer_list<shared_ptr<int>>{make_shared<int>(1), make_shared<int>(2)})
	};
	//list<int *> * p11;
	for (auto& i : *sp11) {
		cout << *i << " ";
	}
	cout << endl;

//list<int *> * p11;
	return 0;
}