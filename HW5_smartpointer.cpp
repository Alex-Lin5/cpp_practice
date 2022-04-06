//CIS554 HW5  Due: 11:59PM, Wednesday, March. 30.
#include <iostream>
#include <memory>
#include <cmath>

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
	tree() { }

	//Implement all member functions below
	tree(int n, int m);//constructor for n-level tree with random values in 0 ... m-1
	//n=1: 1 node; n-2: 3 nodes; n=3: 7 nodes; n=4: 15 nodes, etc.

	tree(const tree& T);//copy constructor
	~tree();//destructor
	tree(tree&& T); //move constructor

	tree(const initializer_list<int>& V);//See lecture video recording for this.
	void operator = (const tree& T);//copy assignment
	void operator = (tree&& T); //move assignment
	tree ThreeTimes(); //return a tree with all node value being three times

	shared_ptr<node> operator[](int k);//The function returns the address of kth node
	//in the overall ring (or cycle).  For example, when k is 0, it returns the address of the
	//root; when k is 1, it returns the address of left child of root; when k is 2, it returns
	//the address of right child of root, etc.
	//For a level 4 tree, when k=14, it returns the address of the very last node of the tree.
	friend ostream& operator<<(ostream& str, const tree& T);//print in the order ring/cycle atarting at the root node
	void InorderPrint(shared_ptr<node>);//in-order printing
};


int main() {
	tree T1(3, 10);
	cout << T1 << endl;
	T1.InorderPrint(T1.root);
	cout << endl;
	tree T2 = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

	cout << T2 << endl;
	T2.InorderPrint(T2.root);
	cout << endl;

	tree T3{ T2 };
	cout << T3 << endl;
	T3.InorderPrint(T3.root);
	cout << endl;
	tree T4;
	T4 = T3;
	cout << T4 << endl;
	T4.InorderPrint(T4.root);
	cout << endl;

	T4 = T3.ThreeTimes();
	cout << T4 << endl;
	T4.InorderPrint(T4.root);
	cout << endl;
	
    T4[3];

	return 0;
}

void tree::InorderPrint(shared_ptr<node> rt) {
    if(rt == nullptr) return;
    InorderPrint(rt->l_child);
    cout << rt->value << ' ';
    InorderPrint(rt->r_child);
}
tree::tree(int n, int m){
    shared_ptr<node> pt{ make_shared<node>(rand()%m)};
    if(n>0) root = pt;
    else return;    
    if(n == 1) root->east = root;

    shared_ptr<node> parent{ root }, pre{ root };
    int level = 0;
    for (int index = 1; index < pow(2, n - 1); index++) {
        //cout << parent->value << ' ';
        parent->l_child = make_shared<node>(rand() % m);
        parent->r_child = make_shared<node>(rand() % m);
        parent->l_child->east = parent->r_child;
        if(index == pow(2,level)) 
            pt = parent->l_child;
        else {
            pre->r_child->east = parent->l_child;// conncet within a level
        }
        if(index == pow(2,level+1)-1){// connnect between levels
            level++;
            parent->east = pt;
        }
        if (index == pow(2, n - 1) - 1) break;
        pre = parent;
        parent = parent->east.lock();

    }
    parent->r_child->east = root;
    pre.reset();
    parent.reset();
    pt.reset();
    cout << "constructor" << endl;
}

tree::~tree(){
    root.reset();
    cout << "destrctor" << endl;
}

tree::tree(const tree& T){
    if (T.root != nullptr) root = make_shared<node>(T.root->value);
    else return;// 0 node
    if(T.root->east.lock() == T.root) root->east = root;// 1 node

    shared_ptr<node> parent{ root }, pre{ root };
    shared_ptr<node> opt {T.root->east.lock()}, pt{T.root->east.lock()};
    int level = 0, index = 1, size = 1;
    while (pt != T.root) {
        pt = pt->east.lock();
        size++;
    }
    double limit = log2(size); // limit is n levels
    while (level < limit - 1) {
        //cout << parent->value << ' ';
        parent->l_child = make_shared<node>(opt->value);
        opt = opt->east.lock();
        parent->r_child = make_shared<node>(opt->value);
        opt = opt->east.lock();
        parent->l_child->east = parent->r_child;
        if (index == pow(2, level))
            pt = parent->l_child;
        else {
            pre->r_child->east = parent->l_child;// conncet within a level
        }
        if (index == pow(2, level + 1) - 1) {// connnect between levels
            level++;
            parent->east = pt;
        }
        pre = parent;
        parent = parent->east.lock();
        index++;
    }

    pre->r_child->east = root;
    parent.reset();
    pre.reset();
    pt.reset();
    opt.reset();
    cout << "copy constructor" << endl;
}

