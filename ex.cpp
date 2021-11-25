#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
	string str = "abcdefghij";

	cout << "After erase : ";
	cout << str.substr (0, str.length()-1);
    return 0;
}