#include <iostream>
#include <map>


using namespace std;


class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }
};


template <class T> class Record {
public:
	map<int, map<int, T*>*> Data;
	Record() { }
	Record(const initializer_list < pair<int, initializer_list<pair <int, T>>>>& I);
	Record(const Record<T>& R);//Copy Constructor
	void operator=(const Record<T>& R);//Copy Assignment
	~Record();//Destructor
	Record<T> deleteFirst();//DeleteFirst
	Record(Record<T>&& R);//Move Constructor
	void operator=(Record<T>&& R);//Move Assignment
};

template <class A> ostream& operator<<(ostream& str, const Record<A>& rcrs);
ostream& operator<<(ostream& str, course*& listc);

int main() {
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");
	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");


	Record<course> R1{ {10, { {12, C1}, {9, C2}  }},
		{7, {{8, C3}, {3, C4}, {1, C5}}},{4, {{21, C6}, {15, C7}} } };

	cout << R1 << endl;


	Record<course> R2{ R1 };
	cout << R2 << endl;

	Record<course> R3;
	R3 = R1;
	cout << R3 << endl;

	R3 = R1.deleteFirst();
	cout << R3 << endl;

	R3 = R3;
	cout << R3 << endl;

	return 0;
}
template <class A> ostream& operator<<(ostream& str, const Record<A>& rcrs){
    if(rcrs.Data.empty()) return str; // if empty data returns
    str << "{";
    for(auto& firstpair : rcrs.Data){
        str << firstpair.first << " {"; // first int print
        for(auto& secondpair : *firstpair.second){
            str << secondpair.first; // seconde int print
            str << secondpair.second; // print template (course)
        }
        str << "} ";      
    }
    str << " }" << endl;
    return str;
}

ostream& operator<<(ostream& str, course*& listc){
    str << '(' << listc->name << ' ' << listc->section << ' ' 
    << listc->credits << ' ' << listc->grade << ") ";
    return str;    
}

template <class T> void Record<T>::operator=(Record<T>&& R) {//Move Assignment
    //(*this).~Record(); // call deconstructor
    auto itr1{ Data.begin() };
    while (itr1 != Data.end()) {
        int firstint{ itr1->first };
        if (itr1->second == nullptr) {
            itr1++;
            Data.erase(firstint);
            continue;
        }
        auto& map1{ Data };
        auto& map2{ *itr1->second };
        auto itr2 = map2.begin();
        while (itr2 != map2.end()) {
            int secondint{ itr2->first };
            T* tplt = itr2->second;
            delete tplt;
            itr2++;
            map2.erase(secondint);
        }
        delete itr1->second;
        itr1++;
        Data.erase(firstint);
    }

    //if (Data.empty()) return;
    auto itrthat{ R.Data.begin() };
    while (itrthat != R.Data.end()) {
        auto& obj{ itrthat->second };
        Data.insert({ itrthat->first, obj });
        obj = nullptr;
        itrthat++;
    }
    cout << "Move Assignment" << endl;
    return;
}

template <class T> Record<T>::Record(Record<T>&& R) {//Move Constructor
    // pair<int, map<int, T*>*>::iterator itrthat {R.Data.begin()};
    auto itrthat {R.Data.begin()};
    //auto itrthis {(*this).Data.begin()};
    while(itrthat != R.Data.end()){
        //auto pt {itrthis->second};
        auto& obj {itrthat->second};
        (*this).Data.insert({ itrthat->first, obj });
        //Data.insert({ itrthat->first, obj });
        //auto itrnul {obj->begin()};
        //while(itrnul != obj->end()){
        //    itrnul->second = nullptr;
        //    itrnul++;
        //}
        obj = nullptr;
        itrthat++;
        //itrthis++;
    }

    cout << "Move Constructor" << endl;    
    return;
}

template<class T> Record<T> Record<T>::deleteFirst() {//DeleteFirst
/*
 copy the original object first, 
 then remove the first pair of Data,
 move the modified one to destiny object
 */
    Record<T> temp{*this};
    auto itr1 {temp.Data.begin()};
    int firstint {itr1->first};
    auto& map1{temp.Data};
    auto& map2{*itr1->second};
    auto itr2 = map2.begin();
    while(itr2 != map2.end()){
        int secondint {itr2->first};
        T* tplt = itr2->second;
        delete tplt;
        itr2++;
        map2.erase(secondint);
    }
    delete itr1->second;
    temp.Data.erase(firstint);
    
    cout << "DeleteFirst" << endl;    
    // return move(temp);
    return temp;
}

template<class T> Record<T>::~Record() {//Destructor
    auto itr1 {Data.begin()};
    while(itr1 != Data.end()){
        int firstint {itr1->first};
        if (itr1->second == nullptr) {
            itr1++;
            Data.erase(firstint);
            continue;
        }
        auto& map1{Data};
        auto& map2{*itr1->second};
        auto itr2 = map2.begin();
        while(itr2 != map2.end()){
            int secondint {itr2->first};
            T* tplt = itr2->second;
            delete tplt;
            itr2++;
            map2.erase(secondint);
        }
        delete itr1->second;
        itr1++;
        Data.erase(firstint);
    }
    Data.clear();
    cout << "Deconstructor" << endl;    
    return;
}
template <class T> void Record<T>::operator=(const Record<T>& R) {//Copy Assignment
    if(this == &R){
        cout << "Copy Assignment to self" << endl;
        return;
    } 
    for(auto& pr1 : R.Data){
        int firstint = pr1.first;
        Data.insert({firstint, new map<int, T*>()});
        for(auto& pr2: *pr1.second){
            int secondint = pr2.first;
            T tplt = *pr2.second;
            (*Data[firstint]).insert({secondint, new T(tplt)});
        }
    }
    cout << "Copy Assignment" << endl;    
    return;
}

template <class T> Record<T>::Record(const Record<T>& R) {    //Copy constructor
    // Record<T>::iterator itr{R.begin()};
    // auto itr{R.begin()};
    for(auto pr1 : R.Data){
        int firstint = pr1.first;
        Data.insert({firstint, new map<int, T*>()});
        for(auto& pr2: *pr1.second){
            int secondint = pr2.first;
            T tplt = *pr2.second;
            (*Data[firstint]).insert({secondint, new T(tplt)});
        }
    }
    cout << "Copy Constructor" << endl;    
}
template <class T> Record<T>::Record(const initializer_list < pair<int, initializer_list<pair <int, T>>>>& I) {
    // if(I == NULL) return;
    auto itr1 {I.begin()};
    while(itr1 != I.end()){
        int firstint {itr1->first};
        auto itr2 = itr1->second.begin();
        Data.insert({firstint, new map<int, T*>()}); // add first pair
        while(itr2 != itr1->second.end()){
            int secondint {itr2->first};
            T tplt = itr2->second;
            (*Data[firstint]).insert({secondint, new T(tplt)});            
            itr2++;
        }
        itr1++;
    }
    cout << "Initializer_List" << endl;
    return;
}

