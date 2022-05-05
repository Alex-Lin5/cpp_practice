
#include <iostream>
#include <deque>
#include <array>

using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k): ht(i), wid(j), dep(k){}
	ThreeD(): ht(0), wid(0), dep(0){}
	int vol() const{ return ht * wid * dep; }

	void* operator new(size_t size)
	{
		cout << "Overloading new operator with size: " << size << endl;
		//void* p = ::operator new(size);
		void * p = malloc(size);// will also work fine

		return p;
	}

	void operator delete(void* p)
	{
		cout << "Overloading delete operator " << endl;
		::delete ( p);

		//free(p);
	}



};
int main() {
	deque<int> dq1{ 1,2,3,4,5 };
	cout << dq1[2] << endl;//3
	dq1.push_back(10);
	dq1.push_front(100);
	dq1.pop_back();
	dq1.pop_front();
	for (auto& i : dq1) cout << i << " ";
	cout << endl;
	auto it{ dq1.begin() };
	it += 2;
	cout << *it << endl;

	array<int, 4> A1{ 1,2,3,4 };

	auto p1{ new ThreeD{1,2,3} };
	cout << p1->vol() << endl;
	delete p1;

	void* p2{ new int{4} };
	cout << *(int *) p2 << endl;
	cout << *static_cast<int*> (p2) << endl;


	return 0;
}