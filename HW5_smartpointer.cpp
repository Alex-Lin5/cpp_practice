//CIS554 HW5  Due: 11:59PM, Wednesday, March. 30.
#include <iostream>
#include <memory>

using namespace std;

class node {
public:
	int value;
	weak_ptr<node> east;
	shared_ptr<node> l_child;
	shared_ptr<node> r_child;
	node() {}
	node(int i) { value = i; }
};

class tree {
public:
	shared_ptr<node> root;
	//int level;
	tree() { }

	//Implement all member functions below
	tree(int n, int m);//constructor for n-level tree with random values in 0 ... m-1
	//n=1: 1 node; n-2: 3 nodes; n=3: 7 nodes; n=4: 15 nodes, etc.

	tree(const tree& T);//copy constructor
	~tree();//destructor
	tree(tree&& T); //move constructor

	tree(const initializer_list<int>& V);//See lecture video recording for this.
	void operator = (const tree& R);//copy assignment
	void operator = (tree&& R); //move assignment
	tree ThreeTimes(); //return a tree with all node value being three times
	friend ostream& operator<<(ostream& str, const tree& T);
	void delete_level(int i); // Delete nodes at level i; i>1

	shared_ptr<node> operator[](int k);//The function returns the address of kth node
	//in the overall ring (or cycle).  For example, when k is 0, it returns the address of the
	//root; when k is 1, it returns the address of left child of root; when k is 2, it returns
	//the address of right child of root, etc.
	//For a level 4 tree, when k=14, it returns the address of the very last node of the tree.
};

int main() {
	tree T1(3, 10);
	cout << T1 << endl;
	tree T2 = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	cout << T2 << endl;

	tree T3{ T2 };
	cout << T3 << endl;

	tree T4;
	T4 = T3;
	cout << T4 << endl;

	T4 = T3.ThreeTimes();
	cout << T4 << endl;

	T4.delete_level(3);
	cout << T4 << endl;

	return 0;
}

tree::tree(int n, int m){
    cout << "constructor" << endl;
}

tree::~tree(){
    cout << "destrctor" << endl;
}

tree::tree(const tree& T){
    cout << "copy constructor" << endl;
}

tree::tree(const initializer_list<int>& V){
    cout << "initializer list" << endl;
}

void tree::operator = (const tree& R){
    cout << "copy assignment" << endl;
}

void tree::operator = (tree&& R){
    cout << "move assignment" << endl;
}

tree tree::ThreeTimes(){
    cout << "three times" << endl;
}

void tree::delete_level(int i){
    cout << "delete level " << i << endl;
}

shared_ptr<node> tree::operator[](int k){
    cout <<"node " << k << " is " << endl;
}

ostream& operator<<(ostream& str, const tree& T){
    cout << "print tree " << T << endl;
}
