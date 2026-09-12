#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
#include "Bioskop.cpp"

// definisi warna untuk output terminal
#define RESET               "\033[0m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define CYAN                "\033[36m"
#define YELLOW              "\033[33m"
#define BOLD                "\033[1m"

using namespace std;
vector<Bioskop> dataBioskop; // menyimpan data bioskop
int col[5]; // lebar kolom untuk tabel

// menginisialisasi lebar kolom berdasarkan panjang header
void initCol() {
    col[0] = string("ID").length();
    col[1] = string("Nama Bioskop").length();
    col[2] = string("Alamat").length();
    col[3] = string("Total Studio").length();
    col[4] = string("Rating").length();
}

// menampilkan judul program dan daftar menu
void intro() {
    cout << BOLD CYAN;
    cout << "+====================================================+\n";
    cout << "|           SISTEM MANAJEMEN DATA BIOSKOP            |\n";
    cout << "+====================================================+\n";
    cout << RESET;
    cout << BOLD << "  Daftar Menu :\n" << RESET;
    cout << CYAN "  [1]" RESET " Insert Data Bioskop\n";
    cout << CYAN "  [2]" RESET " Tampilkan Semua Data\n";
    cout << CYAN "  [3]" RESET " Update Data Bioskop\n";
    cout << CYAN "  [4]" RESET " Hapus Data Bioskop\n";
    cout << CYAN "  [5]" RESET " Cari Data Bioskop\n";
    cout << CYAN "  [6]" RESET " Keluar\n";
    cout << BOLD CYAN;
    cout << "+====================================================+\n";
    cout << RESET << endl;
}

// fungsi memeriksa apakah ID sudah ada
bool searchId(int target) {
    for(auto data : dataBioskop) {
        if(data.getId() == target) {
            // jika id sudah ada
            return true;
        }
    }
    // mengembalikan false jika id belum ada
    return false;
}

