//HW7. Due: Wednesday, April 20 at 11:59pm
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;
//For all comparisons, compare the sums of all int objects in the key parts of structures.
//For all hashing, use h(sum of all int objects in the key parts of structures), where hash<int> h;
int main() {
//The following won't run. Fix it.
//In addition, create your initialized values. For each STL container, at least three elements are required.
//Overload operator<< to allow "cout << H1 << endl;"
unordered_map< map < list<set<int*, myCompareClass>*>, vector<int*>* >, vector<int>> UM{ ... };
cout << UM << endl;
return 0;
}
/*
The following is a possible output.
Depending on the initialization values you select, the output values will be different.
However, do follow the same format for set, map, vector and list.
{
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 19 13 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 1 7 13 > < 1 2 15 > < 6 16 20 > ]
( 5 19 4 ) } ( 7 8 9 )
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 11 3 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 3 4 5 > < 2 5 18 > < 2 6 13 > ] ( 5 11
13 ) } ( 1 2 3 )
{ [ < 5 6 13 > < 3 4 5 > < 3 9 11 > ] ( 4 14 3 ) [ < 5 7 13 > < 1 11 15 > < 3 6 8 > ] ( 5 12 3 ) [ < 3 4 13 > < 2 5 12 > < 2 13
16 > ] ( 5 17 2 ) } ( 3 5 7 )
}
*/