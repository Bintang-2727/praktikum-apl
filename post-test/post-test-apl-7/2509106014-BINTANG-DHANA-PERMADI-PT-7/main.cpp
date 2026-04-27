#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include "TokoBaju.h"

using namespace std;

void inisialisasiData(vector<User>& users, vector<Produk>& produk) {
    users.push_back({"admin", "admin123", "admin"});
    users.push_back({"bintang", "014", "user"});

    produk.push_back({"Kaos Lacoste", {250000, 10}});
    produk.push_back({"Celana Rucas", {400000, 15}});
    produk.push_back({"Jaket H&M",    {550000, 7}});
    produk.push_back({"Topi Nike",    {150000, 20}});
    produk.push_back({"Sepatu Adidas",{750000, 5}});
}

bool cekLogin(vector<User>& users, string username, string password, string &roleAkun, string &namaAkun) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].username == username && users[i].password == password) {
            roleAkun = users[i].role;
            namaAkun = users[i].username;
            return true;
        }
    }
    return false;
}

void lihatProduk(const vector<Produk>& produk) {
    cout << "\n=== DAFTAR SEMUA PRODUK ===\n";
    if (produk.empty()) cout << "Belum ada produk.\n";
    else {
        cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
        cout << "--------------------------------------------------\n";
        for(size_t i = 0; i < produk.size(); i++) {
            cout << left << setw(5) << i + 1 << setw(20) << produk[i].nama << "Rp " << setw(12) << produk[i].detail.harga << produk[i].detail.stok << "\n";
        }
    }
}

void lihatProduk(const vector<Produk>& produk, bool hanyaTersedia) {
    cout << "\n=== DAFTAR PRODUK TERSEDIA ===\n";
    if (produk.empty()) cout << "Belum ada produk.\n";
    else {
        cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
        cout << "--------------------------------------------------\n";
        for(size_t i = 0; i < produk.size(); i++) {
            if (hanyaTersedia && produk[i].detail.stok <= 0) continue;
            cout << left << setw(5) << i + 1 << setw(20) << produk[i].nama << "Rp " << setw(12) << produk[i].detail.harga << produk[i].detail.stok << "\n";
        }
    }
}

long long hitungTotalBelanja(vector<Produk>& keranjang, int n) {
    if (n <= 0) return 0;
    return keranjang[n - 1].detail.harga + hitungTotalBelanja(keranjang, n - 1);
}

void tambahProduk(vector<Produk>& produk) {
    cout << "\n=== TAMBAH PRODUK ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    Produk produkBaru;
    cout << "Nama produk : "; getline(cin, produkBaru.nama);
    cout << "Harga produk: "; produkBaru.detail.harga = getValidLong();
    cout << "Stok produk : "; produkBaru.detail.stok = getValidInt();
    
    produk.push_back(produkBaru);
    cout << "Produk berhasil ditambahkan!\n";
}

void updateProduk(vector<Produk>& produk) {
    cout << "\n=== UBAH PRODUK ===\n";
    lihatProduk(produk); 
    if(produk.empty()) return;

    cout << "\nMasukkan nomor produk yang ingin diubah: ";
    int idxUbah = getValidInt();

    if (idxUbah > 0 && idxUbah <= produk.size()) {
        int target = idxUbah - 1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Nama baru : "; getline(cin, produk[target].nama);
        cout << "Harga baru: "; produk[target].detail.harga = getValidLong();
        cout << "Stok baru : "; produk[target].detail.stok = getValidInt();
        
        cout << "Produk berhasil diperbarui!\n";
    } else {
        throw out_of_range("Nomor tidak valid!");
    }
}

void hapusProduk(vector<Produk>& produk) {
    cout << "\n=== HAPUS PRODUK ===\n";
    lihatProduk(produk); 
    if(produk.empty()) return;

    cout << "\nMasukkan nomor produk yang ingin dihapus: ";
    int idxHapus = getValidInt();

    if (idxHapus > 0 && idxHapus <= produk.size()) {
        produk.erase(produk.begin() + (idxHapus - 1));
        cout << "Produk berhasil dihapus.\n";
    } else {
        throw out_of_range("Nomor tidak valid!");
    }
}

