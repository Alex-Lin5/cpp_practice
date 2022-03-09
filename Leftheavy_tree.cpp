
//Linked List
#include <iostream>

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
	Tnode* MakeTree(int k, int m);//k levels with values in 0 ... m-1
	void InorderPrint(Tnode* p);
	void LeftHeavy(Tnode* p);
	//Make the tree, rooted at a node pointed by p, Left Heavy
	//You required to implement LeftHeavy using recursion.
};

// void Tree::LeftHeavy(Tnode* p){
//     if(p->Lchild == nullptr) return;
//     LeftHeavy(p->Lchild);
//     LeftHeavy(p->Rchild);
//     // int maxnode = max(initializer_list{p->value, p->Lchild->value, p->Rchild->value});
//     // Tnode* max{p};
//     if(p->Lchild->value < p->Rchild->value)
//         swap(p->Lchild->value, p->Rchild->value);
            
//     if(p->value < p->Lchild->value)
//         swap(p->value, p->Lchild->value);
//         // swap(p, p->Rchild);
//     if(p->Lchild->value < p->Rchild->value)
//         swap(p->Lchild->value, p->Rchild->value);
    
//     return;
    
// }
void Tree::LeftHeavy(Tnode* p){
    if(p->Lchild == nullptr) return;
    int Lbranch = 0;
    int Rbranch = 0;
    LeftHeavy(p->Lchild);
    LeftHeavy(p->Rchild);
    // int maxnode = max(initializer_list{p->value, p->Lchild->value, p->Rchild->value});
    // Tnode* max{p};
    Lbranch += p->Lchild->value;
    Rbranch += p->Rchild->value;
    if(Lbranch < Rbranch)
        swap(p->Lchild, p->Rchild);
    return;
    
}

Tnode* Tree::MakeTree(int k, int m) {
	Tnode* p1 = new Tnode(rand() % m);
	if (k == 1){
        cout << k << ": " << p1->value << endl;
        return p1;
    } 
    cout << "L";
	p1->Lchild = MakeTree(k - 1, m);
    cout << "R";
	p1->Rchild = MakeTree(k - 1, m);
    cout << k << ": " << p1->value << endl;
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
	T1.root = T1.MakeTree(4, 10);
	T1.InorderPrint(T1.root);
	cout << endl;
	T1.LeftHeavy(T1.root);
	T1.InorderPrint(T1.root);
	cout << endl;
	T1.LeftHeavy(T1.root);
	T1.InorderPrint(T1.root);
	cout << endl;
	T1.LeftHeavy(T1.root);
	T1.InorderPrint(T1.root);
	cout << endl;
	T1.LeftHeavy(T1.root);
	T1.InorderPrint(T1.root);
	cout << endl;

	return 0;
}