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
	// Node* tail;
	LinkedList() { head = nullptr; }
	LinkedList(int m, int n);//You can use code from class lectures for this constructor.
    void initialize(int* array, int* end);
    void dlt();
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

LinkedList::LinkedList(int n, int m){
    head = nullptr;
    for (int i=0; i<n; i++){
        Node* pt = new Node{rand()%m};
        cout << &pt << " ";
        if(!head){
            // head = tail = pt;
            head = pt;
            // tail->next = nullptr;
        }
        else{
            pt->next = head;
            head = pt;
        }
        cout << &head << " ";
    }
}

void LinkedList::initialize(int* array, int* end){
    head = nullptr;
    Node* pre;
    cout << "initial starts" << endl;
    while(array < end){
        Node* pt = new Node{*array};
        // cout << *array << " ";
        if(!head){
            pre = head = pt;
            array += 1;            
        }
        else{
            pt->next = pre;
            pre = pt;
            array += 1;            
        cout << &pt << " ";
        }
    }
    pre->next = nullptr;
    cout << "initilize end" << endl;
//     for(auto itr: array){
//         cout << *array << " ";
//         Node* pt = new Node{*itr};
//         if(!head)
//             pre = head = pt;
//         else{
//             pt->next = pre;
//             pre = pt;
//     }
}

void LinkedList::dlt(){
    Node* pt1, *pt2;
    if(head)
        pt1 = pt2 = head;
    while(pt1){
        pt2 = pt1->next;
        delete pt1;
        pt1 = pt2;
    }
}

void LinkedList::print(){
    Node* pt{head};
    while(pt){
        cout << pt->value << " ";
        pt = pt->next;
    }
}

void LinkedList::group(){
    Node *root, *branch, *opt;
    root= branch= opt= head;
    // cout << root->value << branch->value << opt->value << endl;
    while(root){
        int goal = root->value;
        while(opt->next){
            // cout << "outbranch" << branch->value << endl;
            // cout << "outopt" << opt->value << endl;
            if(root->next->value == goal){
                opt = root = root->next;
            }
            else if(opt->next->value == goal){
                branch = opt->next; // link the latter part of list first, then front
                opt->next = branch->next;
                branch->next = root->next;
                root->next = branch;
                root = root->next;
                // cout << "goal" << goal;
                // cout << " branch" << branch->value;
                // cout << " opt" << opt->value << endl;
                // print();
            }
            else
                opt = opt->next;
        }
        root = root->next;
        opt = root;
        // cout << "--------" << endl;
    }
}

// losing 2 groups of smallest elements if size of list growing large, or too many lists invovled in the program.
void LinkedList::bubbleSort(){ //ascending order, biggest value is sorted first
    Node *anchor{nullptr};
    // Node *buoy= *cap= *rope= head; // incorrect declaration
    Node *buoy, *cap, *rope;
    buoy= cap= rope= head;
    while(anchor != head){
        rope = cap = buoy = head;
        if(buoy->next == nullptr){ // for 1 element
            anchor = buoy;
        }
        while(buoy != anchor){
            cap = buoy->next; 
            if(buoy->next == nullptr) // last element
                anchor = buoy;            
            else if(buoy->next == anchor){ // elements on the other side to anchor are sorted
                // cout << "anchor" << anchor->value << " buoy" << buoy->value << endl;
                anchor = buoy;
            }
            else if(buoy->value > cap->value){ 
                // cout << "cap" << cap->value << " buoy" << buoy->value << endl;
                buoy->next = cap->next;
                cap->next = buoy;
                if(rope == buoy) // first 2 element, execute once
                    head = cap;
                else{
                    rope->next = cap;
                    rope = cap;
                }
            }
            else{
                rope = buoy;
                buoy = buoy->next;
            }
        }
        // cout << "out: anchor" << anchor->value << " buoy" << buoy->value << endl;
    }
}

