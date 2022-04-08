//CIS554 HW6 Due: 11:59pm, Monday, April 11.
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

int main() {
	/*
	Write a bubble_sort function, Sort, which takes two arguments:
	a reference to vector<int> and a callable. (See how Sort is called in code below.)
	When the callable is a lambda, the result of sorting is in descending order.
	When the callable is a functor, the result of sorting is in ascending order.
	When the callable is a regular function, the result of sorting is an ascending mod 5 sequence.
	Also see the sample screenshot.
	*/
	vector<int> a1{ 10,2,0,14,43,25,18,1,5,45 };
	for (const auto& i : a1) { cout << i << " "; }
	cout << endl;
	Sort(a1, SomeLambda);//You need to implement the lambda
	for (const auto& i : a1) { cout << i << " "; }
	cout << endl;
	vector<int> a2{ 10,2,0,14,43,25,18,1,5,45 };
	for (const auto& i : a2) { cout << i << " "; }
	cout << endl;
	Sort(a2, myCompareClass{});
	for (const auto& i : a2) { cout << i << " "; }
	cout << endl;

	vector<int> a3{ 10,2,0,14,43,25,18,1,5,45 };
	for (const auto& i : a3) { cout << i << " "; }
	cout << endl;
	Sort(a3, f1);//You need to implement f1.
	for (const auto& i : a3) { cout << i << " "; }
	cout << endl;




	/*
	Remember that map will always sort elements by comparing the first part of each element (i.e., the key part).
	Implement functors in class myFunctorClass classes to allow the following map declaration to work.
	In both classes, when comparing two keys, count the sums of all int values at all levels, and compare the sums.
	*/
	map<map<list<int*>*, vector<int*>, myFunctorClass>, int, myFunctorClass> M1
	{

		{   {
				{ new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}}   },
				{ new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{100}}   }
			} , 50
		},


		{	{
				{ new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}}   },
				{ new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{200}}   }
			} , 100
		}



	};
	//Implement the needed overloading operator<< to support the following printing.
	cout << M1 << endl;
	cout << endl;


	/*
	For the following, implement the functions used
	in sorting the list elements using regular funciton, functor, and lambda in the three cases.
	Similar to the case of map, we will compare the sums of int values at all levels.
	In addition, you need to implement the needed overloaded operator<< to supporting the printing.
	*/
	list<map < list<int*>*, vector<int*>, myFunctorClass >> L1{ {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					{new int{20}, new int{400}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					{new int{20}, new int{40}, new int{100}}
				}
		} , {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					{new int{20}, new int{40}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					{new int{20}, new int{40}, new int{200}}
				}
	} };
	cout << L1 << endl;
	L1.sort(? ? ? );//???: use a regular function
	cout << L1 << endl;
	cout << endl;

	list<map < list<int*>*, vector<int*>, myFunctorClass >> L2{ {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					{new int{20}, new int{400}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					{new int{20}, new int{40}, new int{100}}
				}
		} , {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					{new int{20}, new int{40}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					{new int{20}, new int{40}, new int{200}}
				}
	} };

	cout << L2 << endl;
	L2.sort(? ? ? );//???: use a functor 
	cout << L2 << endl;
	cout << endl;

	list<map < list<int*>*, vector<int*>, myFunctorClass >> L3{ {
					{
						new list<int*>{new int{10}, new int{20}, new int{30} } ,
						{new int{20}, new int{400}}
					},

					{
						new list<int*>{new int{40}, new int{20}, new int{30} }   ,
						{new int{20}, new int{40}, new int{100}}
					}
		} , {
					{
						new list<int*>{new int{10}, new int{20}, new int{30} } ,
						{new int{20}, new int{40}}
					},

					{
						new list<int*>{new int{40}, new int{20}, new int{30} }   ,
						{new int{20}, new int{40}, new int{200}}
					}
	} };

	cout << L3 << endl;
	L3.sort(? ? ? );//???: use a lambda 
	cout << L3 << endl;

	return 0;
}
//The following is a sample screenshot
//You must follow the exact format to avoid penalty in grading.
/*

10 2 0 14 43 25 18 1 5 45
45 43 25 18 14 10 5 2 1 0
10 2 0 14 43 25 18 1 5 45
0 1 2 5 10 14 18 25 43 45
10 2 0 14 43 25 18 1 5 45
10 0 25 5 45 1 2 18 43 14


{ { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 100 ] } 50 { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } 100 }

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )
*/