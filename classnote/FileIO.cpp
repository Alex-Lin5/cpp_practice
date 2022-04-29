
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int main() {


	ofstream  Out("output.txt");//laready run Out.open();
	Out << "Write a string to output.txt" << endl;
	int i1{ 50 }, i2{ 40 };
	double d1{ 3.14 };
	char c1{ 'd' };
	Out << i1 << " " << i2 << " " << d1 << " " << c1 << endl;
	Out.close();

	ifstream In("output.txt");
	string s1;
	//In >> s1;//s1 = "Write";
	getline(In, s1);
	cout << s1 << endl;

	int x, y;
	double d2;
	char c2;
	In >> x >> y >> d2 >> c2;

	In.close();


	ifstream  Input("output1.txt");
	vector<string> V;
	string s2;
	while (Input >> s2) {
		V.push_back(s2);
	}
	Input.close();
	for (auto& i : V) cout << i << endl;

	string s3{ "ABCDEFG" };
	for (int i = 0; i < s3.size(); ++i) {
		cout << s3[i] << " ";//s3.at(i)
	}
	
	return 0;
}