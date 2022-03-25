
//Linked List
#include <iostream>
#include <memory>//smart pointers

using namespace std;



class Tnode {
public:
	int value;
	//Tnode* Lchild;
	shared_ptr<Tnode> Lchild;
	shared_ptr<Tnode> Rchild;
	//Tnode* Rchild;
	Tnode(int i) { value = i;  }
	Tnode() { }
};

class Tree {//full tree;  1 node (level 1), 3 nodes (Level 2), 7 nodes (level 3), 15 nodes
public:
	//Tnode* root;
	shared_ptr<Tnode> root;
	Tree() {  }
	//Tnode* MakeTree(int k, int m);//k levels with values in 0 ... m-1
	shared_ptr<Tnode> MakeTree(int k, int m);
	//void InorderPrint(Tnode* p);
	void InorderPrint(shared_ptr<Tnode> p);
};

//Tnode* Tree::MakeTree(int k, int m) {
shared_ptr<Tnode> Tree::MakeTree(int k, int m){

	//Tnode* p1 = new Tnode(rand() % m);
	shared_ptr<Tnode> p1{ make_shared<Tnode>(rand() % m) };
	if (k == 1) return p1;
	p1->Lchild = MakeTree(k - 1, m);
	p1->Rchild = MakeTree(k - 1, m);
	return p1;
}

//void Tree::InorderPrint(Tnode* p) {
void Tree::InorderPrint(shared_ptr<Tnode> p) {
	if (!p) return;
	InorderPrint(p->Lchild);
	cout << p->value << " ";
	InorderPrint(p->Rchild);
}


class Dnode {//for doubly linked list; double linked list
public:
	int value;
	//Dnode* next;
	shared_ptr<Dnode> next;
	weak_ptr<Dnode> previous;
	//Dnode* previous;
	Dnode(int i) { value = i;  }
	Dnode() {  }

};

class DLinkedList {
public:
	//Dnode* head;
	shared_ptr<Dnode> head, tail;
	//Dnode* tail;
	DLinkedList(int n, int m);//n nodes with values in 0 ...m-1
	void print_F();
	void print_B();
	void reverse();
	void new_reverse();
};



void DLinkedList::reverse() {
	if (!head || !head->next) return; //0 or 1 node
	//Dnode* p1{ head }, * p2{ head->next };
	shared_ptr<Dnode> p1{ head }, p2{ head->next }, p3;
	while (p1) {
		//swap(p1->next, p1->previous);//swap (i1, i2);
		//shared_ptr<Dnode> p3{ p1->next };
		p1->next = p1->previous.lock();
		p1->previous = p2;
		//shared_ptr<Dnode> p3{ p1 };
		p3 = p1;
		p1 = p2;
		if (p2) p2 = p2->next;
	}
	swap(head, tail);
}



DLinkedList::DLinkedList(int n, int m) {
	for (int i = 0; i < n; ++i) {
		//Dnode* p1 = new Dnode(rand() % m);
		shared_ptr<Dnode> p1{ make_shared<Dnode>(rand() % m) };
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
	//Dnode* p1{ head };
	shared_ptr<Dnode> p1{ head };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}
void DLinkedList::print_B() {
	//Dnode* p1{ tail };
	shared_ptr<Dnode> p1{ tail };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous.lock();
	}
}





int main() {




	

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

	return 0;
}