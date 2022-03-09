
#include <iostream>
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

ostream& operator<<(ostream& str, map<int, map<int, list<course*>*>> DB) {
	for (auto& i : DB) {
		str << "Student ID: " << i.first << endl;
		for (auto& j : i.second) {
			str << "Semester: " << j.first << endl;
			if (j.second == nullptr) continue;
			for (auto& k : *j.second) {
				str << "(" << k->name << " " << k->section << " " << k->credits << " " << k->grade << ")\t";
			}
			cout << endl;
		}
		cout << endl;
	}
	return str;
}

int main() {
	map<int, map<int, list<course*>*>> DB;
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
	cout << endl;
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);
	print_student_all_courses(DB, 11112);
	cout << endl;

	cout << DB << endl;
	remove_student(DB, 11111);
	cout << DB << endl;

	//For testing
	/*add_student(DB, 11113);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+");
	add_course(DB, 20171, 11113, C1);
	add_course(DB, 20171, 11113, C2);
	print_student_semester_courses(DB, 20171, 11113);
	print_student_semester_courses(DB, 20172, 11113);
	drop_course(DB, 20171, 11113, C2);
	drop_course(DB, 20171, 11113, C2);
	cout << DB << endl;
	add_course(DB, 20171, 11113, C1);
	drop_course(DB, 20171, 11113, C1);
	cout << DB << endl;
	cout << "Semester Courses " << endl;
	print_student_semester_courses(DB, 20171, 11113);
	cout << "ALLLLLLLLLLLLLLLLLLLLLLLLL Semester Courses " << endl;
	print_student_all_courses(DB, 11113);
	remove_student(DB, 11113);
	cout << DB<<endl;*/

	return 0;
}

void add_student(map<int, map<int, list<course*>*>>& DB, int id) {
	if (DB.find(id) == DB.end()) {
		DB.insert({ id, map<int, list<course*>*>() });
	}
	else
		cout << "Student already added to DB" << endl;
}

void add_course(map<int, map<int, list<course*>*>>& DB, int semester, int id, course c) {
	if (DB.find(id) == DB.end()) return;
	for (auto& i : DB[id]) {
		if (i.second == nullptr) continue;
		for (auto& j : *i.second) {
			if (*j == c) { cout << "Course already taken " << c.name << endl; return; }
		}
	}
	if (DB[id].find(semester) == DB[id].end() || DB[id][semester] == nullptr)
	{
		list<course*>* l = new list<course*>();
		DB[id][semester] = l;
	}
	list<course*> ::iterator it;
	for (it = DB[id][semester]->begin();it != DB[id][semester]->end();it++) {
		if (c < **it)
			break;
	}
	DB[id][semester]->insert(it, new course(c));
}

void print_student_semester_courses(map<int, map<int, list<course*>*>>& DB, int semester, int id) {
	if (DB.find(id) == DB.end()) return;
	if (DB[id].find(semester) == DB[id].end())
		return;
	else {
		cout << "Student ID: " << id << endl;
		cout << "Semester: " << semester << endl;
		list<course*> ::iterator it;
		if (DB[id][semester] == nullptr) return;
		for (it = DB[id][semester]->begin();it != DB[id][semester]->end();it++)
			cout << "(" << (*it)->name << " " << (*it)->section << " " << (*it)->credits << " " << (*it)->grade << ")\t";
		cout << endl;
	}
}


void drop_course(map<int, map<int, list<course*>*>>& DB, int semester, int id, course c) {
	if (DB.find(id) == DB.end()) return;
	if (DB[id].find(semester) == DB[id].end())
		return;
	if (DB[id][semester] == nullptr) return;
	else {
		list<course*> ::iterator it = DB[id][semester]->begin();
		if (DB[id][semester]->size() == 1 && c == **DB[id][semester]->begin()) {
			delete* it;
			delete DB[id][semester];
			DB[id][semester] = nullptr;
			return;
		}
		for (it = DB[id][semester]->begin();it != DB[id][semester]->end();it++) {
			if (c == **it)
				break;
		}
		if (it != DB[id][semester]->end()) {
			delete* it;
			DB[id][semester]->erase(it);
		}
	}
}

void print_student_all_courses(map<int, map<int, list<course*>*>>& DB, int id) {
	if (DB.find(id) == DB.end()) return;
	cout << "Student ID: " << id << endl;
	for (auto& i : DB[id]) {
		cout << "Semester: " << i.first << endl;
		if (i.second == nullptr) continue;
		for (auto& j : *i.second) {
			cout << "(" << j->name << " " << j->section << " " << j->credits << " " << j->grade << ")\t";
		}
		cout << endl;
	}
}

void remove_student(map<int, map<int, list<course*>*>>& DB, int id) {
	if (DB.find(id) == DB.end()) return;
	//DB.erase(id);
	for (auto& j : DB[id]) {
		if (j.second == nullptr) continue;
		for (auto& k : *j.second) {
			delete k;
		}
		delete DB[id][j.first];
	}
	DB.erase(id);
}