#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include "Bioskop.cpp"

using namespace std;
vector<Bioskop> dataBioskop;
int col[5] = {0};

void intro() {
    cout << "-----------------------BIOSKOP-----------------------\n";
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

bool isInteger(string s) {
    // Cek apakah string hanya berisi angka (opsional tanda minus)
    if(s.empty()) return false;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

bool isFloat(string s) {
    if(s.empty()) return false;
    if(s[0] == '.' || s[0] == '-') return false;

    int flag = 0;
    for(int i = 0; i < s.length(); i++) {
        if((s[i] < '0' || s[i] > '9') && s[i] != '.') return false;
        if(s[i] == '.' && flag > 0) return false;
        else flag++;
    }
    return true;
}

int inputInteger(string message, int type) {
    string input;
    int flag;
    int ans;

    do {
        flag = 1;
        cout << message;
        getline(cin, input);
        while(!isInteger(input)) {
            cout << "inputan cuma boleh bilangan bulat yeah\n";
            cout << message;
            getline(cin, input);
        }
        
        ans = stoi(input);
        if(ans <= 0) {
            cout << "nilainya harus lebih dari 0\n";
            flag = 0;
        } else if(type == 1 && searchId(ans)) {
            cout << "udah ada id nya kocak\n";
            flag = 0;
        }
    } while(!flag);

    return ans;
}

float inputFloat(string message) {
    string input;
    float ans;
    int flag;

    do {
        flag = 1;
        cout << message;
        getline(cin, input);
        
        while(!isFloat(input)) {
            cout << "inputan tidak sesuai format\n";
            cout << message;
            getline(cin, input);
        }

        ans = stof(input);
    } while(!flag);

    return ans;
}

string inputString(string message) {
    string ans;
    cout << message;
    cin.ignore();
    getline(cin, ans);
    return ans;
}

void insert() {
    cout << "---------------Masukan Data Bioskop---------------\n";
    
    int id = inputInteger("Masukan ID : ", 1);
    string name = inputString("Masukan Nama Bioskop : ");
    string address = inputString("Masukan Alamat Bioskop : ");
    int totalStudios = inputInteger("Masukan Jumlah Studio : ", 0);    
    float rating = inputFloat("Masukan Rating Bioskop : ");

    Bioskop now = Bioskop(id, name, address, totalStudios, rating);
    dataBioskop.push_back(now);
}

void del() {
    cout << "---------------Hapus Data Bioskop---------------\n";
    int id = inputInteger("Masukan ID Bioskop : ", 0);

    int i = 0;
    for(auto data : dataBioskop) {
        if(data.getId() == id) {
            dataBioskop.erase(dataBioskop.begin() + i);
            return;
        }
        else i++;
    }

    cout << "ID Bioskop tidak ditemukan\n";
}

void show() {
}

int main() {
    intro();
    cout << col[0] << endl;

    while(true) {
        cout << "Pilih Opsi : " << endl;
        int option;
        cin >> option;
        cin.ignore();

        switch(option) {
            case 1:
                insert();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                del();
                break;
            case 5:
                break;
            default:
                cout << "pilih opsi yang sesuai" << endl;
        }
    }

    return 0;
}