tree::tree(const initializer_list<int>& V){
    auto itr{ V.begin() };
    if (itr != V.end()) root = make_shared<node>(*itr);
    else return;
    if(V.begin()+1 == V.end()) root->east = root;

    shared_ptr<node> parent{ root }, pre{ root }, pt;
    int level = 0, index = 1;
    int size = V.size();
    double limit = log2(size); // limit is n levels
    while (level < limit-1){
        //cout << parent->value << ' ';
        parent->l_child = make_shared<node>(*(++itr));
        parent->r_child = make_shared<node>(*(++itr));
        parent->l_child->east = parent->r_child;
        if (index == pow(2, level))
            pt = parent->l_child;
        else {
            pre->r_child->east = parent->l_child;// conncet within a level
        }
        if (index == pow(2, level + 1) - 1) {// connnect between levels
            level++;
            parent->east = pt;
        }
        pre = parent;
        parent = parent->east.lock();
        index++;
    }

    pre->r_child->east = root;
    parent.reset();
    pre.reset();
    pt.reset();
    cout << "initializer list" << endl;
}

void tree::operator = (const tree& R){
    if (R.root != nullptr) root = make_shared<node>(R.root->value);
    else return;// 0 node
    if (R.root->east.lock() == R.root) root->east = root;// 1 node

    shared_ptr<node> parent{ root }, pre{ root };
    shared_ptr<node> opt{ R.root->east.lock() }, pt{ R.root->east.lock() };
    int level = 0, index = 1, size = 1;
    while (pt != R.root) {
        pt = pt->east.lock();
        size++;
    }
    double limit = log2(size); // limit is n levels
    while (level < limit - 1) {
        //cout << parent->value << ' ';
        parent->l_child = make_shared<node>(opt->value);
        opt = opt->east.lock();
        parent->r_child = make_shared<node>(opt->value);
        opt = opt->east.lock();
        parent->l_child->east = parent->r_child;
        if (index == pow(2, level))
            pt = parent->l_child;
        else {
            pre->r_child->east = parent->l_child;// conncet within a level
        }
        if (index == pow(2, level + 1) - 1) {// connnect between levels
            level++;
            parent->east = pt;
        }
        pre = parent;
        parent = parent->east.lock();
        index++;
    }

    pre->r_child->east = root;
    parent.reset();
    pre.reset();
    pt.reset();
    opt.reset();
    cout << "copy assignment" << endl;
}

tree::tree(tree&& T) {
    (*this).root.reset();
    (*this).root = T.root;
    (*this).root->east = T.root->east.lock();
    (*this).root->l_child = T.root->l_child;
    (*this).root->r_child = T.root->r_child;
    T.root.reset();
    cout << "move constructor" << endl;
}
void tree::operator = (tree&& R){
    (*this).root.reset();
    (*this).root = R.root;
    (*this).root->east = R.root->east.lock();
    (*this).root->l_child = R.root->l_child;
    (*this).root->r_child = R.root->r_child;
    R.root.reset();
    cout << "move assignment" << endl;
}

 tree tree::ThreeTimes(){
     tree tmp{*this};
     auto pt {tmp.root};
     pt->value = 3 * pt->value;
     pt = pt->east.lock();
     while (pt != tmp.root) {
         pt->value = 3*pt->value;
         pt = pt->east.lock();
     }
     cout << tmp << endl;
     cout << "three times" << endl;
     return move(tmp);
 }

//void tree::delete_level(int i){
//    cout << "delete level " << i << endl;
//}

 shared_ptr<node> tree::operator[](int k){
     shared_ptr<node> pt{root};
     for (int index = 0; index < k; index++) {
         pt = pt->east.lock();
     }
     cout <<"node " << k << " is " << pt->value << endl;
     return pt;
 }

ostream& operator<<(ostream& str, const tree& T){
    shared_ptr<node> pt{T.root};
    int index = 2, level = 1;
    //str << "***************\n";
    str << pt->value << endl;
    pt = pt->east.lock();

    while(pt != T.root){
        str << pt->value << ' ';
        if(index == pow(2,level+1)-1){
            level++;
            str << endl;
        }
        index++;
        pt = pt->east.lock();
    }
    //str << "print tree " << T << endl;
    //str << "print tree\n**************** " << endl;
    return str;
}
