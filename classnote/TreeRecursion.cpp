
//Linked List
#include <iostream>
#include <string>

using namespace std;



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
	Tnode* MakeTree(int k, int m);//k levels with random values in 0 ... m-1
	void InorderPrint(Tnode* p);
	int LeftHeavy(Tnode* p);
	//Make the tree, rooted at a node pointed by p, Left Heavy
	//You required to implement LeftHeavy using recursion.

	void mirror(Tnode* p);
	Tnode* mirrorCopy(Tnode* p);
	bool Existing(Tnode * p, int k);//Return ture if k exists in the tree; else, false
};

bool Tree::Existing(Tnode* p, int k) {
	if (!p) return false;
	if (p->value == k) return true;
	else return (Existing(p->Lchild, k) || Existing(p->Rchild, k));
}


Tnode* Tree::mirrorCopy(Tnode* p) {
	if (!p) return nullptr;
	Tnode* p1{ new Tnode{p->value} };
	p1->Rchild = mirrorCopy(p->Lchild);
	p1->Lchild = mirrorCopy(p->Rchild);
	return p1;
}

void Tree::mirror(Tnode* p) {
	if (!p || !p->Lchild) return; //0 or 1 node
	mirror(p->Lchild);
	mirror(p->Rchild);
	swap(p->Lchild, p->Rchild);
}

int Tree::LeftHeavy(Tnode* p) {
	if (!p) return 0;
	if (!p->Lchild) return p->value;
	int w1{ LeftHeavy(p->Lchild) };
	int w2{ LeftHeavy(p->Rchild) };
	if (w1 < w2) swap(p->Lchild, p->Rchild);
	return w1 + w2 + p->value;



}
Tnode* Tree::MakeTree(int k, int m) {
	Tnode* p1 = new Tnode(rand() % m);
	if (k == 1) return p1;
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



int main() {



	Tree T1;
	T1.root = T1.MakeTree(3, 20);
	T1.InorderPrint(T1.root);
	cout << endl;
	T1.LeftHeavy(T1.root);
	T1.InorderPrint(T1.root);
	cout << endl;
	T1.mirror(T1.root);
	T1.InorderPrint(T1.root);
	cout << endl;
	Tree T2;
	T2.root = T1.mirrorCopy(T1.root);
	T2.InorderPrint(T2.root);
	cout << endl;
	cout << boolalpha << endl;
	cout << T2.Existing(T2.root, 4)<<"  " << T2.Existing(T2.root, 99) << endl;
	cout << noboolalpha << endl;

	int i1, i2;
	string s1, s2;
	//cin >> i1 >> s1 >> i2 >> s2;

	//cout << i1 << " " << i2 << " " << s1 << " " << s2 << endl;
	getline(cin, s1);
	cout << s1 << endl;









	return 0;
}