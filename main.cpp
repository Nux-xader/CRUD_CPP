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


// Function for clear screen
void clr_screen() {
	// if oprating system is windows 32bit or 64bit use cls
	#ifdef _WIN32
		system("cls");
	// if oprating system not windows use clear
	#else
	    system("clear");
	#endif
}

int main(){
	// declarate variable
	string username, password, x;
	string banner = "\tRESTO APP V1.0.0\n";
	while (true) {
		clr_screen();
		cout << banner << endl;

		// Login input
		cout << "Login" << endl;
		cout << "Username : ";
		cin >> username;
		cout << "Password : ";
		cin >> password;

		// Check if login as admin
		if (login(username, password) == "admin") {
			cout << "Anda login sebagai admin" << endl;
			cout << "menu selanjutnya masih tahap pengembangan" << endl;
			break;
		// Check if login as karyawan
		} else if (login(username, password) == "karyawan") {
			cout << "Anda login sebagai karyawan" << endl;
			cout << "menu selanjutnya masih tahap pengembangan" << endl;
			break;
		// statment for wrong username or password
		} else {
			cout << "Wrong username or password" << endl;
			cout << "ingin login ulang? (y/n) : ";
			cin >> x;
			if (x == "n" | x == "N" ) {
				break;
			} else if (x != "y" | x != "Y" ) {
				cout << "Anda memasukkan inputan yang salah" << endl;
				break;
			}
		}
	}
	
	return 0;
}