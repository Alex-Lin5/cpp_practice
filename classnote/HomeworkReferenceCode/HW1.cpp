
#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node(int i) { value = i; next = nullptr; }
	Node() { next = nullptr; }
};

class LinkedList {
public:
	Node* head;
	//Node* tail;
	LinkedList() { head = nullptr; }
	LinkedList(int m, int n);//You can use code from class lectures for this constructor.
	void print();//You can use code from class lecture for print.



	//***************************************************************************************************
	//implement the following member functions group and bubbleSort:

	void group();

	/*
	Group all occurrences of the same numbers together according to the order of appearance.

	For a list with values

	7 6 12 4 33 12 6 6 7 ,

	after grouping, it becomes

	7 7 6 6 6 12 12 4 33

	Note that in the original sequence, 7 appears before 6 before 12 before 4 before 33.

	You are only allowed to change "next" of a node, but not "value."
	Do not introduce additional functions.
	In-place implementation is required.  External structures, such as arrays, are not allowed.
	For example, you are not allowed to copy linked list values to outside, and then process the data and copy them
	back to linked list.

	*/


	void bubbleSort();
	//you are allowed change both value and next for bubbleSort.
	//Like function group, you are not allowed to use any external structures, such as arrays, to help.
	//No extra functions allowed
};
LinkedList::LinkedList(int n, int m) {
	head = nullptr;
	for (int i = 0; i < n; ++i) {
		Node* p1 = new Node{ rand() % m };
		p1->next = head;
		head = p1;
	}
}


void LinkedList::print() {
	Node* p1{ head };
	while (p1) {//while (p1 != nullptr)
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void LinkedList::group() {
	if (!head || !head->next || !head->next->next) {
		return;
	}
	/*Node* pre = head->next->next, *p4 = pre->next, *p4nx = p4->next, *cur = head->next;
	head->next = p4;
	p4->next = cur;
	pre->next = p4nx;*/
	Node* p = head;
	int num = p->value;
	 do{
		Node* cur = p->next;
		while (cur != nullptr && cur->value == p->value) {
			p = p->next;
			cur = cur->next;
		}
	
		Node* change = cur;
		if (cur == nullptr) {
			break;
		}
		while ( cur->next != nullptr) {
			
			if (cur->next->value == num) {
				Node* last = cur->next->next;
				p ->next = cur->next;
				cur->next->next = change;
				cur->next = last;
				p = p ->next;
				
			}
			else {
				cur = cur->next;
			}
		}
		p  = change;
		num = p ->value;
		if (p ->next == nullptr) {
			break;
		}
	 } while (p ->next->next != nullptr || p ->next != nullptr);
	 
	 


}

void LinkedList::bubbleSort() {
	if (!head || !head->next) {
		return;
	}
	Node* cur{ head }, * last{ nullptr };

	while (last != head->next) {
		while (cur->next != last) {
			if (cur->value > cur->next->value) {
				swap(cur->value, cur->next->value);
			}
			cur = cur->next;
			
		}
		last = cur;
		cur = head;
	}
	/*int swaped =1;
	while (swaped) {
		Node* p1 = head;
		swaped = 0;
		while (p1->next != nullptr) {
			if (p1 -> value > p1->next->value) {
				swap(p1->value, p1->next->value);
				
				swaped = 1;
			}
			p1 = p1->next;

		}
	}
	*/

}


int main() {//During grading, different cases will be used.
	LinkedList L1(50,20);
	L1.print();
	cout << endl;
	L1.group();
	L1.print();
	cout << endl;
	LinkedList L2(50, 25);
	L2.print();
	cout << endl;
	L2.bubbleSort();
	L2.print();
	return 0;
}