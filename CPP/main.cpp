#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
#include "Bioskop.cpp"

using namespace std;
vector<Bioskop> dataBioskop;
int col[5];

void initCol() {
    col[0] = string("ID").length();
    col[1] = string("Nama Bioskop").length();
    col[2] = string("Alamat").length();
    col[3] = string("Total Studio").length();
    col[4] = string("Rating").length();
}

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
        if(s[i] == '.' && flag > 0) {
            if(flag > 0) return false;
            else flag++;
        }
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
        if(ans > 5.00 || ans < 0) {
            flag = 0;
            cout << "Rating hanya skala 0-5\n";
        }
    } while(!flag);

    return ans;
}

string inputString(string message) {
    string ans;
    cout << message;
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

    if(col[0] < log10(id)+1) col[0] = log10(id)+1;
    if(col[1] < name.length()) col[1] = name.length();
    if(col[2] < address.length()) col[2] = address.length();
    if(col[3] < log10(totalStudios)+1) col[3] = log10(totalStudios)+1;
    
    Bioskop now = Bioskop(id, name, address, totalStudios, rating);
    dataBioskop.push_back(now);
}

void separator() {
    cout << "+-"; for(int i = 0; i < col[0]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[1]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[2]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[3]; i++) cout << "-";
    cout << "-+-"; for(int i = 0; i < col[4]; i++) cout << "-";
    cout << "-+" << endl;
}

void row(string col1, string col2, string col3, string col4, string col5) {
    cout << "| "; cout << col1; for(int i = 0; i < col[0]-col1.length(); i++) cout << " "; 
    cout << " | "; cout << col2; for(int i = 0; i < col[1]-col2.length(); i++) cout << " ";
    cout << " | "; cout << col3; for(int i = 0; i < col[2]-col3.length(); i++) cout << " ";
    cout << " | "; cout << col4; for(int i = 0; i < col[3]-col4.length(); i++) cout << " ";
    cout << " | "; cout << col5; for(int i = 0; i < col[4]-col5.length(); i++) cout << " ";
    cout << " |" << endl;
}

void show() {
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

void searchData() {
    int id = inputInteger("Masukan ID Bioskop : ", 0);
    for(auto data : dataBioskop) {
        if(data.getId() == id) {
            separator();
            row("ID", "Nama Bioskop", "Alamat", "Total Studio", "Rating");
            separator();
            stringstream rate;
            rate << fixed << setprecision(2) << data.getRating();
            row(to_string(data.getId()), data.getName(), data.getAddress(), to_string(data.getTotalStudios()), rate.str());
            separator();
            return;
        }
    }
    cout << "data tidak ada\n";
}

int main() {
    initCol();
    intro();

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
                show();
                break;
            case 3:
                break;
            case 4:
                del();
                break;
            case 5:
                searchData();
                break;
            default:
                cout << "pilih opsi yang sesuai" << endl;
        }
    }

    return 0;
}