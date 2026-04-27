#ifndef TOKOBAJU_H
#define TOKOBAJU_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

using namespace std;

struct DetailProduk {
    long long harga;
    int stok;
};

struct Produk {
    string nama;
    DetailProduk detail; 
};

struct User {
    string username;
    string password;
    string role;
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseLayar() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int getValidInt() {
    int input;
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Input tidak valid! Harus berupa angka.");
    }
    return input;
}

long long getValidLong() {
    long long input;
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Input tidak valid! Harus berupa angka.");
    }
    return input;
}

#endif