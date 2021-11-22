#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

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

void split_string(string teks) {
	string to;
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
