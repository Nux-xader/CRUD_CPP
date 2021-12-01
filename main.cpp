// include standard library
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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


// check contains string
bool str_in_str(string str1, string str2) {
	if (str1.find(str2) != string::npos) {
		return true;
	} else {
		return false;
	}
	return false;
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
			getline(cin, username);

			// replacing space with unique string
			if (str_in_str(username, " ")) {
				username.replace(username.find(" "), 1, "_-_");
			}

			// Checking username
			if (check_already_account(username, "admin")) {
				cout << "Akun "<< username <<" telah terdaftar sebelumnya!" << endl;
				cout << "Gunakan username lain untuk menambahkan akun baru" << endl;
			} else { // braek if username not already
				break;
			}
		}

		// input password
		cout << "Password : ";
		getline(cin, password);

		// replacing space with unique string
		if (str_in_str(password, " ")) {
			password.replace(password.find(" "), 1, "_-_");
		}


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
		getline(cin, add_again);
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
	string path, data, username, password, change_again, buffer;
	ifstream file, karyawan;
	ofstream savefile, karyawansave;

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
			// replacing space with unique string
			if (str_in_str(data, "_-_")) {
				data.replace(data.find("_-_"), 3, " ");
			}
			cout << data << endl;
		}
	}
	file.close();

	cout << "\n";
	while (true) {
		cout << "Masukkan username : ";
		getline(cin, username);
		// replacing space with unique string
		if (str_in_str(username, " ")) {
			username.replace(username.find(" "), 1, "_-_");
		}
		i = 0;
		if (check_already_account(username, type_account)) {
			cout << "Masukkan password baru : ";
			getline(cin, password);

			// replacing space with unique string
			if (str_in_str(password, " ")) {
				password.replace(password.find(" "), 1, "_-_");
			}

			// reverse unique string
			if (str_in_str(username, "_-_")) {
				username.replace(username.find("_-_"), 3, " ");
			}
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


			if (type_account == "karyawan") {
				// Update karyawan bio
				result = "";
				karyawan.open("db/bio_karyawan.txt");
				while(!karyawan.eof()) {
					karyawan >> buffer;
					result+=" "+buffer;
					karyawan >> buffer;
					result+=" "+buffer;
					if (buffer == username) {
						karyawan >> buffer;
						result+=" "+password;
					} else {
						karyawan >> buffer;
						result+=" "+buffer;
					}
					karyawan >> buffer;
					result+=" "+buffer;
					karyawan >> buffer;
					result+=" "+buffer;
					karyawan >> buffer;
					result+=" "+buffer;
				}
				karyawan.close();

				// saving to file
				karyawansave.open("db/bio_karyawan.txt");
				karyawansave << result;
				karyawansave.close();
			}


			cout << "Password berhasil di update" << endl;
			cout << "Apakah ingin mengubah password lagi? (y) : ";
			getline(cin, change_again);
			if ((change_again == "y") | (change_again == "Y")) {
				// clear screen, and view banner
				clr_screen();
				cout << banner << endl;
				i = 0;
				cout << "Daftar username "<< type_account <<" :" << endl;
				file.open(path);
				while(!file.eof()) {
					i++;
					file >> data;
					if ((i%2) != 0) {
						// replacing space with unique string
						if (str_in_str(data, "_-_")) {
							data.replace(data.find("_-_"), 3, " ");
						}
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


void add_karyawan_account() {
	ifstream karyawan, bio_karyawan;
	ofstream karyawansave, bio_karyawansave;
	string username, password, add_again, buffer, data, name, address, birth_date_place, salary, data_bio_karyawan;
	int i;
	while (true) {
		clr_screen();
		cout << banner << endl;
		cout << "Tambah akun karyawan" << endl;

		// always check username if already regristed
		while (true) {
			cout << "Username : ";
			getline(cin, username);
			// replacing space with unique string
			if (str_in_str(username, " ")) {
				username.replace(username.find(" "), 1, "_-_");
			}

			// Checking username
			if (check_already_account(username, "karyawan")) {
				cout << "Akun "<< username << "telah terdaftar sebelumnya!" << endl;
				cout << "Gunakan username lain untuk menambahkan akun baru" << endl;
			} else { // braek if username not already
				break;
			}
		}

		// input password
		cout << "Password : ";
		getline(cin, password);
		// replacing space with unique string
		if (str_in_str(password, " ")) {
			password.replace(password.find(" "), 1, "_-_");
		}

		// input information account karyawan
		cout << "Nama : ";
		getline(cin, name);
		// replacing space with unique string
		i = 0;
		while (i <= name.length()){
			if (str_in_str(name, " ")) {
				name.replace(name.find(" "), 1, "_-_");
			}
			i++;
		}


		cout << "Tempat tanggal lahir : ";
		getline(cin, birth_date_place);
		// replacing space with unique string
		i = 0;
		while (i <= birth_date_place.length()){
			if (str_in_str(birth_date_place, " ")) {
				birth_date_place.replace(birth_date_place.find(" "), 1, "_-_");
			}
			i++;
		}

		cout << "Asal : ";
		getline(cin, address);
		// replacing space with unique string
		i = 0;
		while (i <= address.length()){
			if (str_in_str(address, " ")) {
				address.replace(address.find(" "), 1, "_-_");
			}
			i++;
		}

		cout << "Gaji : ";
		getline(cin, salary);
		// replacing space with unique string
		i = 0;
		while (i <= salary.length()){
			if (str_in_str(salary, " ")) {
				salary.replace(salary.find(" "), 1, "_-_");
			}
			i++;
		}

		// read karyawan.txt and save to var data
		karyawan.open("db/karyawan.txt");
		while(!karyawan.eof()) {
			getline(karyawan, buffer);
			data+=buffer+"\n";
		}
		karyawan.close();
		// add new username, password
		data+=username+" "+password;
		// saving to file
		karyawansave.open("db/karyawan.txt");
		karyawansave << data;
		karyawansave.close();

		// read bio_karyawan.txt and save to var data
		bio_karyawan.open("db/bio_karyawan.txt");
		while(!bio_karyawan.eof()) {
			getline(bio_karyawan, buffer);
			data_bio_karyawan+=buffer+"\n";
		}
		bio_karyawan.close();
		// add new bio data
		data_bio_karyawan+=name+" "+username+" "+password+" "+birth_date_place+" "+address+" "+salary;
		// saving to file
		bio_karyawansave.open("db/bio_karyawan.txt");
		bio_karyawansave << data_bio_karyawan;
		bio_karyawansave.close();		

		cout << "Akun berhasil di tambahkan" << endl;
		cout << "Apakah ingin menambahkan akun lagi? (y) : ";
		getline(cin, add_again);
		if ((add_again == "y") | (add_again == "Y")) {

		} else {
			break;
		}
	}
}


// void view_bio_karyawan() {
// 	int i = 1;
// 	int x = 0;
// 	int y = 0;
// 	string buffer;
// 	ifstream file;

// 	clr_screen();
// 	cout << "\t\t\t\t" << banner << endl;
// 	cout << "-----------------------------------------------------------------------------------------------------" << endl;
// 	cout << "| Nama\t\t| Username\t| Password\t| Tempat Tgl lahir\t| Asal\t\t| Gaji\t|" << endl;
// 	cout << "-----------------------------------------------------------------------------------------------------" << endl;
// 	file.open("db/bio_karyawan.txt");
// 	while(!file.eof()) {
// 		getline(file, buffer);
// 		y = buffer.length();
// 		while (true) {
// 			if (x >= y) {
// 				break;
// 			}
// 			x+=1;
// 			if (str_in_str(buffer, " ")) {
// 				buffer.replace(buffer.find(" "), 1, "\t|");
// 			}
// 		}
// 		x = 1;
// 		while (true) {
// 			if (str_in_str(buffer, "_-_")) {
// 				buffer.replace(buffer.find("_-_"), 3, " ");
// 			}
// 			if (x >= y) {
// 				break;
// 			}
// 			x++;
// 		}

// 		x = 1;
// 		while (true) {
// 			if (str_in_str(buffer, "\t|")) {
// 				buffer.replace(buffer.find("\t|"), 3, "\t| ");
// 			}
// 			if (x >= y) {
// 				break;
// 			}
// 			x++;
// 		}

// 		cout << buffer << endl;
// 		break;
// 	}

// 	file.close();
// 	cout << "[Press Enter to Continue]";
// 	getline(cin, buffer);
// }


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


void admin_menu() {
	clr_screen();
	cout << banner << endl;
	cout << "Menu :" << endl;
	cout << "1. Tambah akun admin" << endl;
	cout << "2. Ubah password admin" << endl;
	cout << "3. Tambah akun karyawan" << endl;
	cout << "4. Ubah password karyawan" << endl;
	cout << "0. Keluar\n" << endl;
}

void admin() {
	string choice;
	admin_menu();
	while (true) {
		cout << "Pilih : ";
		getline(cin, choice);
		if (choice == "0"){
			break;
		} else if (choice == "1") {
			add_admin_account();
		} else if (choice == "2") {
			change_paswd("admin");
		} else if (choice == "3") {
			add_karyawan_account();
		} else if (choice == "4") {
			change_paswd("karyawan");
		} else {
			cout << "menu berikutnya masih tahap pengembangan" << endl;
			break;
		}
		admin_menu();
	}
}


// view list menu
int view_menu(string type_menu) {
	ifstream menu;
	string buffer;
	int num = 1;

	// clearing screen, view banner
	clr_screen();
	cout << banner << endl;

	// read db menu
	if (type_menu == "foods") {
		menu.open("db/foods.txt");
	} else if (type_menu == "drinks") {
		menu.open("db/drinks.txt");
	}

	while(!menu.eof()) {
		menu >> buffer;
		for (int i = 0; i < buffer.length(); ++i) {
			if (str_in_str(buffer, "_-_")) {
				buffer.replace(buffer.find("_-_"), 3, " ");
			}
		}

		cout << num << ". " << buffer;
		menu >> buffer;
		cout << " Rp " << integer_formater(buffer) << endl;
		num++;
	}
	cout << "0. Tidak memesan makanan\n" << endl;

	return num;
}


// function for convert string to integer
int string_to_int(string data) {
	int result = 0;
	result = stoi(data);
	return result;
}


string int_to_string (int data) {
	string result;
	stringstream ss;
	ss << data;
	ss >> result;
	return result;
}



// function view nota
void nota(string data, bool discount) {
	string buffer, subdata;
	int total = 0;
	int i = 0;
	int num = 1;
	stringstream ss_data(data);

	// clearing screen, view banner
	clr_screen();
	cout << banner << endl;

	// calc total and view list orders
	while(getline(ss_data, subdata, ' ')) {
		if ((i+1)%2 == 0) {
			total+=string_to_int(subdata);
			cout << integer_formater(subdata) << endl;
		} else {
			// replace unique string to space
			while (true) {
				if (str_in_str(subdata, "_-_")) {
					subdata.replace(subdata.find("_-_"), 3, " ");
				} else {
					break;
				}
			}
			// view menu order
			cout << num << ". " << subdata << " ";
			num++;
		}
		i++;
	}

	// use discount if true
	if (discount) {
		total = total-(total*0.1);
	}

	cout << "--------------------------------" << endl;
	cout << "Total\t: " << total << endl;

	// View discount description
	if (discount) {
		cout << "Total sudah dengan diskon sebesar 10%" << endl;
	}

	cout << "\n[Press Enter to Continue]";
	getline(cin, buffer);
}


string get_item(int choice, string type_menu) {
	ifstream menu;
	string buffer;
	int i = 0;

	// read db menu
	if (type_menu == "foods") {
		menu.open("db/foods.txt");
	} else if (type_menu == "drinks") {
		menu.open("db/drinks.txt");
	}

	while(!menu.eof()) {
		i++;
		getline(menu, buffer);
		if (i == choice) {
			return buffer;
		}
	}
	return buffer;
}

void karyawan() {
	string choice, buffer, take_it_home, voucher_code;
	int total, total_menu, choice_int;
	int i = 1;
	int count_table = 5;
	string orders = "";
	string table = "ABC";

	// select menu foods
	total_menu = view_menu("foods");

	while (true) {
		cout << "Pilih : ";
		getline(cin, choice);
		choice_int = string_to_int(choice);
		if ((choice_int <= total_menu) and (choice_int > 0)) {
			buffer = get_item(choice_int, "foods");
			orders+=buffer+" ";
			cout << "Ingin memesan makanan lagi? (y/n) : ";
			getline(cin, buffer);
			if ((buffer == "y") | buffer == "Y") {
				total_menu = view_menu("foods");
				continue;
			}
			break;
		} else if (choice_int == 0) {
			break;
		}
		cout << "Mohon pilih makanan berdasarkan angka yang tersedia" << endl;
	}

	// select menu drinks
	total_menu = view_menu("drinks");

	while (true) {
		cout << "Pilih : ";
		getline(cin, choice);
		choice_int = string_to_int(choice);
		if ((choice_int <= total_menu) and (choice_int > 0)) {
			buffer = get_item(choice_int, "drinks");
			orders+=buffer+" ";
			cout << "Ingin memesan makanan lagi? (y/n) : ";
			getline(cin, buffer);
			if ((buffer == "y") | buffer == "Y") {
				total_menu = view_menu("drinks");
				continue;
			}
			break;
		} else if (choice_int == 0) {
			break;
		}
		cout << "Mohon pilih makanan berdasarkan angka yang tersedia" << endl;
	}

	cout << "Bawa pulang? (y/n) : ";
	getline(cin, take_it_home);
	if ((take_it_home == "y") | take_it_home == "Y") {
		// statmen if customer will take it home
		cout << "Masukkan kode voucher untuk mendapatkan diskon 10%\n(langsung enter jika tidak ada voucher) : ";
		getline(cin, voucher_code);
		if (voucher_code == "MAKANDIRUMAH") {
			nota(orders, true);
		} else {
			nota(orders, false);
		}
	} else {
		clr_screen();
		cout << banner << endl;
		cout << "Pilih meja :" << endl;
		for (int i = 1; i <= count_table; ++i) {
			for (int j = 0; j < table.length(); ++j) {
				cout << i << table[j] << "\t";
			}
			cout << endl;
		}
		cout << endl;

		while (true){
			cout << "Pilih :";
			getline(cin , choice);

			// checking invalid input
			buffer = "invalid";
			for (int i = 1; i <= count_table; ++i) {
				for (int j = 0; j < table.length(); ++j) {
					if ((int_to_string(i)+table[j]) == choice) {
						buffer = "valid";
						break;
					}
				}
			}
			if (buffer == "invalid") {
				cout << "Mohon pilih meja dengan benar!" << endl;
				continue;
			}

			break;
		}
		nota(orders, false);
	}
}


int main() {
	// declarate variable
	string username, password, x;
	while (true) {
		clr_screen();
		cout << banner << endl;

		// Login input
		cout << "Login" << endl;
		cout << "Username : ";
		getline(cin, username);
		cout << "Password : ";
		getline(cin, password);

		if (str_in_str(username, " ")) {
			username.replace(username.find(" "), 1, "_-_");
		}
		if (str_in_str(password, " ")) {
			password.replace(password.find(" "), 1, "_-_");
		}

		// Check if login as admin
		if (login(username, password) == "admin") {
			admin();
			break;
		} else if (login(username, password) == "karyawan") { // Check if login as karyawan
			cout << "Anda login sebagai karyawan" << endl;
			karyawan();
			break;
		} else { // statment for wrong username or password
			cout << "Wrong username or password" << endl;
			cout << "ingin login ulang? (y/n) : ";
			getline(cin, x);
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