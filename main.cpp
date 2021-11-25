// include standard library
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// declarate banner var
string banner = "\tRESTO APP V1.0.0\n";


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


// Check if account already regristed
bool check_already_account(string username, string type_account) {
	// decarate var
	ifstream admin, karyawan;
	string data;

	// Check admin account
	if (type_account == "admin") {
		int i = 0;
		admin.open("db/admin.txt");
		while(!admin.eof()) {
			i++;
			admin >> data;
			if ((i%2) != 0) {
				if (username == data) {
					return true;
				}
			}
		}
		return false;

	} else if (type_account == "karyawan") {
		// Check karyawan account
		int i = 0;
		karyawan.open("db/karyawan.txt");
		while(!karyawan.eof()) {
			i++;
			karyawan >> data;
			if ((i%2) != 0) {
				if (username == data) {
					return true;
				}
			}
		}
		return false;
	}

	return false;
}



void add_admin_account() {
	string username, password, add_again;
	while (true) {
		clr_screen();
		cout << banner << endl;
		cout << "Tambah akun admin" << endl;

		// always check username if already regristed
		while (true) {
			cout << "Username : ";
			cin >> username;
			// Checking username
			if (check_already_account(username, "admin")) {
				cout << "Akun "<< username <<"telah terdaftar sebelumnya!" << endl;
				cout << "Gunakan username lain untuk menambahkan akun baru" << endl;
			} else { // braek if username not already
				break;
			}
		}

		// input password
		cout << "Password : ";
		cin >> password;
		cout << "Akun berhasil di tambahkan" << endl;
		cout << "Apakah ingin menambahkan akun lagi? (y) : ";
		cin >> add_again;
		if ((add_again == "y") | (add_again == "Y")) {

		} else {
			break;
		}
	}
}


void admin_menu() {
	clr_screen();
	cout << banner << endl;
	cout << "Menu :" << endl;
	cout << "1. Tambah akun admin" << endl;
	cout << "2. Ubah password admin" << endl;
	cout << "3. Tambah akun karyawan" << endl;
	cout << "4. Ubah password karyawan" << endl;
	cout << "5. Lihat data karyawan" << endl;
	cout << "0. Keluar\n" << endl;
}

void admin() {
	string choice;
	admin_menu();
	while (true) {
		cout << "Pilih : ";
		cin >> choice;
		if (choice == "0"){
			break;
		} else if (choice == "1") {
			add_admin_account();
			admin_menu();
		} else {
			cout << "menu berikutnya masih tahap pengembangan" << endl;
			break;
		}
	}
}

int main(){
	// declarate variable
	string username, password, x;
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
			admin();
			break;
		} else if (login(username, password) == "karyawan") { // Check if login as karyawan
			cout << "Anda login sebagai karyawan" << endl;
			cout << "menu selanjutnya masih tahap pengembangan" << endl;
			break;
		} else { // statment for wrong username or password
			cout << "Wrong username or password" << endl;
			cout << "ingin login ulang? (y/n) : ";
			cin >> x;
			if ((x == "n") | (x == "N")) {
				break;
			} else if ((x == "y") | (x == "Y")) {

			} else {
				cout << "Anda memasukkan inputan yang salah" << endl;
				break;
			}
		}
	}
	
	return 0;
}