//Initializer_List, Copy constructor, Copy assignment, destructor, deep and shallow copy/assign/destruct
/*
Lvalue vs Rvalue
Lvalue: Any entity that can be placed on the left side of an assignment statement.

(Any entity that has a memory address.)

if not Lvalue, then an entity is Rvalue.

j = r+1; //j is Lvalue

A[5} = 6; A[5] is Lvalue;
Can  you do   x+1 = 5; ?    x+1 is Rvalue

Can you do sqrt(i) = j; ?  sqrt(i) is Rvalue

it1 = List1.begin();   List1.begin() is Rvalue; it1 is Lvalue;


*/
#include <iostream>
#include <vector>

using namespace std;

template <class T> class node {
public:
	T value;
	node<T>* next;
	node() { next = nullptr; }
	node(T i) { value = i; next = nullptr; }
};

template <class T> class LinkedList {
public:
	node<T>* head;
	LinkedList() { head = nullptr; cout << "Default Constructor" << endl; }
	LinkedList(int m, T n);//Constructor ; m nodes with random values in 0 ... n-1
	LinkedList(const initializer_list<T>& I);//Initializer_List
	LinkedList(const LinkedList<T>& L);//Copy Constructor; Lvalue copy constructor
	LinkedList<T>& operator=(const LinkedList<T>& L);//copy assignment; Lvalue assignment
	~LinkedList();//Destructor
	LinkedList<T> ThreeTimes();//ThreeTimes
	LinkedList(LinkedList<T>&& L);//Move constructor; Rvalue, const is removed; Rvalue copy constructor
	LinkedList<T>& operator=(LinkedList<T>&& L);//Move assignment; Rvalue assighnment

};
template <typename T> LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& L) {//Move assignment;
	while (head) {
		node<T>* p1{ head->next };
		delete head;
		head = p1;
	}
	head = L.head;
	L.head = nullptr;

	cout << "Move Assignment" << endl;
	return *this;
}
template<typename T>  LinkedList<T>::LinkedList(LinkedList<T>&& L) {//Move constructor;

	head = L.head;
	L.head = nullptr;
	cout << "Move Constructor" << endl;

}


template <typename T> LinkedList<T>  LinkedList<T>::ThreeTimes() {//ThreeTimes

	LinkedList<T> temp{ *this };//Copy Constructor   *this is L3
	node<T>* p1 = temp.head;
	while (p1) {
		p1->value *= 3;
		p1 = p1->next;
	}
	cout << "ThreeTimes" << endl;
	return temp;//Compiler will automatically change it to return move(temp);
	//move wiill change a Lvalue object to Rvalue
	//VS compiler will automatically change it to return move(temp); Thus becoming Rvalue
	//It changes because it found a move constructor
}
template <class T> LinkedList<T>::~LinkedList() {//Destructor

	while (head) {
		node<T>* p1 = head->next;
		delete head;
		head = p1;
	}
	cout << "Destructor" << endl;

}



template <class T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& L) {//Copy Assignment
	if (this == &L) { cout << "Copy Assignment" << endl; return *this; }//L5 = L5;
	while (head) {
		node<T>* p1 = head->next;
		delete head;
		head = p1;
	}

	node<T>* p1{ L.head }, * p2;
	while (p1) {
		p2 = new node<T>{};
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}

	cout << "Copy Assignment" << endl;

	return *this;//Will it change it to return move(*this);  No. it will not.
}



template <class T> LinkedList<T>::LinkedList(const LinkedList<T>& L) : LinkedList<T>{} {//Copy Constructor
	//head = nullptr;

	node<T>* p1{ L.head }, * p2;
	while (p1) {
		p2 = new node<T>{};
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}

	cout << "Copy Constructor" << endl;
}

template <class T> LinkedList<T>::LinkedList(const initializer_list<T>& I) : LinkedList<T>{} {//Initializer_List
	//head = nullptr;
	auto p = I.end() - 1;
	while (p != I.begin() - 1) {
		node<T>* p1{ new node<T>{*p} };
		p1->next = head;
		head = p1;
		--p;
	}
	cout << "Initializer_List" << endl;


}
template <class T> LinkedList<T>::LinkedList(int m, T n) : LinkedList<T>{} {//Constructor
	//head = nullptr;
	for (int i = 0; i < m; ++i) {
		node<T>* p1{ new node<T>(rand() % n) };
		p1->next = head;
		head = p1;
	}
	cout << "Constructor" << endl;
}

template <class X> ostream& operator<<(ostream& str, const LinkedList<X>& L);


void f1(int& k) {//Lvalue
	cout << "Lvalue" << endl;
}

void f1(int&& k) {//Ravalue

	cout << "Rvalue" << endl;
}



int main() {
	LinkedList<int>  L1(15, 10);//will call constructor with {) rather than {}
	cout << L1 << endl;
	//LinkedList<int> 

	LinkedList<int> L2{ 3,4,5,6,7,8,9 };//3 4 5 6 7 8 9
	cout << L2 << endl;
	LinkedList<int> L3{ 15,10 };//will call initializer_list
	//initializer_list > constructor > aggregate initilaiziton

	//vector<int> V{ 3,4,5,6 };

	//shallow vs deep copy and assignment

	LinkedList<int> L4{ L2 };//will call copy constructor  L4=L2
	cout << L4 << endl;
	cout << L2 << endl;
	L4.head->value = 25;
	cout << L4 << endl;
	cout << L2 << endl;
	cout << "*********" << endl;




	L3 = L4;//will call copy assignment  L3 = L4 = L1; won't work;
	//compiler will change it into     L3.operator=(L4);
	L3.head->next->value = 100;
	cout << L3 << endl;
	cout << L4 << endl;





	LinkedList<int> L5 = L4;// the same as LinkedList<int> L5 { L4};  will call copy constructor not 
	//copy assignment
	/*
	Under the following 3 cases will copy constructor be called by system:
	(1) When an object is declared and initialized to another object in the same statement.
	(2) Call by value
	(3) Return by value
	*/
	L5 = L5;//copy assignment

	{
		LinkedList<int> L6{ L4 };

	}

	//cout << L6 << endl;  Error!  L6 has been deleted by destructor
	L5 = L3.ThreeTimes();
	//Compiler chnage it to:  L5.operator=(L3.ThreeTimes());//R value 





	//int w = 10;
	//f1(w);//w is Lvalue
	//f1(abs(w)); //abs(w) is Rvalue

	cout << "11111111111" << endl;
	L2 = L3 = L4 = L5;
	//compilier will change it to L2.operator= (L3.opreator=(L4));

	cout << L2 << endl;
	cout << L3 << endl;
	cout << L4 << endl;
	cout << L5 << endl;


	cout << "2222222222222222" << endl;

	return 0;
}

template <class X> ostream& operator<<(ostream& str, const LinkedList<X>& L) {
	node<X>* p1{ L.head };
	str << "{ ";
	while (p1) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	str << "}";
	return str;
}