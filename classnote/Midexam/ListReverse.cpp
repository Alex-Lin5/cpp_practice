
#include <iostream>
using namespace std;

class node {
public:
	int value;
	node* next;
	node(int i) { value = i; next = nullptr; }
	node() { next = nullptr; }//default constructor
};

class LinkedList {
public:
	node* head;// points to the first node of the linked list.
	LinkedList() { head = nullptr; }//default constructor
	LinkedList(int n, int m);//Construct an n-node linked list with random values in 0 ... m-1
	void reverse();

};

void LinkedList::reverse() {
	if (!head || !head->next) return;
	node* p1{ head }, * p2{ head }, * p3{ nullptr };
	while (p1->next != p3) {
		p2 = p1->next;
		while (p2->next != p3) {
			p2 = p2->next;
		}
		swap(p1->value, p2->value);
		p3 = p2;
		p1 = p1->next;
	}
}
LinkedList::LinkedList(int n, int m) {
	head = nullptr;
	for (int i = 0; i < n; ++i) {
		node* p1{ new node(rand() % m) };
		p1->next = head;
		head = p1;
	}
}


ostream& operator<<(ostream& str, const LinkedList& L) {
	node* p1{ L.head };
	while (p1) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	return str;
}
int main() {
	LinkedList L1{ 15, 10 };
	cout << L1 << endl;
	L1.reverse();
	cout << L1 << endl;

	return 0;
}