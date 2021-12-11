// meng include beberapa standar library yang di perlukan

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
// deklarasikan variabel banner
string banner = "\tRESTO APP V1.0.0\n";


// Function untuk clear terminal
void clr_screen() {
	// menggunakan system("cls") jika sistem oprasi nya windows
	#ifdef _WIN32
		system("cls");
	// menggunakan system("clear") jika sistem oprasi nya selain windows
	#else
	    system("clear");
	#endif
}


// function untuk mengecek apakah sub string terdapat di dalam string
// jika sub string terdapat dalam string return true, jika tidak return false
bool str_in_str(string str1, string str2) {
	if (str1.find(str2) != string::npos) {
		return true;
	} else {
		return false;
	}
	return false;
}

/*
function untuk mengecek tipe akun yand di gunakan untuk login
return admin jika akun terdapat pada database admin.txt
return karyawan jika akun terdapat pada database karywan.txt
return wrong jika akun tidak terdaftar atau password salah
*/
string login(string username, string password) {
	// deklarasi variable admin, karyawan yang bertipe data ifstream
	ifstream admin, karyawan;
	// deklarasi variable data untuk menampun setiap data username, dan password
	string data;
	// deklarasi variabel i yang bertipe data integer 0
	int i = 0;

	// Blok kode untuk mengecek database admin.txt, jika akun di temukan langsung di return
	admin.open("db/admin.txt");
	// melakukan looping untuk membaca setiap baris data dan spasi
	while(!admin.eof()) {
		i++;
		admin >> data;
		// jika jumlah loopingan modulus 2 = 0 maka cek username
		if ((i%2) != 0) {
			if (username == data) {
				admin >> data;
				// jika userame di temukan, cek passwordnya, jika salah return wrong
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
	// menutup objek admin, karena sebelumnya telah membuka file admin.txt
	admin.close();

	// reset nilai i dengan 0
	i = 0;
	// Blok kode untuk mengecek database admin.txt, jika akun di temukan langsung di return
	// logika nya sama seperti pada pengecekan akun admin
	// hanya saja jika akun telah di temukan di database admin kode di bawah ini tidak di eksekusi
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
	// menutup objek karyawan, karena sebelumnya telah membuka file admin.txt
	karyawan.close();
	// return wrong jika akun sama sekali tidak di temukan
	return "wrong";
}


// Function untuk mengecek apakah akun telah terdaftar
// return true jika telah terdaftar, return flase jika belum terdaftar
bool check_already_account(string username, string type_account) {
	// deklarasi variable admin, karyawan yang bertipe data ifstream
	ifstream admin, karyawan;
	// deklarasi variable data untuk menampun setiap data username
	string data;

	// Kode dalam if (type_account == "admin") sama seperti mengecek tipe akun yang login
	// hanya saja tidak mengecek passwordnya (yang di cek hanya uername)
	if (type_account == "admin") {
		// jalankan statment ini jika tipe akun yang ingin di cek adalah admin
		int i = 0;
		// buka file admin.txt
		admin.open("db/admin.txt");
		while(!admin.eof()) {
			i++;
			admin >> data;
			// selalu cek username jika jumlah loopingan modulus 2 = 0
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
		// jalankan statment ini jika tipe akun yang ingin di cek adalah karyawan
		// logika nya sama seperti saat mengecek akun admin hanya saja file yg di baca adalah karyawan.txt
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


// function tanpa return untuk menambahkan akun admin
void add_admin_account() {
	// deklarasi variable admin dan adminsave
	ifstream admin;
	ofstream adminsave;
	// deklarasi variable dengan tipe data sting
	string username, password, add_again, buffer, data;

	clr_screen();
	cout << banner << endl;
	// meminta inputan apakah ingin lanjut menambahkan akun
	// y untuk lanjut, n untuk kembali ke menu admin
	cout << "Lanjut menambahkan akun? (y/n) : ";
	getline(cin, buffer);
	if ((buffer == "y") | (buffer == "Y")) {

	} else {
		return;
	}

	// melakukan while loop dengan kondisi selalu true agar bisa menambahkan akun lagi
	while (true) {
		// memanggil function clear screen
		clr_screen();
		// menampilkan banner dan beberapa teks
		cout << banner << endl;
		cout << "Tambah akun admin" << endl;

		// melakukan while loop agar jika username yg di inputkan telah terdaftar, pengguna bisa memasukkan ulang username nya
		while (true) {
			cout << "Username : ";
			getline(cin, username);

			// kode untuk me replace spasi dengan _-_
			if (str_in_str(username, " ")) {
				username.replace(username.find(" "), 1, "_-_");
			}

			// membuat percabangan dengan kondisi sesuai return atau nilai kembalian dari fungsi check_already_account
			if (check_already_account(username, "admin")) {
				// menjalankan statment ini jika username terlah terdaftar
				cout << "Akun "<< username <<" telah terdaftar sebelumnya!" << endl;
				cout << "Gunakan username lain untuk menambahkan akun baru" << endl;
			} else { // hentikan while loop jika username belum terdaftar, agar bisa menginpukan password
				break;
			}
		}

		// meminta pengguna untuk memasukkan password
		cout << "Password : ";
		getline(cin, password);

		// kode untuk me replace spasi dengan _-_
		if (str_in_str(password, " ")) {
			password.replace(password.find(" "), 1, "_-_");
		}


		// membaca seluruh data pada file admin.txt dan menyimpannya pada variable data
		admin.open("db/admin.txt");
		while(!admin.eof()) {
			getline(admin, buffer);
			data+=buffer+"\n";
		}
		admin.close();
		// menambahkan username dan password baru pada variable data
		data+=username+" "+password;
		// menyimpan nilai variable data pada file admin.txt
		adminsave.open("db/admin.txt");
		adminsave << data;
		adminsave.close();

		// menampilkan info bahwa akun berhasil di tambahkan
		cout << "Akun berhasil di tambahkan" << endl;
		// meminta user untuk menginputkan y jika ingin menambahkan lagi
		// atau input selain y jika tidak ingin menambahkan lagi/kembali ke menu admin
		cout << "Apakah ingin menambahkan akun lagi? (y) : ";
		getline(cin, add_again);
		if ((add_again == "y") | (add_again == "Y")) {

		} else {
			break;
		}
	}
}


// fungsi tanpa return untuk mengubah password
void change_paswd(string type_account) {
	// deklarasi variabel
	// ifstream untuk variable yang dapat membaca data
	// ofstream untuk variable yg dapat menulis data
	int i;
	string result = "";
	string path, data, username, password, change_again, buffer;
	ifstream file, karyawan;
	ofstream savefile, karyawansave;

	clr_screen();
	cout << banner << endl;
	// meminta inputan apakah ingin lanjut mengubah password
	// y untuk lanjut, n untuk kembali ke menu admin
	cout << "Lanjut mengubah password? (y/n) : ";
	getline(cin, buffer);
	if ((buffer == "y") | (buffer == "Y")) {

	} else {
		return;
	}


	// memanggil fungsi clear screen dan meampilkan banner
	clr_screen();
	cout << banner << endl;


	// mengecek akun tipe yang ingin di ubah passwordnya
	// variable path akan bernilai db/admin.txt jika akun admin
	// dan akan bernilai db/karyawan.txt jika akun karyawan
	if (type_account == "admin") {
		path = "db/admin.txt";
	} else if (type_account == "karyawan") {
		path = "db/karyawan.txt";
	}

	// kode untuk menampilkan list username yang telah terdaftar
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

	// membuat while loop dengan kondisi true agar pengguna dapat memasukkan userame ulang jika yang di inputkan salah
	cout << "\n";
	while (true) {
		cout << "Masukkan username : ";
		getline(cin, username);
		// replace spasi dengan _-_
		if (str_in_str(username, " ")) {
			username.replace(username.find(" "), 1, "_-_");
		}
		i = 0;
		// mengecek apakah username akun terdaftar
		if (check_already_account(username, type_account)) {
			// jika akun telah terdaftar minta pengguna memamsukkan password baru
			cout << "Masukkan password baru : ";
			getline(cin, password);

			// replace spasi dengan _-_
			if (str_in_str(password, " ")) {
				password.replace(password.find(" "), 1, "_-_");
			}

			// replace _-_ dengan spasi
			if (str_in_str(username, "_-_")) {
				username.replace(username.find("_-_"), 3, " ");
			}
			// membaca database akun dan skip data ketika userame nya di temukan (menghapus akun)
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
			// menambahkan usernam yang tadi terdaftar dan menggunakan password baru
			result+=username+" "+password;

			// menyimpan data
			savefile.open(path);
			savefile << result;
			savefile.close();

			// memnampilkan bahwa password berhasil di update
			cout << "Password berhasil di update" << endl;
			cout << "Apakah ingin mengubah password lagi? (y) : ";
			// meminta user menginpitkan y jika ingin mengubah password akun lagi
			// input selain y jika ingin kembali ke menu utama
			getline(cin, change_again);
			if ((change_again == "y") | (change_again == "Y")) {
				// panggil fungsi clear screen dan tampilkan bannner
				clr_screen();
				cout << banner << endl;
				i = 0;
				// menampilkan list username yang terdaftar
				// kode ini logika nya sama seperi kode di awal fungsi ini
				cout << "Daftar username "<< type_account <<" :" << endl;
				file.open(path);
				while(!file.eof()) {
					i++;
					file >> data;
					if ((i%2) != 0) {
						// replace spasi dengan _-_
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


// fungsi untuk menambahkan akun karyawan
void add_karyawan_account() {
	// deklarasikan variabel
	ifstream karyawan, bio_karyawan;
	ofstream karyawansave, bio_karyawansave;
	string username, password, add_again, buffer, data, name, address, birth_date_place, salary, data_bio_karyawan;
	int i;

	clr_screen();
	cout << banner << endl;
	// meminta inputan apakah ingin lanjut menambahkan akun
	// y untuk lanjut, n untuk kembali ke menu admin
	cout << "Lanjut menambahkan akun? (y/n) : ";
	getline(cin, buffer);
	if ((buffer == "y") | (buffer == "Y")) {

	} else {
		return;
	}

	// melakukan while loop agar bisa menambahkan akun lagi
	while (true) {
		// memanggil fungsi clear screen dan menampilkan banner
		clr_screen();
		cout << banner << endl;
		cout << "Tambah akun karyawan" << endl;

		// always check username if already regristed
		while (true) {
			// meminta untuk menginputkan username
			cout << "Username : ";
			getline(cin, username);
			// replace spasi dengan _-_
			if (str_in_str(username, " ")) {
				username.replace(username.find(" "), 1, "_-_");
			}

			// jika username telah terdaftar minta untuk memasukkan username lain
			if (check_already_account(username, "karyawan")) {
				cout << "Akun "<< username << "telah terdaftar sebelumnya!" << endl;
				cout << "Gunakan username lain untuk menambahkan akun baru" << endl;
			} else { // jika tidak break loopingan
				break;
			}
		}

		// meminta user untuk menginputkan passowrd
		cout << "Password : ";
		getline(cin, password);
		// replace spasi dengan _-_
		if (str_in_str(password, " ")) {
			password.replace(password.find(" "), 1, "_-_");
		}

		// membaca data karyawan.txt dan menyimpannya pada variable data
		karyawan.open("db/karyawan.txt");
		while(!karyawan.eof()) {
			getline(karyawan, buffer);
			data+=buffer+"\n";
		}
		karyawan.close();
		// menambahkan username, password baru
		data+=username+" "+password;
		// menyimpan data pada file karyawan.txt
		karyawansave.open("db/karyawan.txt");
		karyawansave << data;
		karyawansave.close();

		// memberi tahu jika akun berhasil di tambahkan
		cout << "Akun berhasil di tambahkan" << endl;
		// meminta user menginpitkan y jika ingin menambah akun lagi
		// input selain y jika ingin kembali ke menu utama
		cout << "Apakah ingin menambahkan akun lagi? (y) : ";
		getline(cin, add_again);
		if ((add_again == "y") | (add_again == "Y")) {

		} else {
			break;
		}
	}
}


// Fuction untuk membalikan urutan data string
string reverseStr(string data) {
	string result = "";
	for (int i=data.length()-1; i>=0; i--) {
		result+=data[i];
	}
	return result;
}


// fungsi untuk memformat angka pada data string (menambahkan titik (.) pada angka)
string integer_formater(string num) {
	string result = "";

	// memanggil fungsi reverseStr untuk membalikkan urutan variabl num
	num = reverseStr(num);

	// menambahkan . setiap looping 3 kali
	for (int i=1; i <= num.length(); ++i) {
		result+=num[i-1];
		if (((i%3) == 0) and (i < num.length())) {
			result+=".";
		}
	}

	// membalikkan string ke awal lagi
	result = reverseStr(result);

	// me return nilai variable result
	return result;
}


void delete_account(string type_account) {
	int i, num;
	string result = "";
	string path, username, data, buffer;
	ifstream file;
	ofstream savefile;

	clr_screen();
	cout << banner << endl;
	// meminta inputan apakah ingin lanjut menghapus akun
	// y untuk lanjut, n untuk kembali ke menu admin
	cout << "Lanjut menghapus akun? (y/n) : ";
	getline(cin, buffer);
	if ((buffer == "y") | (buffer == "Y")) {

	} else {
		return;
	}

	// memanggil fungsi clear screen dan meampilkan banner
	clr_screen();
	cout << banner << endl;


	// mengecek akun tipe yang ingin di ubah passwordnya
	// variable path akan bernilai db/admin.txt jika akun admin
	// dan akan bernilai db/karyawan.txt jika akun karyawan
	if (type_account == "admin") {
		path = "db/admin.txt";
	} else if (type_account == "karyawan") {
		path = "db/karyawan.txt";
	}

	// kode untuk menampilkan list username yang telah terdaftar
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

	// membuat while loop dengan kondisi true agar pengguna dapat memasukkan userame ulang jika yang di inputkan salah
	cout << "\n";
	while (true) {
		cout << "Masukkan username : ";
		getline(cin, username);
		// replace spasi dengan _-_
		if (str_in_str(username, " ")) {
			username.replace(username.find(" "), 1, "_-_");
		}
		// mengecek apakah username akun terdaftar
		if (check_already_account(username, type_account)) {
			// membaca database akun dan skip data ketika userame nya di temukan (menghapus akun)
			num = 1;
			file.open(path);
			while(!file.eof()) {
				num++;
				file >> data;
				if (username == data) {
					file >> data;
				} else {
					result+=data+" ";
					file >> data;
					result+=data;
					if (num < (i/2)) {
						result+="\n";
					}
				}
			}
			file.close();

			// menyimpan data
			savefile.open(path);
			savefile << result;
			savefile.close();

			// memnampilkan bahwa password berhasil di update
			cout << "Akun berhasil di hapus" << endl;
			cout << "Apakah ingin menghapus lagi? (y) : ";
			// meminta user menginputkan y jika ingin mengubah password akun lagi
			// input selain y jika ingin kembali ke menu utama
			getline(cin, buffer);
			if ((buffer == "y") | (buffer == "Y")) {
				// panggil fungsi clear screen dan tampilkan bannner
				clr_screen();
				cout << banner << endl;
				i = 0;
				// menampilkan list username yang terdaftar
				// kode ini logika nya sama seperi kode di awal fungsi ini
				cout << "Daftar username "<< type_account <<" :" << endl;
				file.open(path);
				while(!file.eof()) {
					i++;
					file >> data;
					if ((i%2) != 0) {
						// replace spasi dengan _-_
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


// fungsi untuk menampilkan menu admin
void admin_menu() {
	clr_screen();
	cout << banner << endl;
	cout << "Menu :" << endl;
	cout << "1. Tambah akun admin" << endl;
	cout << "2. Ubah password admin" << endl;
	cout << "3. Tambah akun karyawan" << endl;
	cout << "4. Ubah password karyawan" << endl;
	cout << "5. Hapus akun admin" << endl;
	cout << "6. Hapus akun karyawan" << endl;
	cout << "0. Keluar\n" << endl;
}

// fungsi yang akan di panggil jika login sebagai admin
void admin() {
	string choice;
	admin_menu();
	// melakukan while dengan kondisi true agar bisa memilih menu terus menerus
	while (true) {
		cout << "Pilih : ";
		getline(cin, choice);
		// membuat percabangan jika yang di pilih 0 maka break loopingan
		if (choice == "0"){
			break;
		} else if (choice == "1") {
			// jika yg di pilih 1 makan panggil fungsi add admin account, dan begitu juga seterusnya
			add_admin_account();
		} else if (choice == "2") {
			change_paswd("admin");
		} else if (choice == "3") {
			add_karyawan_account();
		} else if (choice == "4") {
			change_paswd("karyawan");
		} else if (choice == "5") {
			delete_account("admin");
		} else if (choice == "6") {
			delete_account("karyawan");
		} else {
			cout << "Mohon memilih sesuai menu" << endl;
			continue;
		}
		admin_menu();
	}
}


// menampilkan list menu makanan dan minuman, dan mereturn jumlah menu
int view_menu(string type_menu) {
	// delarasi variabel
	ifstream menu;
	string buffer;
	int num = 1;

	// panggil fungsi clear screen dan tampilkan banner
	clr_screen();
	cout << banner << endl;

	// membaca database foods atau drinks sesuai nilai dari variabel type_menu
	if (type_menu == "foods") {
		menu.open("db/foods.txt");
	} else if (type_menu == "drinks") {
		menu.open("db/drinks.txt");
	}

	// kode untuk menampulkan list menu berserta harga nya
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


// function untuk mengkonversi data string ke data integer
int string_to_int(string data) {
	int result = 0;
	result = stoi(data);
	return result;
}


// function untuk mengkonversi data integer ke string
string int_to_string (int data) {
	string result;
	stringstream ss;
	ss << data;
	ss >> result;
	return result;
}



// function untuk menampilkan nota atau tagihan
void nota(string data, bool discount) {
	string buffer, subdata;
	int total = 0;
	int i = 0;
	int num = 1;
	stringstream ss_data(data);

	// panggil fungsi clear_screen dan tampilkan banner
	clr_screen();
	cout << banner << endl;

	// kalkulasi total harga pesanan
	while(getline(ss_data, subdata, ' ')) {
		if ((i+1)%2 == 0) {
			total+=string_to_int(subdata);
			cout << integer_formater(subdata) << endl;
		} else {
			// replace _-_ ke spasi
			while (true) {
				if (str_in_str(subdata, "_-_")) {
					subdata.replace(subdata.find("_-_"), 3, " ");
				} else {
					break;
				}
			}
			// menampilkan list pesanan
			cout << num << ". " << subdata << " ";
			num++;
		}
		i++;
	}

	// menggunakan rumus diskon jika memasukkan kode voucher denga benar
	if (discount) {
		total = total-(total*0.1);
	}

	cout << "--------------------------------" << endl;
	// menampilkan nominal tagihan
	cout << "Total\t: " << total << endl;

	// menampilkan deskripsi diskon jika menggunakan diskon
	if (discount) {
		cout << "Total sudah dengan diskon sebesar 10%" << endl;
	}

	cout << "\n[Press Enter to Continue]";
	getline(cin, buffer);
}


// funvtion untuk menampilkan list order
void view_list_orders(string data) {
	int i = 1;
	int num = 1;
	string buffer;
	stringstream ss_data(data);

	// menampilkan list order
	while(getline(ss_data, buffer, ' ')) {
		if ((i%2) != 0) {
			// replace _-_ ke spasi
			while (true) {
				if (str_in_str(buffer, "_-_")) {
					buffer.replace(buffer.find("_-_"), 3, " ");
				} else {
					break;
				}
			}
			cout << num << ". " << buffer << endl;
			num++;
		}
		i++;
	}

}


// function untuk mendapatkan data makanan atau minuman beserta pilihan yang di inputkan
string get_item(int choice, string type_menu) {
	ifstream menu;
	string buffer;
	int i = 0;

	// membaca database foods jika ingin mendapatkan data makanan, dan drinks jika ingin mendapatkan data minuman
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

// fugnsi yang akan di panggil jika login sebagai karyawan
void karyawan() {
	// deklarasi variable
	string choice, buffer, take_it_home, voucher_code;
	int total, total_menu, choice_int;
	int i = 1;
	// deklarasi jumlah meja dan tipe meja
	int count_table = 5;
	string orders = "";
	string table = "ABC";

	// menampilkan list menu makann berserta menyimpan jumlah menu
	total_menu = view_menu("foods");
	cout << "\n-----------------------------\nMenu yang telah anda pilih :" << endl;
	view_list_orders(orders);

	// melakukan while dengan kondisi true agar bisa memesan lagi
	while (true) {
		// meminta untuk menginputkan nomor pesanan
		cout << "\nPilih : ";
		getline(cin, choice);
		choice_int = string_to_int(choice);
		// statmen yang berjajan jika inputan valid
		if ((choice_int <= total_menu) and (choice_int > 0)) {
			buffer = get_item(choice_int, "foods");
			orders+=buffer+" ";
			cout << "Ingin memesan makanan lagi? (y/n) : ";
			getline(cin, buffer);
			if ((buffer == "y") | buffer == "Y") {
				total_menu = view_menu("foods");
				cout << "\n-----------------------------\nMenu yang telah anda pilih :" << endl;
				view_list_orders(orders);
				continue;
			}
			break;
		} else if (choice_int == 0) {
			// break while loop jika yang di pilih 0
			break;
		}
		// tampilkan peringatan jika inputan tidak valid
		cout << "Mohon pilih makanan berdasarkan angka yang tersedia" << endl;
	}

	// logika kode di bawah ini sama seperti menu makanan yg di atas
	total_menu = view_menu("drinks");
	cout << "\n-----------------------------\nMenu yang telah anda pilih :" << endl;
	view_list_orders(orders);

	while (true) {
		cout << "\nPilih : ";
		getline(cin, choice);
		choice_int = string_to_int(choice);
		if ((choice_int <= total_menu) and (choice_int > 0)) {
			buffer = get_item(choice_int, "drinks");
			orders+=buffer+" ";
			cout << "Ingin memesan makanan lagi? (y/n) : ";
			getline(cin, buffer);
			if ((buffer == "y") | buffer == "Y") {
				total_menu = view_menu("drinks");
				cout << "\n-----------------------------\nMenu yang telah anda pilih :" << endl;
				view_list_orders(orders);
				continue;
			}
			break;
		} else if (choice_int == 0) {
			break;
		}
		cout << "Mohon pilih makanan berdasarkan angka yang tersedia" << endl;
	}


	// meminta user untuk menginputkan y jika ingin di bawa pulang
	// input selain y jika makan di sini
	cout << "Bawa pulang? (y/n) : ";
	getline(cin, take_it_home);
	if ((take_it_home == "y") | take_it_home == "Y") {
		// meminta user memasukkan kode voucher jika ingin makan di rumah
		cout << "Masukkan kode voucher untuk mendapatkan diskon 10%\n(langsung enter jika tidak ada voucher) : ";
		getline(cin, voucher_code);
		if (voucher_code == "MAKANDIRUMAH") {
			// tampilkan nota dengan diskon
			nota(orders, true);
		} else {
			// menampilkan nota tanpa diskon karena voucher salah
			nota(orders, false);
		}
	} else {
		// jika ingin makan di sini minta untuk pilih meja
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

			// kode untuk mengecek jika meja yang di pilih tidak tersedia
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
		// menampilkan nota tanpa diskon
		nota(orders, false);
	}
}


int main() {
	// deklarasi variabel bertipe data string
	string username, password, x;
	while (true) {
		clr_screen();
		cout << banner << endl;

		// meminta user untuk memasukkan username dan passwordnya
		cout << "Login" << endl;
		cout << "Username : ";
		getline(cin, username);
		cout << "Password : ";
		getline(cin, password);

		// replace spasi dengan _-_
		if (str_in_str(username, " ")) {
			username.replace(username.find(" "), 1, "_-_");
		}
		if (str_in_str(password, " ")) {
			password.replace(password.find(" "), 1, "_-_");
		}

		// mengecek jika akun yang login admin, jalankan fungsi admin
		if (login(username, password) == "admin") {
			admin();
		} else if (login(username, password) == "karyawan") { // Check if login as karyawan
			// mengecek jika akun yang login karyawan, jalankan fungsi karyawan
			cout << "Anda login sebagai karyawan" << endl;
			karyawan();
			break;
		} else { // jalankan kode ini jika password salah atau akun tidak terdaftar
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