// memvalidasi apakah string merupakan bilangan bulat
bool isInteger(string s) {
    // Cek apakah string hanya berisi angka (opsional tanda minus)
    if(s.empty()) return false;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

// memvalidasi apakah string merupakan bilangan desimal
bool isFloat(string s) {
    // mengembalikan false ketika string kosong atau ada simbol di index 0
    if(s.empty()) return false;
    if(s[0] == '.' || s[0] == '-') return false;

    int flag = 0;
    for(int i = 0; i < s.length(); i++) {
        if((s[i] < '0' || s[i] > '9') && s[i] != '.') return false;
        if(s[i] == '.' && flag > 0) {
            if(flag > 0) return false;
            else flag++;
        }
    }
    return true;
}

// menerima input angka dari user dengan validasi tipe (0=bulat, 1=desimal)
string inputNumber(string message, int type) {
    string input;

    cout << message;
    getline(cin, input);
    
    if(!type) {
        // type 0 atau bilangan bulat
        while(!isInteger(input)) {
            cout << RED "  Input harus berupa bilangan bulat.\n" RESET;
            cout << message;
            getline(cin, input);
        }
    } else {
        // type 1 atau bilangan desimal
        while(!isFloat(input)) {
            cout << RED "  Input harus berupa bilangan desimal.\n" RESET;
            cout << message;
            getline(cin, input);
        }
    }

    return input;
}

// menerima input teks dari user
string inputString(string message) {
    string ans;
    cout << message;
    getline(cin, ans);
    return ans;
}

// menambahkan data bioskop baru ke dalam vector
void insert() {
    cout << BOLD CYAN "\n=============== Masukan Data Bioskop ===============\n" << RESET << endl;

    int id = stoi(inputNumber("  Masukan ID : ", 1));
    // loop error handling jika data ID sudah digunakan
    while(searchId(id)) {
        cout << RED "  ID sudah terpakai, gunakan ID lain\n" RESET;
        id = stoi(inputNumber("  Masukan ID : ", 1));
    }

    // input data lainnya
    string name = inputString("  Masukan Nama Bioskop : ");
    string address = inputString("  Masukan Alamat Bioskop : ");
    int totalStudios = stoi(inputNumber("  Masukan Jumlah Studio : ", 0));    
    float rating = stof(inputNumber("  Masukan Rating Bioskop : ", 1));

    // cek ukuran tiap kolom untuk tabel
    if(col[0] < log10(id)+1) col[0] = log10(id)+1;
    if(col[1] < name.length()) col[1] = name.length();
    if(col[2] < address.length()) col[2] = address.length();
    if(col[3] < log10(totalStudios)+1) col[3] = log10(totalStudios)+1;
    
    // instansiasi data
    Bioskop now = Bioskop(id, name, address, totalStudios, rating);
    dataBioskop.push_back(now);
    cout << GREEN "\n  Data Bioskop berhasil ditambahkan!\n" << RESET << endl;
}

// mencetak garis pembatas tabel
void separator() {
    cout << "+-"; for(int i = 0; i < col[0]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[1]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[2]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[3]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[4]; i++) cout << "-";
    cout << "-+" << endl;
}

// mencetak satu baris data dalam tabel
void row(string col1, string col2, string col3, string col4, string col5) {
    cout << "| "; cout << col1; for(int i = 0; i < col[0]-col1.length(); i++) cout << " "; 
    cout << " | "; cout << col2; for(int i = 0; i < col[1]-col2.length(); i++) cout << " ";
    cout << " | "; cout << col3; for(int i = 0; i < col[2]-col3.length(); i++) cout << " ";
    cout << " | "; cout << col4; for(int i = 0; i < col[3]-col4.length(); i++) cout << " ";
    cout << " | "; cout << col5; for(int i = 0; i < col[4]-col5.length(); i++) cout << " ";
    cout << " |" << endl;
}

// menampilkan seluruh data bioskop dalam bentuk tabel
void show() {
    cout << BOLD CYAN "\n=============== Data Bioskop ===============\n" << RESET << endl;

    if(dataBioskop.empty()) {
        cout << YELLOW "  Belum ada data yang tersimpan.\n" << RESET << endl;
        return;
    }

    // print header
    separator();
    row("ID", "Nama Bioskop", "Alamat", "Total Studio", "Rating");
    separator();

    // print row
    for(auto data : dataBioskop) {
        stringstream rate;
        rate << fixed << setprecision(2) << data.getRating();
        row(to_string(data.getId()), data.getName(), data.getAddress(), to_string(data.getTotalStudios()), rate.str());
    }
    separator();
    cout << endl;
}

// menerima input angka untuk update, mengembalikan nilai lama jika input kosong
string updateNumber(string message, auto base, int type) {
    string str;

    cout << message;
    getline(cin, str);
    if(str.empty()) return to_string(base); // return string kosong
    
    if(!type) {
        // type 0 atau bilangan bulat
        while(!isInteger(str)) {    // loop error handling jika nilai input tidak sesuai 
            cout << RED "  Input harus berupa bilangan bulat.\n" RESET;
            cout << message;
            getline(cin, str);
            if(str.empty()) return to_string(base);
        }
    } else {
        // type 1 atau bilangan desimal
        while(!isFloat(str)) {  // loop error handling jika nilai input tidak sesuai 
            cout << RED "  Input harus berupa bilangan desimal.\n" RESET;
            cout << message;
            getline(cin, str);
            if(str.empty()) return to_string(base);
        }
    }

    return str;
}

// memperbarui data bioskop berdasarkan ID
void update() {
    cout << BOLD CYAN "\n=============== Update Data Bioskop ===============\n" << RESET << endl;
    int id = stoi(inputNumber("  Masukan ID : ", 0));
    
    // loop mencari data berdasarkan ID
    int i = 0;
    for(auto data: dataBioskop) {
        if(data.getId() == id) {    // jika data ditemukan
            // input ID baru
            string str1 = "  Masukan ID baru [" + to_string(data.getId()) + "] : ";
            id = stoi(updateNumber(str1, data.getId(), 0));

            // loop error handling jika ID baru sudah digunakan
            while(id != data.getId() && searchId(id)) {
                cout << RED "  ID sudah terpakai, gunakan ID lain\n" RESET;
                id = stoi(updateNumber(str1, data.getId(), 0));
            }

            // input nama dan alamat baru
            string str2 = "  Masukan Nama baru [" + data.getName()+ "] : "; string name = inputString(str2);
            string str3 = "  Masukan Alamat baru [" + data.getAddress() + "] : "; string address = inputString(str3);

            // input jumlah studio
            string str4 = "  Masukan Jumlah Studio [" + to_string(data.getTotalStudios()) + "] : ";
            int totalStudios = stoi(updateNumber(str4, data.getTotalStudios(), 0));
            
            // input rating
            string str5 = "  Masukan Rating Bioskop [" + to_string(data.getRating()) + "] : ";
            float rating = stof(updateNumber(str5, data.getRating(), 1));

            // update object
            dataBioskop[i].setId(id);
            dataBioskop[i].setName(name.empty() ? data.getName() : name);
            dataBioskop[i].setAddress(address.empty() ? data.getAddress() : address);
            dataBioskop[i].setTotalStudios(totalStudios);
            dataBioskop[i].setRating(rating);

            cout << GREEN "\n  Data Bioskop berhasil diupdate!\n" << RESET << endl;
            return;
        }
        i++;
    }

    // keitka ID tidak ditemukan
    cout << RED "\n  ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" << RESET << endl;
}

// menghapus data bioskop berdasarkan ID
void del() {
    cout << BOLD CYAN "\n=============== Hapus Data Bioskop ===============\n" << RESET << endl;
    int id = stoi(inputNumber("  Masukan ID Bioskop : ", 0));

    // loop mencari daa berdasarkan ID
    int i = 0;
    for(auto data: dataBioskop) {
        if(data.getId() == id) {    // jika data ditemukan
            dataBioskop.erase(dataBioskop.begin() + i);
            cout << GREEN "\n  Data Bioskop berhasil dihapus!\n" << RESET << endl;
            return;
        }
        else i++;
    }

    // ketika ID tidak ditemukan
    cout << RED "\n  ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" << RESET << endl;
}

// mencari dan menampilkan data bioskop berdasarkan ID
void searchData() {
    cout << BOLD CYAN "\n=============== Cari Data Bioskop ===============\n" << RESET << endl;
    int id = stoi(inputNumber("  Masukan ID Bioskop : ", 0));   // input ID

    // loop mencari data berdasarkan ID
    for(auto data : dataBioskop) {
        if(data.getId() == id) {    // jika data ditemukan
            cout << GREEN "  Data ditemukan!\n" << RESET << endl;
            separator();
            row("ID", "Nama Bioskop", "Alamat", "Total Studio", "Rating");
            separator();
            stringstream rate;
            rate << fixed << setprecision(2) << data.getRating();
            row(to_string(data.getId()), data.getName(), data.getAddress(), to_string(data.getTotalStudios()), rate.str());
            separator();
            cout << endl;
            return;
        }
    }
    // ketika ID tidak ditemukan
    cout << RED "\n  ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" << RESET << endl;
}

// program utama
int main() {
    initCol();
    intro();

    int exit = 0;
    while(!exit) { // loop utama program
        cout << BOLD "  Pilih opsi [1-6] >> " << RESET;
        int option;
        cin >> option;
        cin.ignore(); // membersihkan buffer input

        switch(option) { // menjalankan operasi sesuai pilihan user
            case 1:
                insert();
                break;
            case 2:
                show();
                break;
            case 3:
                update();
                break;
            case 4:
                del();
                break;
            case 5:
                searchData();
                break;
            case 6:
                cout << GREEN "\n  Sampai jumpa! Terima kasih telah menggunakan program ini.\n\n" << RESET;
                exit = 1;
                break;
            default:
                cout << RED "\n  Opsi tidak valid, silakan pilih antara 1 sampai 6.\n" << RESET << endl;
        }
    }

    return 0;
}