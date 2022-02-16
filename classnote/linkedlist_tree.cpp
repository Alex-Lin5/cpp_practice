
//Linked List
#include <iostream>

using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	int vol() { return ht * wid * dep; }
	ThreeD(int i, int j, int k) : ht(2 * i), wid(2 * j), dep(2 * k) {} //constructor for initialization
	ThreeD() {}//default constructor
	/*
	alternatively,
	ThreeD(int i, int j, int k){ht = 2*i; wid = 2*j; dep = 2*k;     }
	*/
};

class Tnode {
public:
	int value;
	Tnode* Lchild;
	Tnode* Rchild;
	Tnode(int i) { value = i; Lchild = Rchild = nullptr; }
	Tnode() { Lchild = Rchild = nullptr; }
};

class Tree {//full tree;  1 node (level 1), 3 nodes (Level 2), 7 nodes (level 3), 15 nodes
public:
	Tnode* root;
	Tree() { root = nullptr; }
	Tnode* MakeTree(int k, int m);//k levels with values in 0 ... m-1
	void InorderPrint(Tnode* p);
	int sum(Tnode* p);
	bool find(Tnode* p, int k);
	void mirror(Tnode* p);
};
void Tree::mirror(Tnode* p) {// Tranform a tree into its mirror
	if (!p || !p->Lchild) return;//0 or 1 node
	mirror(p->Lchild);
	mirror(p->Rchild);
	swap(p->Lchild, p->Rchild);
}

bool Tree::find(Tnode* p, int k) {//if k exists in the tree, return true (1), else return false (0)
	if (!p) return false;
	if (!p->Lchild) return (p->value  == k);
	return (p->value == k) || find(p->Lchild, k) || find(p->Rchild, k);
}

int Tree::sum(Tnode* p){//return sum of all values in a tree rooted by the node pointed by p
	if (!p) return 0;
	if (!p->Lchild) return p->value;//p points to a leaf node
	return p->value + sum(p->Lchild) + sum(p->Rchild);
	}


Tnode* Tree::MakeTree(int k, int m) {//constructing full trees
	Tnode* p1 = new Tnode(rand() % m);
	if (k == 1) return p1;//k ie level of the tree
	p1->Lchild = MakeTree(k - 1, m);
	p1->Rchild = MakeTree(k - 1, m);
	return p1;
}

void Tree::InorderPrint(Tnode* p) {
	if (!p) return;
	InorderPrint(p->Lchild);
	cout << p->value << " ";
	InorderPrint(p->Rchild);
}


class Dnode {//for doubly linked list; double linked list
public:
	int value;
	Dnode* next;
	Dnode* previous;
	Dnode(int i) { value = i; next = previous = nullptr; }
	Dnode() { next = previous = nullptr; }

};

class DLinkedList {
public:
	Dnode* head;
	Dnode* tail;
	DLinkedList(int n, int m);//n nodes with values in 0 ...m-1
	void print_F();
	void print_B();
	void reverse();
};

void DLinkedList::reverse() {
	if (!head || !head->next) return; //0 or 1 node
	Dnode* p1{ head }, * p2{ head->next };
	while (p1) {
		swap(p1->next, p1->previous);//swap (i1, i2);
		p1 = p2;
		if (p2) p2 = p2->next;
	}
	swap(head, tail);
}



DLinkedList::DLinkedList(int n, int m) {
	for (int i = 0; i < n; ++i) {
		Dnode* p1 = new Dnode(rand() % m);
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
	Dnode* p1{ head };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}
void DLinkedList::print_B() {
	Dnode* p1{ tail };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}



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
	LinkedList(int n, int m);//constructor an n-node linked list with random values in 0 ... m-1
	void print();
	void reverse();
	void sort();//prototype  sort them in ascemnding order
	void remove_one(int k);//Delete the first occurance of node with value k

};


void LinkedList::remove_one(int k) {
	if (!head) return; //0 node
	if (head->value == k) {
		node* p1{ head->next };
		delete head;
		head = p1;
		return;
	}
	node* p1{ head }, * p2{ head->next };
	while (p2) {
		if (p2->value == k) {
			p1->next = p2->next;
			delete p2;
			return;
		}
		p1 = p2;
		p2 = p2->next;
	}
}

void LinkedList::sort() {//selection sort
	if (!head || !head->next) return; // 0 or 1 node
	node* p1{ head }, * p2;
	while (p1->next) {
		p2 = p1->next;
		node* p_min{ p1 };
		int min{ p1->value };
		while (p2) {
			if (p2->value < min) {
				min = p2->value;
				p_min = p2;
			}
			p2 = p2->next;
		}
		p_min->value = p1->value;
		p1->value = min;
		p1 = p1->next;
	}
}


void LinkedList::reverse() {
	if (!head || !head->next) return; //0 or 1 node

	node* p1{ head }, * p2, * p3;
	p2 = p1->next;
	while (p2) {
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) p1->next = nullptr;
		p1 = p2;
		p2 = p3;
	}
	head = p1;

}





LinkedList::LinkedList(int n, int m) {
	head = nullptr;
	for (int i = 0; i < n; ++i) {
		node* p1 = new node{ rand() % m };
		p1->next = head;
		head = p1;
	}
}


void LinkedList::print() {
	node* p1{ head };
	while (p1) {//while (p1 != nullptr)
		cout << p1->value << " ";
		p1 = p1->next;
	}
}





int main() {

	int A[3]{ 1,2,3 };
	cout << 2[A] << " " << A[2] << endl; //*(2+A) or *(A+2)

	int* p1;
	p1 = nullptr;//NULL is out of date
	if (p1 == nullptr) cout << " p1 is not pointing to any object" << endl;
	if (!p1) cout << " p1 is not pointing to any object" << endl;//equivalent
	/*
	if (p1) is the same as if (p1 != nullptr)
	*/


	ThreeD t1;
	t1.ht = 25;
	t1.wid = 14;
	ThreeD t2{ 1,2,3 };//ht = 1, wid = 2, dep = 3; aggregate initialization

	cout << t2.vol() << endl;// 48  constructor takes priority over aggregate initialization

	ThreeD* p2 = new ThreeD{ 2,2,2 };

	cout << (*p2).vol() << endl;//Nobody would use this.
	cout << p2->vol() << endl;//arrow or select






	char c1;
	double d1;
	float f1;



	LinkedList L1{ 20, 10 };
	L1.print();
	L1.reverse();
	cout << endl;
	L1.print();
	cout << endl;
	L1.remove_one(1);
	L1.remove_one(6);
	L1.remove_one(8);
	L1.print();
	cout << endl;

	L1.sort();
	L1.print();
	cout << endl;

	DLinkedList DL1{ 12, 20 };
	DL1.print_F();
	cout << endl;
	DL1.print_B();
	cout << endl;

	DL1.reverse();
	cout << endl;
	DL1.print_F();
	cout << endl;
	DL1.print_B();
	cout << endl;


	Tree T1;
	T1.root = T1.MakeTree(3, 20);
	T1.InorderPrint(T1.root);
	cout << endl;
	cout << T1.sum(T1.root) << endl;
	cout << T1.find(T1.root, 12) << endl;//1  true
	cout << T1.find(T1.root, 7) << endl;//1 true
	cout << T1.find(T1.root, 14) << endl;//0 false

	T1.mirror(T1.root);
	T1.InorderPrint(T1.root);
	cout << endl;


	return 0;
}