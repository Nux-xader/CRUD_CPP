// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

void tokenize(string s, string del) {
	int start = 0;
	int end = s.find(del);
	while (end != -1) {
		cout << s.substr(start, end - start) << endl;
		start = end + del.size();
		end = s.find(del, start);
	}
	cout << s.substr(start, end - start);
}

int main(int argc, char const* argv[]) {
	// Takes C++ string with any separator
	string a = "Hisdfs||dfgdf||vsdfsd";
	tokenize(a, "||");
	cout << a.find("||");

	return 0;
}