void tampilkanHasilSorting(const vector<Produk>& temp) {
    cout << left << setw(5) << "No" << setw(20) << "Nama Produk"
         << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
    cout << "--------------------------------------------------\n";
    for (size_t i = 0; i < temp.size(); i++) {
        cout << left << setw(5)  << i + 1
             << setw(20) << temp[i].nama
             << "Rp " << setw(12) << temp[i].detail.harga
             << temp[i].detail.stok << "\n";
    }
}

void bubbleSortNamaDescending(vector<Produk> temp) {
    cout << "\n=== SORTING 1: BUBBLE SORT ===\n";
    cout << "    Kriteria : Nama Produk | Urutan : Z -> A (Descending)\n\n";
    bool swapped;
    for (size_t i = 0; i < temp.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < temp.size() - 1 - i; j++) {
            if (temp[j].nama < temp[j + 1].nama) {
                Produk tukar = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = tukar;
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
    tampilkanHasilSorting(temp);
}

void selectionSortHargaAscending(vector<Produk> temp) {
    cout << "\n=== SORTING 2: SELECTION SORT ===\n";
    cout << "    Kriteria : Harga | Urutan : Termurah -> Termahal (Ascending)\n\n";
    for (size_t i = 0; i < temp.size() - 1; i++) {
        size_t indeksMin = i;
        for (size_t j = i + 1; j < temp.size(); j++) {
            if (temp[j].detail.harga < temp[indeksMin].detail.harga) {
                indeksMin = j;
            }
        }
        if (indeksMin != i) {
            Produk tukar = temp[i];
            temp[i] = temp[indeksMin];
            temp[indeksMin] = tukar;
        }
    }
    tampilkanHasilSorting(temp);
}

void insertionSortStokAscending(vector<Produk> temp) {
    cout << "\n=== SORTING 3: INSERTION SORT ===\n";
    cout << "    Kriteria : Stok | Urutan : Sedikit -> Terbanyak (Ascending)\n\n";
    for (size_t i = 1; i < temp.size(); i++) {
        Produk key = temp[i];
        int j = i - 1;
        while (j >= 0 && temp[j].detail.stok > key.detail.stok) {
            temp[j + 1] = temp[j];
            j = j - 1;
        }
        temp[j + 1] = key;
    }
    tampilkanHasilSorting(temp);
}

void linearSearchNama(const vector<Produk>& produk, string cariNama) {
    bool found = false;
    cout << "\n=== HASIL PENCARIAN NAMA (LINEAR SEARCH) ===\n";
    
    for (size_t i = 0; i < produk.size(); i++) {
        if (produk[i].nama == cariNama) {
            cout << "Data ditemukan pada indeks ke-" << i << "!\n";
            cout << "- Nama  : " << produk[i].nama << "\n";
            cout << "- Harga : Rp " << produk[i].detail.harga << "\n";
            cout << "- Stok  : " << produk[i].detail.stok << "\n";
            found = true;
            break;
        }
    }
    
    if (!found) cout << "Data tidak ditemukan dalam array.\n";
}

void binarySearchHarga(vector<Produk> temp, long long cariHarga) {
    // Binary search butuh data terurut (Sorting dulu berdasarkan Harga Ascending)
    for (size_t i = 0; i < temp.size() - 1; i++) {
        size_t indeksMin = i;
        for (size_t j = i + 1; j < temp.size(); j++) {
            if (temp[j].detail.harga < temp[indeksMin].detail.harga) {
                indeksMin = j;
            }
        }
        Produk tukar = temp[i];
        temp[i] = temp[indeksMin];
        temp[indeksMin] = tukar;
    }

    int low = 0;
    int high = temp.size() - 1;
    bool found = false;
    
    cout << "\n=== HASIL PENCARIAN HARGA (BINARY SEARCH) ===\n";
    
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        long long hargaMid = temp[mid].detail.harga;
        
        if (hargaMid == cariHarga) {
            cout << "Produk dengan harga Rp " << cariHarga << " ditemukan:\n";
            cout << "- Nama  : " << temp[mid].nama << "\n";
            cout << "- Harga : Rp " << temp[mid].detail.harga << "\n";
            cout << "- Stok  : " << temp[mid].detail.stok << "\n";
            found = true;
            break;
        } 
        else if (hargaMid < cariHarga) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }
    }

    if (!found) cout << "Angka harga " << cariHarga << " tidak ada dalam data.\n";
}