int main() {//During grading, different cases will be used.
    // int* pt; int arysize;
    // int array[] {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 1, 1, 1, 1};
    // pt = &array[0]; 
    // // pt = new int[] {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 1, 1, 1, 1};
    // arysize = sizeof(array)/sizeof(array[0]);
    // cout << "pt=" << pt << ", *pt=" << *pt << ", pt+1=" << pt+1;
    // cout << ", *(pt+arysize-1)=" << *(pt+arysize-1) << ", size=" << arysize << endl;
    // LinkedList listsp;
    // listsp.initialize(pt, pt+arysize);
    // listsp.print(); cout << "initial" << endl;
    // listsp.bubbleSort();
    // listsp.print(); cout << "sort" << endl;
    
    // ---------------------------------------------
    int configure[][2]{
        // {0,10},{1,10},{2,2},{3,2},{3,100},{4,1},
        {5,10},
        // {10,100},
        // {20,4},
        // {100,10},{100,100}
        };
    int N = sizeof(configure)/sizeof(configure[0]);
    for(int i=0; i<N; i++){
        LinkedList List(configure[i][0], configure[i][1]);
        cout << "Testlist" << i+1 << ": ";
        List.print(); cout << endl;
        List.group(); 
        List.print(); cout << "group" << endl;        
        List.bubbleSort();
        List.print(); cout << "sort" << endl;
        List.dlt();        
    }
    // --------------------------------
	// LinkedList L1(50, 20);
	// L1.print();
	// cout << endl;
	// L1.group();
	// L1.print();
	// cout << endl;
	// LinkedList L2(55, 25);
	// L2.print();
	// cout << endl;
	// L2.bubbleSort();
	// L2.print();
	return 0;
}

/*
Testlist3: 3 0 2 3 3 1 0 0 1 3 0 0 0 3 1 0 1 2 2 1
3 3 3 3 3 0 0 0 0 0 0 0 2 2 2 1 1 1 1 1 group
1 3 3 3 3 3 sort
Testlist4: 0 0 1 7 3 4 2 3 0 0 5 9 3 7 1 7 8 1 8 5 7 4 7 4 1 1 8 0 0 1 2 8 6 2 7 1 3 6 5 7 0 0 1 8 3 5 2 4 9 6 7 5 3 4 6 9 6 4 7 9 7 9 5 5 9 9 0 3 2 2 6 0 9 0 4 4 3 6 7 0 9 5 4 4 0 1 5 7 9 1 6 6 0 1 3 4 2 0 4 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 7 7 7 7 7 7 7 7 7 7 7 7 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 4 4 2 2 2 2 2 2 2 5 5 5 5 5 5 5 5 5 9 9 9 9 9 9 9 9 9 9 8 8 8 8 8 6 6 6 6 6 6 6 6 6 group
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 6 6 6 6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 7 7 8 8 8 8 8 9 9 9 9 9 9 9 9 9 9 sort
Testlist5: 95 72 12 45 26 73 87 55 17 7 10 29 49 35 79 37 40 43 44 56 41 60 74 53 73 48 94 5 45 95 30 55 73 10 95 74 93 32 55 30 19 6 89 23 18 70 65 68 2 6 61 74 82 55 15 0 19 86 58 31 24 47 60 85 42 96 0 10 5 10 2 87 70 52 83 5 74 0 73 3 68 87 9 10 87 46 11 20 88 93 85 38 88 93 8 97 3 26 78 57
95 95 95 72 12 45 45 26 26 73 73 73 73 87 87 87 87 55 55 55 55 17 7 10 10 10 10 10 29 49 35 79 37 40 43 44 56 41 60 60 74 74 74 74 53 48 94 5 5 5 30 30 93 93 93 32 19 19 6 6 89 23 18 70 70 65 68 68 2 2 61 82 15 0 0 0 86 58 31 24 47 85 85 42 96 52 83 3 3 9 46 11 20 88 88 38 8 97 78 57 group
8 9 11 20 38 42 46 52 57 78 83 88 88 95 95 95 96 97 sort
*/