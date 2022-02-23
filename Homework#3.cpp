//HW3
//Due: 11:59PM, February 23, Wednesday.

// Does the class of course is inserted into the database directly as an object, or the member of course are passed by separately?
// How does the course sort in the list of pointers? The course class defines operator'<', does sorting operation achieved by a for loop?

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }
	bool operator<(course c) { return (name < c.name); }
	bool operator==(course c) { return (name == c.name); }
};
void add_student(map<int, map<int, list<course*>*>>& DB, int id);
//Do nothing and return if the student is already in DB.

void remove_student(map<int, map<int, list<course*>*>>& DB, int id);
//Do nothing and ruturn if the student is not in DB.

void add_course(map<int, map<int, list<course*>*>>& DB, int semester, int id, course c);
//20171: Spring semester of 2017; 20172: Fall semester of 2017
//All courses in the list should be sorted according to name (ascending order)
//No duplicated courses allowed even if they are in different semesters.

void drop_course(map<int, map<int, list<course*>*>>& DB, int semester, int id, course c);
//Do nothing and return if the student, semester, or course is not in DB.

void print_student_semester_courses(map<int, map<int, list<course*>*>>& DB, int semester, int id);
//Do nothing and return if the student or semester is not in DB.

void print_student_all_courses(map<int, map<int, list<course*>*>>& DB, int id);
//Do nothing and return if the student is not in DB.

ostream& operator<<(ostream& str, const map<int, map<int, list<course*>*>>& DB);
ostream& operator<<(ostream& str, const course& crs);
int main() {
	map<int, map<int, list<course *>*>> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	print_student_all_courses(DB, 11111);//ID GPA

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	// cout << DB << endl;
	// remove_student(DB, 11111);
	// cout << DB << endl;

	return 0;
}

void add_student(map<int, map<int, list<course*>*>>& DB, int id){
    if(DB.find(id) != DB.end()) return; // student already added
    DB.insert({id, map<int, list<course*>*>()});

    // DB.insert({id, auto});
}

void remove_student(map<int, map<int, list<course*>*>>& DB, int id){
    if(DB.find(id) == DB.end()) return; // no student in this id
    else{
        for(auto& sem : DB[id]){
            for(auto& listc : *sem.second){
                delete listc;// remove course
            }
            delete sem.second;// remove list
            DB[id].erase(sem.first);
        }
        DB.erase(id);
    }
    return;       
}
void add_course(map<int, map<int, list<course*>*>>& DB, int semester, int id, course c){
    if(DB.find(id) == DB.end()) return; // no student in this id
    for(auto& sem : DB[id]){ // find course in another semester
        for(auto& listc : *sem.second){
            if(*listc == c) return;
        }
    }
    if(DB[id].find(semester) == DB[id].end()){ // empty semester
        // DB[id].insert({semester, list<course*>*}); 
        ;
    }
    auto& listc {*DB[id][semester]};
    for(auto&itr : listc){
        if(c < *itr)
            itr++;
        else{
            // listc.insert(itr, new course (c.name, c.section, c.credits, c.grade));
            break;
        }

    }

    // auto itr = find(*listc.begin(), *listc.end(), c);
    // // cout << typeid(itr).name() << endl;
    // if(itr != *listc.end()) return; //duplicate course
    // else{
    //     itr = *listc.begin();
    //     // cout << **itr << endl;
    //     while(itr != *listc.end()){
    //         // if(itr->course < course c)
    //         if(*itr < c)
    //             itr++;
    //         else
    //             break;
    //     }
    //     // auto cc = new course (c.name, c.section, c.credits, c.grade);
        // listc.insert({itr, new course {c}});
    // }
    return;
    // cout << **couli.begin() << endl;
}
void drop_course(map<int, map<int, list<course*>*>>& DB, int semester, int id, course c){
    if(DB.find(id) == DB.end()) return; // no student in this id
    else if(DB[id].find(semester) == DB[id].end()) return; // empty semester
    auto& listc {*DB[id][semester]};
    auto itr = find(*listc.begin(), *listc.end(), c);
    if(itr == *listc.end()) return; // course is not found
    else{
        delete itr; // delete course
        if(listc.begin() == listc.end()){ // delete empty list if no course in semster
            delete &listc;
            DB[id].erase(semester);
        }
    }
    return;
}

void print_student_all_courses(map<int, map<int, list<course*>*>>& DB, int id){
    if(DB.find(id) == DB.end()) return; // no student in this id
    else{
        cout << "Student ID: " << id << endl;
        for(auto& sem : DB[id]){
            cout << "semester: " << sem.first << endl;
            for(auto& listc : *sem.second){
                cout << '(' << listc << ')' << ' ';
            }
            cout << endl;
        }

    }
    return; 
}

void print_student_semester_courses(map<int, map<int, list<course*>*>>& DB, int semester, int id){
    if(DB.find(id) == DB.end()) return; // no student in this id
    else{
        cout << "Student ID: " << id << endl;
        cout << "semester: " << semester << endl;
        for(auto& listc : *DB[id][semester]){
            cout << '(' << listc << ')' << ' ';
        }
        cout << endl;
        }
    return;
}

ostream& operator<<(ostream& str, map<int, map<int, list<course*>*>>& DB){
	for (auto& id : DB) {
        str << "Student ID: " << id.first << endl;
		for (auto& sem : id.second) {
        str << "semester: " << sem.first << endl;
            for (auto& listc : *sem.second)
			    str << '(' << listc << ')' << ' ';
            str << endl;
		}
	}
    str << endl;
	return str;
}
