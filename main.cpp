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
					admin.close();
					return "admin";
				} else {
					return "wrong";
				}
				break;
			}
		}
	}
	admin.close();

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
					karyawan.close();
					return "karyawan";
				} else {
					return "wrong";
				}
				break;
			}
		}
	}
	karyawan.close();
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
					admin.close();
					return true;
				}
			}
		}
		admin.close();
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
					karyawan.close();
					return true;
				}
			}
		}
		karyawan.close();
		return false;
	}

	return false;
}



void add_admin_account() {
	ifstream admin;
	ofstream adminsave;
	string username, password, add_again, buffer, data;
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

		// read admin.txt and save to var data
		admin.open("db/admin.txt");
		while(!admin.eof()) {
			getline(admin, buffer);
			data+=buffer+"\n";
		}
		admin.close();
		// add new username, password
		data+=username+" "+password;
		// saving to file
		adminsave.open("db/admin.txt");
		adminsave << data;
		adminsave.close();

		cout << "Akun berhasil di tambahkan" << endl;
		cout << "Apakah ingin menambahkan akun lagi? (y) : ";
		cin >> add_again;
		if ((add_again == "y") | (add_again == "Y")) {

		} else {
			break;
		}
	}
}


void change_paswd(string type_account) {
	// declarate var
	int i;
	string result = "";
	string path, data, username, password, change_again;
	ifstream file;
	ofstream savefile;

	// clear screen, and view banner
	clr_screen();
	cout << banner << endl;


	// checking account type
	if (type_account == "admin") {
		path = "db/admin.txt";
	} else if (type_account == "karyawan") {
		path = "db/karyawan.txt";
	}

	i = 0;
	cout << "Daftar username "<< type_account <<" :" << endl;
	file.open(path);
	while(!file.eof()) {
		i++;
		file >> data;
		if ((i%2) != 0) {
			cout << data << endl;
		}
	}
	file.close();

	cout << "\n";
	while (true) {
		cout << "Masukkan username : ";
		cin >> username;
		i = 0;
		if (check_already_account(username, type_account)) {
			cout << "Masukkan password baru : ";
			cin >> password;

			// Update password
			file.open(path);
			while(!file.eof()) {
				file >> data;
				if (username == data) {
					file >> data;
				} else {
					result+=data+" ";
					file >> data;
					result+=data+"\n";
				}
			}
			file.close();
			result+=username+" "+password;

			// saving to file
			savefile.open(path);
			savefile << result;
			savefile.close();

			cout << "Password berhasil di update" << endl;
			cout << "Apakah ingin mengubah password lagi? (y) : ";
			cin >> change_again;
			if ((change_again == "y") | (change_again == "Y")) {
				// clear screen, and view banner
				clr_screen();
				cout << banner << endl;
				cout << "Daftar username "<< type_account <<" :" << endl;
				file.open(path);
				while(!file.eof()) {
					i++;
					file >> data;
					if ((i%2) != 0) {
						cout << data << endl;
					}
				}
				file.close();
			} else {
				break;
			}

		} else {
			cout << "Mohom memasukkan username yang telah ada" << endl;
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
		} else if (choice == "2") {
			change_paswd("admin");
		}
		else {
			cout << "menu berikutnya masih tahap pengembangan" << endl;
			break;
		}
		admin_menu();
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