void menuSorting(const vector<Produk>& produk) {
    if (produk.empty()) {
        cout << "Belum ada produk untuk diurutkan.\n";
        return;
    }

    int pilihanSort = 0;
    while (pilihanSort != 4) {
        clearScreen();
        cout << "\n=== MENU SORTING PRODUK ===\n";
        cout << "1. Bubble Sort    - Nama Produk  (Z -> A              / Descending)\n";
        cout << "2. Selection Sort - Harga Produk (Termurah -> Termahal / Ascending)\n";
        cout << "3. Insertion Sort - Stok Produk  (Sedikit -> Terbanyak / Ascending)\n";
        cout << "4. Kembali ke Menu Admin\n";
        cout << "Pilih metode sorting: ";
        
        try {
            pilihanSort = getValidInt();
            if      (pilihanSort == 1) bubbleSortNamaDescending(produk);
            else if (pilihanSort == 2) selectionSortHargaAscending(produk);
            else if (pilihanSort == 3) insertionSortStokAscending(produk);
            else if (pilihanSort == 4) cout << "Kembali ke Menu Admin.\n";
            else throw out_of_range("Pilihan tidak valid!");
            
            if(pilihanSort != 4) pauseLayar();
        } catch(const exception& e) {
            cout << "[ERROR] " << e.what() << "\n";
            pauseLayar();
        }
    }
}

void menuSearching(const vector<Produk>& produk) {
    if (produk.empty()) {
        cout << "Belum ada produk untuk dicari.\n";
        return;
    }

    int pilihanSearch = 0;
    while (pilihanSearch != 3) {
        clearScreen();
        cout << "\n=== MENU SEARCHING PRODUK ===\n";
        cout << "1. Linear Search - Cari Kata (Berdasarkan Nama Produk)\n";
        cout << "2. Binary Search - Cari Angka (Berdasarkan Harga Produk)\n";
        cout << "3. Kembali ke Menu Admin\n";
        cout << "Pilih metode searching: ";
        
        try {
            pilihanSearch = getValidInt();
            if (pilihanSearch == 1) {
                string cariNama;
                cout << "Masukkan nama produk yang dicari (Sama Persis & Case Sensitive): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cariNama);
                linearSearchNama(produk, cariNama);
            } 
            else if (pilihanSearch == 2) {
                cout << "Masukkan harga produk yang dicari: ";
                long long cariHarga = getValidLong();
                binarySearchHarga(produk, cariHarga);
            } 
            else if (pilihanSearch == 3) {
                cout << "Kembali ke Menu Admin.\n";
            } 
            else throw out_of_range("Pilihan tidak valid!");
            
            if(pilihanSearch != 3) pauseLayar();
        } catch(const exception& e) {
            cout << "[ERROR] " << e.what() << "\n";
            pauseLayar();
        }
    }
}

void menuAdmin(vector<Produk>& produk) {
    int menu = 0;
    while (menu != 7) {
        clearScreen();
        cout << "\n=== MENU ADMIN TOKO BAJU BRAND ===\n";
        cout << "1. Lihat Produk\n2. Tambah Produk\n3. Update Produk\n";
        cout << "4. Hapus Produk\n5. Sorting Produk\n6. Searching Produk\n7. Logout\n";
        cout << "Pilih menu: ";
        
        try {
            menu = getValidInt();
            if      (menu == 1) lihatProduk(produk); 
            else if (menu == 2) tambahProduk(produk);
            else if (menu == 3) updateProduk(produk);
            else if (menu == 4) hapusProduk(produk);
            else if (menu == 5) menuSorting(produk);
            else if (menu == 6) menuSearching(produk);
            else if (menu == 7) cout << "Logout Admin berhasil.\n";
            else throw out_of_range("Pilihan tidak valid.");
            
            if(menu >= 1 && menu <= 4) pauseLayar();
        } catch(const exception& e) {
            cout << "[ERROR] " << e.what() << "\n";
            pauseLayar();
        }
    }
}

