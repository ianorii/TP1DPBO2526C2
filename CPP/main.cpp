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

string inputNumber(string message, int type) {
    string input;

    cout << message;
    getline(cin, input);
    
    if(!type) {
        while(!isInteger(input)) {
            cout << "inputan cuma boleh bilangan bulat yeah\n";
            cout << message;
            getline(cin, input);
        }
    } else {
        while(!isFloat(input)) {
            cout << "ini bukan bilangan real woy\n";
            cout << message;
            getline(cin, input);
        }
    }

    return input;
}

string inputString(string message) {
    string ans;
    cout << message;
    getline(cin, ans);
    return ans;
}

void insert() {
    cout << "---------------Masukan Data Bioskop---------------\n";
    
    int id = stoi(inputNumber("Masukan ID : ", 1));
    while(searchId(id)) {
        cout << "ID sudah ada\n";
        id = stoi(inputNumber("Masukan ID : ", 1));
    }
    string name = inputString("Masukan Nama Bioskop : ");
    string address = inputString("Masukan Alamat Bioskop : ");
    int totalStudios = stoi(inputNumber("Masukan Jumlah Studio : ", 0));    
    float rating = stof(inputNumber("Masukan Rating Bioskop : ", 1));

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

string updateNumber(string message, auto base, int type) {
    string str;

    cout << message;
    getline(cin, str);
    if(str.empty()) return to_string(base);
    
    if(!type) {
        while(!isInteger(str)) {
            cout << "masukin bilangan bulat yeah\n";
            cout << message;
            getline(cin, str);
            if(str.empty()) return to_string(base);
        }
    } else {
        while(!isFloat(str)) {
            cout << "ini bukan float\n";
            cout << message;
            getline(cin, str);
            if(str.empty()) return to_string(base);
        }
    }

    return str;
}

void update() {
    cout << "---------------Update Data Bioskop---------------\n";
    int id = stoi(inputNumber("Masukan ID : ", 0));
    
    int i = 0;
    for(auto data: dataBioskop) {
        if(data.getId() == id) {
            string str1 = "Masukan ID baru [" + to_string(data.getId()) + "] : ";
            id = stoi(updateNumber(str1, data.getId(), 0));
            while(id != data.getId() && searchId(id)) {
                cout << "ID udah ada\n";
                id = stoi(updateNumber(str1, data.getId(), 0));
            }
            
            string str2 = "Masukan Nama baru [" + data.getName()+ "] : "; string name = inputString(str2);
            string str3 = "Masukan Alamat baru [" + data.getAddress() + "] : "; string address = inputString(str3);

            string str4 = "Masukan Jumlah Studio [" + to_string(data.getTotalStudios()) + "] : ";
            int totalStudios = stoi(updateNumber(str4, data.getTotalStudios(), 0));
            
            string str5 = "Masukan Rating Bioskop [" + to_string(data.getRating()) + "] : ";
            float rating = stof(updateNumber(str5, data.getRating(), 1));

            dataBioskop[i].setId(id);
            dataBioskop[i].setName(name.empty() ? data.getName() : name);
            dataBioskop[i].setAddress(address.empty() ? data.getAddress() : address);
            dataBioskop[i].setTotalStudios(totalStudios);
            dataBioskop[i].setRating(rating);

            return;
        }
        i++;
    }

    cout << "ID tidak ditemukan\n";
}

void del() {
    cout << "---------------Hapus Data Bioskop---------------\n";
    int id = stoi(inputNumber("Masukan ID Bioskop : ", 0));

    int i = 0;
    for(auto data: dataBioskop) {
        if(data.getId() == id) {
            dataBioskop.erase(dataBioskop.begin() + i);
            return;
        }
        else i++;
    }

    cout << "ID Bioskop tidak ditemukan\n";
}

void searchData() {
    int id = stoi(inputNumber("Masukan ID Bioskop : ", 0));
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
                update();
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