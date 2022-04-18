CIS554 HW8. Due: Thursday, 11:59pm, April 28, 2022. (This is more a take-home exam than
regular HW. Discussions with classmates are limited to clarifications.)
HW Objective: Store combinational logic circuits with one or more outputs to a database,
implemented using unordered_map. Each element of the unordered_map is {Circuit, pointer to
circuit name}.
(In actual design environment, it should be a pointer to circuit implementation, rather than
circuit name as is done here.) More explanation will be given in class.
As discussed in class, permuting inputs columns, output columns, or rows of a circuit’s truth
table will lead to different circuits which can re-use the original circuit and thus do not need to
be re-designed. Thus, we should only keep one circuit in the database for all of them.
You need to be able to add, delete, and find a circuit.
You will design the data structures and functions.
You need to design a class, Circuit.
class Circuit {
…
}
Your program will read in circuits and the operations from the file “input.txt”.
You will implement the following three functions:
void add(undordered_map<…> & DB, const Circuit & C);
void find(undordered_map<…>& DB, const Circuit & C);
void delete(unordered_map<…>& DB, const Circuit & C);
You need to implement overloaded operator<< to facilitate printing a circuit (See the possible
output messages below.)
//Input file “input.txt”, with the following format.
25//number of database operations, such as add, find, or delete
add
Circuit_1
3//number of inputs
2//number of outputs
000 10
001 00
010 00
011 10
100 00
101 11
110 01
111 11
add
Circuit_2
4
2
0000 01
0001 11
0010 00
…
find
Circuit_3
….
delete
Circuit_8
…
Add
Circuit 20
…
Possible output messages for “add” are in the following:
Circuit 4 is added to the database.
Circuit 4 is not added. It has a re-useable circuit, Circuit 1, in the database, whose truth table is
shown below.
Circuit_1
3
2
000 10
001 00
010 00
011 10
100 00
101 11
110 01
111 11
Possible output messages for “find” are in the following:
Circuit 4 does not have any re-useable circuit in the database.
Circuit 4 has a re-useable circuit, Circuit 1, in the database, whose truth table is shown below.
Circuit_1
3
2
000 10
001 00
010 00
011 10
100 00
101 11
110 01
111 11
Possible output messages for “delete” are in the following.
Circuit 4 does not have any re-useable circuit in the database.
Circuit 4 has a re-useable circuit, Circuit 1, in the database, whose truth table is shown below
and Circuit 1 is deleted from the database.
Circuit_1
3
2
000 10
001 00
010 00
011 10
100 00
101 11
110 01
111 11