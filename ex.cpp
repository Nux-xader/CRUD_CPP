#include <iostream>
using namespace std;


// Fuction for reverse string
string reverseStr(string data) {
	string result = "";
	for (int i=data.length()-1; i>=0; i--) {
		result+=data[i];
	}
	return result;
}

string integer_formater(string num) {
	string result = "";

	// reverse string num
	num = reverseStr(num);

	// adding . when 3x loops
	for (int i=1; i <= num.length(); ++i) {
		result+=num[i-1];
		if (((i%3) == 0) and (i < num.length())) {
			result+=".";
		}
	}

	// reverse string result
	result = reverseStr(result);

	return result;
}

int main() {
	string text = integer_formater("1500");
	cout << text << endl;
	return 0;
}