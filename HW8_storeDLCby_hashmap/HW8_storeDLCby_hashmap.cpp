// CIS554 HW8. Due: Thursday, 11:59pm, April 28, 2022. (This is more a take-home exam than
// regular HW. Discussions with classmates are limited to clarifications.)
// HW Objective: Store combinational logic circuits with one or more outputs to a database,
// implemented using unordered_map. Each element of the unordered_map is {Circuit, pointer to
// circuit name}.
// (In actual design environment, it should be a pointer to circuit implementation, rather than
// circuit name as is done here.) More explanation will be given in class.
// As discussed in class, permuting inputs columns, output columns, or rows of a circuit’s truth
// table will lead to different circuits which can re-use the original circuit and thus do not need to
// be re-designed. Thus, we should only keep one circuit in the database for all of them.
// You need to be able to Add, Delete, and Find a circuit.
// You will design the data structures and functions.
// You need to design a class, Circuit.
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
// #include <map>
// #include <vector>
// #include <set>
using namespace std;
typedef unordered_map<string key, Circuit C>* theMap;
class TruthTable {
public:
	list<list<bool>>* table;
	//list<pair<int, list<bool>>>* table;
	TruthTable(){
		table = new list<list<bool>>{};
		// table = new list<pair<int, list<bool>>>{};
	}
	// void addLine(int lineNum, list<bool> line) {
	// 	(*table).insert(pair<lineNum, line>);
	// }
	void addLine(list<bool> line) {
		(*table).insert((*table).end(), line);
	}
	void delteTable() { delete table;}
};

class Circuit {
public:
	int inputNum;
	int outputNum;
	string name;
	string key;
	TruthTable value;
	
	Circuit() {
		inputNum = 0;
		outputNum = 0;
		name = "";
		key = "";
		value = *(new TruthTable());
	}
	void Delete() { value.delteTable();}
};

class Database {
public:
	undordered_map<string key, Circuit C>* warehouse;
	int circuitNum;
	
	Database(){
		circuitNum = 0;
		warehouse = new undordered_map<string key, Circuit C>;
	}
	void Add(undordered_map<…> & DB, const Circuit & C);
	void Find(undordered_map<…>& DB, const Circuit & C);
	void Delete(unordered_map<…>& DB, const Circuit & C);
	
};

template <typename T> ostream& operator<<(ostream& str, const Database& DB);
template <typename T> ostream& operator<<(ostream& str, const Circuit& C);
template <typename T> ostream& operator<<(ostream& str, const TruthTable& T);

int main(){
	Database DB1 = *(new Database());
	
	DB1.Add();
	DB1.Find();
	DB1.Delete();
	cout << DB1;
	return 0;
}
// Your program will read in circuits and the operations from the file “input.txt”.
// You will implement the following three functions:
template <typename T> ostream& operator<<(ostream& str, const Database& DB);
template <typename T> ostream& operator<<(ostream& str, const TruthTable& T){
	for (auto& pr: *(T.table)) {
		for (auto& i: pr.second)
			str << i;
		str << '\n';
	}
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const Circuit& C){
	str << C.name << endl;
	str << C.inputNum << '\n' << C.outputNum << '\n';
	str << C.TruthTable;
	return str;
}

void Add(undordered_map<…> & DB, const Circuit & C) {
// Add
// Circuit_2
// 4
// 2
// 0000 01
// 0001 11
// 0010 00
// Circuit 4 is added to the database.
// Circuit 4 is not added. It has a re-useable circuit, Circuit 1, in the database, whose truth table is

	cout << "Add\n";
	// cout << "Add\n" << C.name << endl;
	cout << C;
	
	if (ture)
		cout << "Circuit " << C.name << " is added to the database\n";
	else
		cout << "Circuit " << C.name << " is not added.It has a re-useable circuit,"
		<< " in the database, whose truth table is shown below.\n";
}
void Find(undordered_map<…>& DB, const Circuit & C){
// Find
// Circuit_3
// Circuit 4 does not have any re-useable circuit in the database.
// Circuit 4 has a re-useable circuit, Circuit 1, in the database, whose truth table is shown below.
	
	cout << "Find\n";
	cout << C;

	if (ture)
		cout << "Circuit " << C.name << " does not have any re-useable circuit in the database.\n";
	else
		cout << "Circuit " << C.name << " has a re-useable circuit,"
		<< " in the database, whose truth table is shown below.\n";
	
}
void Delete(unordered_map<…>& DB, const Circuit & C){
// Delete
// Circuit_8
// Circuit 4 does not have any re-useable circuit in the database.
// Circuit 4 has a re-useable circuit, Circuit 1, in the database, whose truth table is shown below
// and Circuit 1 is deleted from the database.

	cout << "Delete\n";
	cout << C;

	if (ture) {
		cout << "Circuit " << C.name << " does not have any re-useable circuit in the database.\n";

	}
	else {
		cout << "Circuit " << C.name << " has a re-useable circuit,"
		<< " in the database, whose truth table is shown below.\n";

		cout << "Circuit " << " is deleted from the database."


	}
}
// You need to implement overloaded operator<< to facilitate printing a circuit (See the possible
// output messages below.)
// Input file “input.txt”, with the following format.
// 25//number of database operations, such as Add, Find, or Delete
// Add
// Circuit_1
// 3//number of inputs
// 2//number of outputs
// 000 10
// 001 00
// 010 00
// 011 10
// 100 00
// 101 11
// 110 01
// 111 11
// Add
// Circuit_2
// 4
// 2
// 0000 01
// 0001 11
// 0010 00
// …
// Find
// Circuit_3
// ….
// Delete
// Circuit_8
// …
// Add
// Circuit 20
// …
// Possible output messages for “add” are in the following:
// Circuit 4 is added to the database.
// Circuit 4 is not added. It has a re-useable circuit, Circuit 1, in the database, whose truth table is
// shown below.
// Circuit_1
// 3
// 2
// 000 10
// 001 00
// 010 00
// 011 10
// 100 00
// 101 11
// 110 01
// 111 11
// Possible output messages for “find” are in the following:
// Circuit 4 does not have any re-useable circuit in the database.
// Circuit 4 has a re-useable circuit, Circuit 1, in the database, whose truth table is shown below.
// Circuit_1
// 3
// 2
// 000 10
// 001 00
// 010 00
// 011 10
// 100 00
// 101 11
// 110 01
// 111 11
// Possible output messages for “delete” are in the following.
// Circuit 4 does not have any re-useable circuit in the database.
// Circuit 4 has a re-useable circuit, Circuit 1, in the database, whose truth table is shown below
// and Circuit 1 is deleted from the database.
// Circuit_1
// 3
// 2
// 000 10
// 001 00
// 010 00
// 011 10
// 100 00
// 101 11
// 110 01
// 111 11