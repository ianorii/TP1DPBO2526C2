#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
#include<sstream>
#include "Film.cpp"

// definisi warna untuk output terminal
#define RESET               "\033[0m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define CYAN                "\033[36m"
#define YELLOW              "\033[33m"
#define BOLD                "\033[1m"

using namespace std;
vector<Film> dataFilm; // menyimpan data film
string headers[4] = {"ID", "Nama Film", "Durasi (menit)", "Rating"}; // header tabel
int col[4]; // lebar kolom untuk tabel

// menginisialisasi lebar kolom berdasarkan panjang header
void initCol() {
    for(int i = 0; i < 4; i++) col[i] = headers[i].length();
}

// menampilkan judul program dan daftar menu
void intro() {
    cout << BOLD CYAN;
    cout << "+====================================================+\n";
    cout << "|           SISTEM MANAJEMEN DATA FILM               |\n";
    cout << "+====================================================+\n";
    cout << RESET;
    cout << BOLD << "  Daftar Menu :\n" << RESET;
    cout << CYAN "  [1]" RESET " Insert Data Film\n";
    cout << CYAN "  [2]" RESET " Tampilkan Semua Data\n";
    cout << CYAN "  [3]" RESET " Update Data Film\n";
    cout << CYAN "  [4]" RESET " Hapus Data Film\n";
    cout << CYAN "  [5]" RESET " Cari Data Film\n";
    cout << CYAN "  [6]" RESET " Keluar\n";
    cout << BOLD CYAN "+====================================================+\n" << RESET << endl;
}

// mencari index data berdasarkan ID, mengembalikan -1 jika tidak ditemukan
int findIndex(int target) {
    for(int i = 0; i < dataFilm.size(); i++) {
        if(dataFilm[i].getId() == target) return i;
    }
    return -1;
}

// memvalidasi apakah string merupakan bilangan (bulat atau desimal)
bool isNumber(string s, bool isFloat = false) {
    if(s.empty()) return false;
    int dot = 0;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '.') { if(++dot > 1) return false; continue; }
        if(s[i] < '0' || s[i] > '9') return false;
    }
    if(!isFloat && dot > 0) return false;
    return true;
}

// menerima input angka dari user dengan validasi tipe (0=bulat, 1=desimal)
// defaultVal digunakan untuk fitur update (tekan enter = nilai lama)
string inputNumber(string message, int type = 0, string defaultVal = "") {
    string input;
    while(true) {
        cout << message;
        getline(cin, input);
        if(input.empty() && !defaultVal.empty()) return defaultVal;
        if(isNumber(input, type)) return input;
        cout << RED "  Input harus berupa bilangan " << (type ? "desimal" : "bulat") << ".\n" RESET;
    }
}

// menerima input teks dari user, defaultVal jika input kosong
string inputString(string message, string defaultVal = "") {
    string ans;
    cout << message;
    getline(cin, ans);
    return ans.empty() ? defaultVal : ans;
}

// memperbarui lebar kolom tabel berdasarkan data terbaru
void updateCol(int id, string nama, int durasi) {
    int len = (int)log10(id) + 1; if(col[0] < len) col[0] = len;
    if(col[1] < (int)nama.length()) col[1] = nama.length();
    len = (int)log10(durasi) + 1; if(col[2] < len) col[2] = len;
}

// mencetak garis pembatas tabel
void separator() {
    for(int i = 0; i < 4; i++) { cout << "+-"; for(int j = 0; j < col[i]; j++) cout << "-"; }
    cout << "-+" << endl;
}

// mencetak satu baris data dalam tabel
void row(string cols[]) {
    for(int i = 0; i < 4; i++) {
        cout << "| " << cols[i];
        for(int j = 0; j < col[i] - (int)cols[i].length(); j++) cout << " ";
    }
    cout << " |" << endl;
}

// mencetak satu data film dalam tabel (garis + baris data)
void printTable(Film &data) {
    stringstream rate;
    rate << fixed << setprecision(2) << data.getRating();
    string r[4] = {to_string(data.getId()), data.getNama(), to_string(data.getDurasi()), rate.str()};
    separator();
    row(r);
}