void menuUser(string namaAkun, vector<Produk>& produk) {
    vector<Produk> keranjang;
    int pilihUser = -1;

    while (pilihUser != 0) {
        clearScreen();
        cout << "\n=== SELAMAT DATANG " << namaAkun << " DI TOKO BAJU BRAND ===\n";
        lihatProduk(produk, true); 
        
        cout << "\n0. Checkout (Selesai Belanja)\n";
        cout << "Pilih produk untuk dimasukkan ke keranjang (Berdasarkan No Asli): ";
        
        try {
            pilihUser = getValidInt();

            if (pilihUser > 0 && pilihUser <= produk.size()) {
                int target = pilihUser - 1;
                
                if (produk[target].detail.stok > 0) {
                    keranjang.push_back(produk[target]);
                    produk[target].detail.stok--; 
                    cout << produk[target].nama << " masuk ke keranjang!\n";
                } else {
                    throw runtime_error("Maaf, stok habis!");
                }
                pauseLayar();
            } 
            else if (pilihUser == 0) {
                clearScreen();
                cout << "\n=== STRUK BELANJA ===\n";
                cout << left << setw(25) << "Item" << "Harga\n";
                cout << "-------------------------------------\n";
                for(size_t j = 0; j < keranjang.size(); j++) {
                    cout << left << setw(25) << keranjang[j].nama << "Rp " << keranjang[j].detail.harga << "\n";
                }
                cout << "-------------------------------------\n";
                long long total = hitungTotalBelanja(keranjang, keranjang.size());
                cout << left << setw(25) << "Total Belanja" << "Rp " << total << "\n";
                cout << "Terima kasih telah berbelanja!\n";
                pauseLayar();
            } 
            else {
                throw out_of_range("Pilihan nomor produk tidak valid!");
            }
        } catch(const exception& e) {
            cout << "[ERROR] " << e.what() << "\n";
            pauseLayar();
        }
    }
}

void registerAkun(vector<User>& users) {
    clearScreen();
    cout << "=== REGISTER AKUN BARU ===\n";

    string userBaru, passBaru;
    cout << "Buat username: "; cin >> userBaru;
    cout << "Buat password: "; cin >> passBaru;

    bool duplikat = false;
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].username == userBaru) {
            duplikat = true;
            break;
        }
    }

    if (duplikat) {
        cout << "Username sudah terdaftar!\n";
    } else {
        users.push_back({userBaru, passBaru, "user"});
        cout << "Akun berhasil dibuat! Silakan login.\n";
    }
    pauseLayar();
}

void menuLogin(vector<User>& users, vector<Produk>& produk) {
    string username, password;
    int percobaan = 0;
    bool loginBerhasil = false;
    string roleAkun = "", namaAkun = "";

    while (percobaan < 3 && !loginBerhasil) {
        clearScreen();
        cout << "\n=== LOGIN (Kesempatan: " << 3 - percobaan << ") ===\n";
        cout << "Username: "; cin >> username;
        cout << "Password: "; cin >> password;

        loginBerhasil = cekLogin(users, username, password, roleAkun, namaAkun);

        if (loginBerhasil) {
            cout << "\nLogin berhasil sebagai " << roleAkun << "!\n";
            pauseLayar();
        } else {
            percobaan++;
            cout << "Login gagal! Username atau password salah.\n";
            if(percobaan < 3) pauseLayar();
        }
    }

    if (!loginBerhasil) {
        cout << "\nAnda telah gagal login 3 kali. Program berhenti otomatis.\n";
        exit(0); 
    }

    if (roleAkun == "admin") menuAdmin(produk);
    else if (roleAkun == "user") menuUser(namaAkun, produk);
}

int main() {
    vector<User> users;
    vector<Produk> produk;

    inisialisasiData(users, produk); 

    int pilih = 0;
    while (pilih != 3) {
        clearScreen(); 
        cout << "=== SELAMAT DATANG DI TOKO BAJU BRAND ===\n";
        cout << "1. Login\n2. Register\n3. Keluar\n";
        cout << "Pilih menu: ";
        
        try {
            pilih = getValidInt();
            if      (pilih == 1) menuLogin(users, produk);
            else if (pilih == 2) registerAkun(users);
            else if (pilih == 3) cout << "Terima kasih telah mengunjungi Toko Baju Brand!\n";
            else throw out_of_range("Pilihan tidak valid!");
        } catch(const exception& e) {
            cout << "[ERROR] " << e.what() << "\n";
            pauseLayar();
        }
    }
    return 0;
}