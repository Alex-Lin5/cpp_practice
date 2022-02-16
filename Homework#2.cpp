//HW2 Due: 11:59pm, Wed. Feb. 16.
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
    DLinkedList(initializer_list<int> list);
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
DLinkedList::DLinkedList(initializer_list<int> list) {
    tail = head = nullptr;
    node* pt = nullptr;
    for (auto itr : list) {
        node* pt = new node{ itr };
        if (!head) {
            tail = head = pt;
        }
        else {
            pt->previous = tail;
            tail->next = pt;
            tail = pt;
        }
 
    }
}
void DLinkedList::sort(){
    node* stem, *branch, *opt;
    stem = branch = opt = nullptr;
    if(head != nullptr){ // initialize for none empty list
        opt = branch = stem = head;        
    }

    while(stem != tail && tail != nullptr){ // 1 element list do not run this loop
		// print_F(); cout << " F " << endl;
        // print_B(); cout << " B " << endl;
        // cout << "tail=" << tail->value << endl;
		// cout << "branch value=" << branch->value << endl;
		// cout << "opt value=" << opt->value << endl;
        opt = branch = stem;
        while(opt){ // opt will traverse through the list frequently
    		// cout << "opt value=" << opt->value << endl;
            if(opt->value < branch->value){
                branch = opt;
            }
            opt = opt->next;
        }
        if(stem == branch){// the smallest element is already in correct place
            stem = stem->next;      
        }
        // else if(stem->next == branch){// the smallest element in this loop is in the next slot to the first one
        // }
        else{// general case
            opt = branch->previous; // deal with tail part
            opt->next = branch->next;
            if(branch != tail){
                opt = opt->next;
                opt->previous = branch->previous;
            }
            else
                tail = opt;
            opt = stem->previous; // deal with front part
            branch->next = stem;
            stem->previous = branch;
            branch->previous = opt;
            if(stem == head){
                head = stem->previous;
            }
            else
                opt->next = branch;
        }
    }
}

void DLinkedList::removeAll(int k){
    node* opt,* rm;
    opt = rm = nullptr;
    if(head != nullptr)
        opt = head;
    while(opt){
		// print_F();
		// cout << endl;
        if(opt->value == k){
            rm = opt;
            if(rm == head){
                head = opt->next;
                opt = head;
                delete rm;
                if(head != nullptr)
                    head->previous = nullptr;
                else
                    tail = nullptr;
                continue;
            }
            else if(rm == tail){
                tail = opt->previous;
                opt = tail;
                delete rm;
                if(tail != nullptr)
                    tail->next = nullptr;
            }
            else{
                opt = opt->previous;
                opt->next = rm->next;
                opt->next->previous = rm->previous;
                delete rm;
            }
        }
        // rm = nullptr;
        opt = opt->next;
    }
}

DLinkedList::DLinkedList(int n, int m) {
	head = tail = nullptr;
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
    // int configure[][2]{
    //     // {0,10},{1,10},{2,2},{3,2},{3,100},{4,1},{5,10},
    //     {10,100},{20,4},
    //     {100,10},{100,100}
    //     };
    // int N = sizeof(configure)/sizeof(configure[0]);
    // for(int i=0; i<N; i++){
    //     DLinkedList List(configure[i][0], configure[i][1]);
    //     cout << "Testlist" << i+1 << ": ";
    //     List.print_F(); cout << " F " << endl;
    //     List.print_B(); cout << " B " << endl;
    //     List.removeAll(0); 
    //     cout << "remove" << endl;        
    //     List.print_F(); cout << " F " << endl;
    //     List.print_B(); cout << " B " << endl;
    //     List.sort();
    //     cout << "sort" << endl;
    //     List.print_F(); cout << " F " << endl;
    //     List.print_B(); cout << " B " << endl;
    //     // List.dlt();        
    // }

 
    int listt[]{5, 3, 4, 6, 9, 6, 4, 7, 9, 7, 9, 5, 5, 9, 9, 3, 2, 2, 6, 9, 4, 4, 3, 6, 7, 9, 5, 4, 4, 1, 5, 7, 9, 1, 6, 6, 1, 3, 4, 2, 4, 5, 4, 7, 1};
    cout << *listt << endl;
    DLinkedList <int> dllist{ 9, 7, 9, 5, 5, 9, 9, 3, 2, 2};
    // dllist.print_F(); cout << " F " << endl;
    // dllist.print_B(); cout << " B " << endl;
    // dllist.removeAll(0); 
    // cout << "remove" << endl;        
    // dllist.print_F(); cout << " F " << endl;
    // dllist.print_B(); cout << " B " << endl;
    // dllist.sort();
    // cout << "sort" << endl;
    // dllist.print_F(); cout << " F " << endl;
    // dllist.print_B(); cout << " B " << endl;

	// DLinkedList DL1{ 20, 10 };
	// DL1.print_F();
	// cout << endl;
	// DL1.print_B();
	// cout << endl;

	// DL1.removeAll(0);
	// DL1.print_F();
	// cout << "remove" << endl;
	// DL1.print_B();
	// cout << endl;

	// DL1.sort();
	// DL1.print_F();
	// cout << "sort" << endl;
    // cout << "tail=" << DL1.tail << endl;
	// DL1.print_B();
	// cout << endl;

	return 0;
}