// menambahkan data film baru ke dalam vector
void insert() {
    cout << BOLD CYAN "\n=============== Masukan Data Film ===============\n" << RESET << endl;

    // input ID dengan validasi jika sudah ada
    int id;
    while(true) {
        id = stoi(inputNumber("  Masukan ID : "));
        if(findIndex(id) == -1) break;
        cout << RED "  ID sudah terpakai, gunakan ID lain\n" RESET;
    }

    // input data lainnya
    string nama = inputString("  Masukan Nama Film : ");
    int durasi = stoi(inputNumber("  Masukan Durasi (menit) : "));
    float rating = stof(inputNumber("  Masukan Rating Film : ", 1));

    // update lebar kolom dan tambahkan data
    updateCol(id, nama, durasi);
    dataFilm.push_back(Film(id, nama, durasi, rating));
    cout << GREEN "\n  Data Film berhasil ditambahkan!\n" << RESET << endl;
}

// menampilkan seluruh data film dalam bentuk tabel
void show() {
    cout << BOLD CYAN "\n=============== Data Film ===============\n" << RESET << endl;
    if(dataFilm.empty()) { cout << YELLOW "  Belum ada data yang tersimpan.\n" << RESET << endl; return; }

    separator();
    row(headers);
    for(auto &data : dataFilm) printTable(data);
    separator();
    cout << endl;
}

// memperbarui data film berdasarkan ID
// tekan enter pada input untuk mempertahankan nilai lama
void update() {
    cout << BOLD CYAN "\n=============== Update Data Film ===============\n" << RESET << endl;
    int id = stoi(inputNumber("  Masukan ID : "));
    int idx = findIndex(id);

    if(idx != -1) {
        Film &data = dataFilm[idx];

        // input ID baru dengan validasi
        id = stoi(inputNumber("  Masukan ID baru [" + to_string(data.getId()) + "] : ", 0, to_string(data.getId())));
        while(id != data.getId() && findIndex(id) != -1) {
            cout << RED "  ID sudah terpakai, gunakan ID lain\n" RESET;
            id = stoi(inputNumber("  Masukan ID baru [" + to_string(data.getId()) + "] : ", 0, to_string(data.getId())));
        }

        // input field lainnya (tekan enter = nilai lama)
        string nama = inputString("  Masukan Nama baru [" + data.getNama() + "] : ", data.getNama());
        int durasi = stoi(inputNumber("  Masukan Durasi baru [" + to_string(data.getDurasi()) + "] menit : ", 0, to_string(data.getDurasi())));
        float rating = stof(inputNumber("  Masukan Rating Film [" + to_string(data.getRating()) + "] : ", 1, to_string(data.getRating())));

        // update object
        data.setId(id);
        data.setNama(nama);
        data.setDurasi(durasi);
        data.setRating(rating);
        cout << GREEN "\n  Data Film berhasil diupdate!\n" << RESET << endl;
    } else {
        cout << RED "\n  ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" << RESET << endl;
    }
}

// menghapus data film berdasarkan ID
void del() {
    cout << BOLD CYAN "\n=============== Hapus Data Film ===============\n" << RESET << endl;
    int id = stoi(inputNumber("  Masukan ID Film : "));
    int idx = findIndex(id);

    if(idx != -1) {
        dataFilm.erase(dataFilm.begin() + idx);
        cout << GREEN "\n  Data Film berhasil dihapus!\n" << RESET << endl;
    } else {
        cout << RED "\n  ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" << RESET << endl;
    }
}

// mencari dan menampilkan data film berdasarkan ID
void searchData() {
    cout << BOLD CYAN "\n=============== Cari Data Film ===============\n" << RESET << endl;
    int id = stoi(inputNumber("  Masukan ID Film : "));
    int idx = findIndex(id);

    if(idx != -1) {
        cout << GREEN "  Data ditemukan!\n" << RESET << endl;
        separator(); row(headers); separator();
        printTable(dataFilm[idx]);
        separator();
        cout << endl;
    } else {
        cout << RED "\n  ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" << RESET << endl;
    }
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
            case 1: insert(); break;
            case 2: show(); break;
            case 3: update(); break;
            case 4: del(); break;
            case 5: searchData(); break;
            case 6:
                cout << GREEN "\n  Sampai jumpa! Terima kasih telah menggunakan program ini.\n\n" << RESET;
                exit = 1; break;
            default:
                cout << RED "\n  Opsi tidak valid, silakan pilih antara 1 sampai 6.\n" << RESET << endl;
        }
    }
    return 0;
}
