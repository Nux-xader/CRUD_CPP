#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#define max 8

using namespace std;


string strings[max];


int get_length_str_array(data string[]) {
	int result = *(&data + 1) - data;
	return result;
}

string read_file(string path) {
	string data;
	ifstream f(path);
	if(f) {
		ostringstream ss;
		ss << f.rdbuf(); // reading data
		data = ss.str();
	}
	return data;
}

string* split_string(string teks) {
	string to;
	string* result;
	int num = 0;

	stringstream ss(teks);
	while(getline(ss, to, '\n')) {
		num+=1;
	}
	string result[num];
	num = 0;
	while(getline(ss, to, '\n')) {
		result[num] = to;
		num+=1;
	}

	cout << result[0]<<endl;
	cout << result[1]<<endl;
	// return result;
}

int main(){
	string admin_db;
	admin_db = read_file("db/admin.txt");
	// cout << admin_db;
	split_string("gerger\nrdgr\ndfdf");
	return 0;
}
