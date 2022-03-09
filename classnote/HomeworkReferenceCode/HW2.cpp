
#include <iostream>

using namespace std;

class node {//for doubly linked list; double linked list
public:
	int value;
	node* next;
	node* previous;
	node(int i) { value = i; next = previous = nullptr; }
	node() { next = previous = nullptr; }

};


class DLinkedList {
public:
	node* head;
	node* tail;
	DLinkedList(int n, int m);//n nodes with random values in 0 ...m-1
	void print_F();
	void print_B();
	void sort();
	/*
	Sort the DLinkedList into asscending order.
	You are only allowed to modify next and previous of a node, but not value.
	You are not allowed to use any external stucture (such as array) to help.
	Do not introduce any additional function.
	You are required to implement selection sort.
	*/

	void removeAll(int k);
	/*
	Remove all nodes with value k.
	You are allow to modify  value, next, and previous of a node.
	You are not allowed to use any external stucture (such as array) to help.
	Do not introduce any additional function.
	*/

};

void DLinkedList::sort() {
	if (head) {
		node* p1{ head }, * p2{ p1->next }, * p3{ p1 };
		while (p1->next) {
			while (p2) {
				if ((p2->value) < (p3->value)) {
					p3 = p2;
				}
				p2 = p2->next;
			}
			if (p3 != p1) {
				if (p1->previous) {
					p1->previous->next = p3;
				}
				else {
					head = p3;
				}
				if (p3->next) {
					p3->next->previous = p1;
				}
				else {
					tail = p1;
				}
				if (p1->next == p3) {
					p3->previous = p1->previous;
					p1->previous = p3;
					p1->next = p3->next;
					p3->next = p1;
				}
				else {
					p1->next->previous = p3;
					p3->previous->next = p1;
					p2 = p1->next;
					p1->next = p3->next;
					p3->next = p2;
					p2 = p1->previous;
					p1->previous = p3->previous;
					p3->previous = p2;

				}
			}
			p3 = p3->next;
			p1 = p3;
			p2 = p3->next;
		}
	}
}

void DLinkedList::removeAll(int k) {
	if (head) {
		node* p1{ head }, * p2{ p1 };
		while (p1) {
			p2 = p1->next;
			if (p1->value == k) {
				if (p1->previous) {
					p1->previous->next = p1->next;
				}
				else {
					head = p1->next;
				}
				if (p1->next) {
					p1->next->previous = p1->previous;
				}
				else {
					tail = p1->previous;
				}
				delete p1;
			}
			p1 = p2;
		}
	}
}


DLinkedList::DLinkedList(int n, int m) {
	for (int i = 0; i < n; ++i) {
		node* p1 = new node(rand() % m);
		if (!head) {//empty DLinkedList
			head = tail = p1;
		}
		else {
			p1->previous = tail;
			tail->next = p1;
			tail = p1;
		}
	}
}


void DLinkedList::print_F() {
	node* p1{ head };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}
void DLinkedList::print_B() {
	node* p1{ tail };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}


int main() {

	DLinkedList DL1{ 20, 10 };
	DL1.print_F();
	cout << endl;
	DL1.print_B();
	cout << endl;

	DL1.removeAll(5);
	DL1.print_F();
	cout << endl;
	DL1.print_B();
	cout << endl;

	DL1.sort();
	DL1.print_F();
	cout << endl;
	DL1.print_B();
	cout << endl;

	return 0;
}