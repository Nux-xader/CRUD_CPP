#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// return admin if login as admin, and return karyawan if login as karyawan
string login(string username, string password) {
	// decarate var
	ifstream admin, karyawan;
	string data;
	int i = 0;

	// Check admin account
	admin.open("db/admin.txt");
	while(!admin.eof()) {
		i++;
		admin >> data;
		if ((i%2) != 0) {
			if (username == data) {
				admin >> data;
				if (password == data) {
					return "admin";
				} else {
					return "wrong";
				}
				break;
			}
		}
	}

	// reset value i
	i = 0;
	// Check karyawan account
	karyawan.open("db/karyawan.txt");
	while(!karyawan.eof()) {
		i++;
		karyawan >> data;
		if ((i%2) != 0) {
			if (username == data) {
				karyawan >> data;
				if (password == data) {
					return "karyawan";
				} else {
					return "wrong";
				}
				break;
			}
		}
	}
	return "wrong";
}


int main(){
	string username, password;
	string banner = "\tRESTO APP V1.0.0\n";
	cout << banner << endl;

	// Login input
	cout << "Login" << endl;
	cout << "Username : ";
	cin >> username;
	cout << "Password : ";
	cin >> password;

	string account = login(username, password);
	cout << account << endl;
	cin.get();
	
	return 0;
}