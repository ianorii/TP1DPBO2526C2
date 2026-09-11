#include<iostream>
#include<string>
#include<vector>
#include "Bioskop.cpp"

using namespace std;
vector<Bioskop> dataBioskop;

void intro() {
    cout << "-----------------------BIOSKOP-----------------------\n";
}

bool searchId(int target) {
    int found = false;
    int i = 0;
    while(!found && i < dataBioskop.size()) {
        if(dataBioskop[i].getId() == target) found = true;
        else i++;
    }

    return found;
}

bool isInteger(string s) {
    // Cek apakah string hanya berisi angka (opsional tanda minus)
    if(s.empty()) return false;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

void insert() {
    cout << "---------------Masukan Data Bioskop---------------\n";
    
    // error handling ID
    string input;
    int id, flag;
    do {
        flag = 1;
        cout << "Masukan ID : ";
        getline(cin, input);
        while(!isInteger(input)) {
            cout << "inputan cuma boleh bilangan bulat yeah\n";
            cout << "Masukan ID : ";
            getline(cin, input);
        }
        id = stoi(input);
        
        if(id <= 0) {
            cout << "id harus lebih dari 0\n";
            flag = 0;
        } else if(searchId(id)) {
            cout << "udah ada id nya kocak\n";
            flag = 0;
        }
    } while(!flag);

    cout << "Masukan Nama Bioskop : ";
    string name; cin >> name;

    cout << "Masukan Alamat Bioskop : ";
    cin.ignore();   // hapus buffer \n
    string address; getline(cin, address);

    cout << "Masukan Jumlah Studio : ";
    int totalStudios; cin >> totalStudios;

    cout << "Masukan Rating Bioskop : ";
    float rating; cin >> rating;

    Bioskop now = Bioskop(id, name, address, totalStudios, rating);
    dataBioskop.push_back(now);
}

int main() {
    intro();

    while(true) {
        cout << "Pilih Opsi : " << endl;
        int option;
        cin >> option;
        cin.ignore();

        switch(option) {
            case 1:
                insert();
                cout << dataBioskop[0].getAddress() << endl;
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                cout << "pilih opsi yang sesuai" << endl;
        }
    }

    return 0;
}