#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;

#define MAX_USER 50
#define MAX_PRODUK 100
#define MAX_KERANJANG 100

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

void inisialisasiData(User *users, int *jumlahUser, Produk *produk, int *jumlahProduk) {
    (users + 0)->username = "admin";
    (users + 0)->password = "admin123";
    (users + 0)->role = "admin";

    (users + 1)->username = "bintang";
    (users + 1)->password = "014";
    (users + 1)->role = "user";
    
    *jumlahUser = 2;

    (produk + 0)->nama = "Kaos Lacoste"; (produk + 0)->detail = {250000, 10};
    (produk + 1)->nama = "Celana Rucas"; (produk + 1)->detail = {400000, 15};
    (produk + 2)->nama = "Jaket H&M";    (produk + 2)->detail = {550000, 7}; 
    (produk + 3)->nama = "Topi Nike";    (produk + 3)->detail = {150000, 20};
    (produk + 4)->nama = "Sepatu Adidas";(produk + 4)->detail = {750000, 5};
    
    *jumlahProduk = 5;
}

bool cekLogin(User *users, int jumlahUser, string username, string password, string &roleAkun, string &namaAkun) {
    for (int i = 0; i < jumlahUser; i++) {
        User *currentUser = &users[i];
        if (currentUser->username == username && currentUser->password == password) {
            roleAkun = currentUser->role;
            namaAkun = currentUser->username;
            return true;
        }
    }
    return false;
}

void lihatProduk(Produk *produk, int jumlahProduk) {
    cout << "\n=== DAFTAR SEMUA PRODUK ===\n";
    if (jumlahProduk == 0) cout << "Belum ada produk.\n";
    else {
        cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
        cout << "--------------------------------------------------\n";
        for(int i = 0; i < jumlahProduk; i++) {
            Produk *p = (produk + i);
            cout << left << setw(5) << i + 1 << setw(20) << p->nama << "Rp " << setw(12) << p->detail.harga << p->detail.stok << "\n";
        }
    }
}

void lihatProduk(Produk *produk, int jumlahProduk, bool hanyaTersedia) {
    cout << "\n=== DAFTAR PRODUK TERSEDIA ===\n";
    if (jumlahProduk == 0) cout << "Belum ada produk.\n";
    else {
        cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
        cout << "--------------------------------------------------\n";
        for(int i = 0; i < jumlahProduk; i++) {
            Produk *p = &produk[i];
            if (hanyaTersedia && p->detail.stok <= 0) continue;
            cout << left << setw(5) << i + 1 << setw(20) << p->nama << "Rp " << setw(12) << p->detail.harga << p->detail.stok << "\n";
        }
    }
}

long long hitungTotalBelanja(Produk *keranjang, int n) {
    if (n <= 0) return 0;
    Produk *k = &keranjang[n - 1];
    return k->detail.harga + hitungTotalBelanja(keranjang, n - 1);
}

void tambahProduk(Produk *produk, int &jumlahProduk) {
    if (jumlahProduk >= MAX_PRODUK) {
        cout << "Kapasitas gudang penuh!\n";
        return; 
    }
    cout << "\n=== TAMBAH PRODUK ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    Produk *produkBaru = &produk[jumlahProduk]; 
    cout << "Nama produk : "; getline(cin, produkBaru->nama);
    cout << "Harga produk: "; cin >> produkBaru->detail.harga;
    cout << "Stok produk : "; cin >> produkBaru->detail.stok;
    
    jumlahProduk++;
    cout << "Produk berhasil ditambahkan!\n";
}

void updateProduk(Produk *produk, int jumlahProduk) {
    cout << "\n=== UBAH PRODUK ===\n";
    lihatProduk(produk, jumlahProduk); 
    if(jumlahProduk == 0) return;

    int idxUbah;
    cout << "\nMasukkan nomor produk yang ingin diubah: ";
    cin >> idxUbah;

    if (idxUbah > 0 && idxUbah <= jumlahProduk) {
        int target = idxUbah - 1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        Produk *targetPtr = &produk[target];
        cout << "Nama baru : "; getline(cin, targetPtr->nama);
        cout << "Harga baru: "; cin >> targetPtr->detail.harga;
        cout << "Stok baru : "; cin >> targetPtr->detail.stok;
        
        cout << "Produk berhasil diperbarui!\n";
    } else {
        cout << "Nomor tidak valid!\n";
    }
}

void hapusProduk(Produk *produk, int *jumlahProduk) {
    cout << "\n=== HAPUS PRODUK ===\n";
    lihatProduk(produk, *jumlahProduk); 
    if(*jumlahProduk == 0) return;

    int idxHapus;
    cout << "\nMasukkan nomor produk yang ingin dihapus: ";
    cin >> idxHapus;

    if (idxHapus > 0 && idxHapus <= *jumlahProduk) {
        for (int k = idxHapus - 1; k < *jumlahProduk - 1; k++) {
            *(produk + k) = *(produk + k + 1);
        }
        (*jumlahProduk)--;
        cout << "Produk berhasil dihapus.\n";
    } else {
        cout << "Nomor tidak valid!\n";
    }
}

void tampilkanHasilSorting(Produk *temp, int jumlahProduk) {
    cout << left << setw(5) << "No" << setw(20) << "Nama Produk"
        << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < jumlahProduk; i++) {
        Produk *p = temp + i;
        cout << left << setw(5)  << i + 1
            << setw(20) << p->nama
            << "Rp " << setw(12) << p->detail.harga
            << p->detail.stok << "\n";
    }
}

void bubbleSortNamaDescending(Produk *produk, int jumlahProduk) {
    cout << "\n=== SORTING 1: BUBBLE SORT ===\n";
    cout << "    Kriteria : Nama Produk | Urutan : Z -> A (Descending)\n\n";
    Produk temp[MAX_PRODUK];
    for (int i = 0; i < jumlahProduk; i++) temp[i] = *(produk + i);
    bool swapped;
    for (int i = 0; i < jumlahProduk - 1; i++) {
        swapped = false;
        for (int j = 0; j < jumlahProduk - 1 - i; j++) {
            if ((temp + j)->nama < (temp + j + 1)->nama) {
                Produk tukar    = *(temp + j);
                *(temp + j)     = *(temp + j + 1);
                *(temp + j + 1) = tukar;
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
    tampilkanHasilSorting(temp, jumlahProduk);
}

void selectionSortHargaAscending(Produk *produk, int jumlahProduk) {
    cout << "\n=== SORTING 2: SELECTION SORT ===\n";
    cout << "    Kriteria : Harga | Urutan : Termurah -> Termahal (Ascending)\n\n";
    Produk temp[MAX_PRODUK];
    for (int i = 0; i < jumlahProduk; i++) temp[i] = *(produk + i);
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int indeksMin = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if ((temp + j)->detail.harga < (temp + indeksMin)->detail.harga) {
                indeksMin = j;
            }
        }
        if (indeksMin != i) {
            Produk tukar        = *(temp + i);
            *(temp + i)         = *(temp + indeksMin);
            *(temp + indeksMin) = tukar;
        }
    }
    tampilkanHasilSorting(temp, jumlahProduk);
}

void insertionSortStokAscending(Produk *produk, int jumlahProduk) {
    cout << "\n=== SORTING 3: INSERTION SORT ===\n";
    cout << "    Kriteria : Stok | Urutan : Sedikit -> Terbanyak (Ascending)\n\n";
    Produk temp[MAX_PRODUK];
    for (int i = 0; i < jumlahProduk; i++) temp[i] = *(produk + i);
    for (int i = 1; i < jumlahProduk; i++) {
        Produk key = *(temp + i);
        int j = i - 1;
        while (j >= 0 && (temp + j)->detail.stok > key.detail.stok) {
            *(temp + j + 1) = *(temp + j);
            j = j - 1;
        }
        *(temp + j + 1) = key;
    }
    tampilkanHasilSorting(temp, jumlahProduk);
}



void linearSearchNama(Produk *produk, int jumlahProduk, string cariNama) {
    bool found = false;
    cout << "\n=== HASIL PENCARIAN NAMA (LINEAR SEARCH) ===\n";
    
    for (int i = 0; i < jumlahProduk; i++) {
        if ((produk + i)->nama == cariNama) {
            cout << "Data ditemukan pada indeks ke-" << i << "!\n";
            cout << "- Nama  : " << (produk + i)->nama << "\n";
            cout << "- Harga : Rp " << (produk + i)->detail.harga << "\n";
            cout << "- Stok  : " << (produk + i)->detail.stok << "\n";
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Data tidak ditemukan dalam array.\n";
    }
}

void binarySearchHarga(Produk *produk, int jumlahProduk, long long cariHarga) {
    Produk temp[MAX_PRODUK];
    for (int i = 0; i < jumlahProduk; i++) {
        *(temp + i) = *(produk + i);
    }

    for (int i = 0; i < jumlahProduk - 1; i++) {
        int indeksMin = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if ((temp + j)->detail.harga < (temp + indeksMin)->detail.harga) {
                indeksMin = j;
            }
        }
        Produk tukar = *(temp + i);
        *(temp + i) = *(temp + indeksMin);
        *(temp + indeksMin) = tukar;
    }

    int low = 0;
    int high = jumlahProduk - 1;
    bool found = false;
    
    cout << "\n=== HASIL PENCARIAN HARGA (BINARY SEARCH) ===\n";
    
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        
        long long hargaMid = (temp + mid)->detail.harga;
        
        if (hargaMid == cariHarga) {
            cout << "Produk dengan harga Rp " << cariHarga << " ditemukan:\n";
            cout << "- Nama  : " << (temp + mid)->nama << "\n";
            cout << "- Harga : Rp " << (temp + mid)->detail.harga << "\n";
            cout << "- Stok  : " << (temp + mid)->detail.stok << "\n";
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

    if (!found) {
        cout << "Angka harga " << cariHarga << " tidak ada dalam data.\n";
    }
}

void menuSorting(Produk *produk, int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << "Belum ada produk untuk diurutkan.\n";
        return;
    }

    int pilihanSort = 0;
    while (pilihanSort != 4) {
        cout << "\n=== MENU SORTING PRODUK ===\n";
        cout << "1. Bubble Sort    - Nama Produk  (Z -> A              / Descending)\n";
        cout << "2. Selection Sort - Harga Produk (Termurah -> Termahal / Ascending)\n";
        cout << "3. Insertion Sort - Stok Produk  (Sedikit -> Terbanyak / Ascending)\n";
        cout << "4. Kembali ke Menu Admin\n";
        cout << "Pilih metode sorting: ";
        cin >> pilihanSort;

        if      (pilihanSort == 1) bubbleSortNamaDescending(produk, jumlahProduk);
        else if (pilihanSort == 2) selectionSortHargaAscending(produk, jumlahProduk);
        else if (pilihanSort == 3) insertionSortStokAscending(produk, jumlahProduk);
        else if (pilihanSort == 4) cout << "Kembali ke Menu Admin.\n";
        else                       cout << "Pilihan tidak valid!\n";
    }
}

void menuSearching(Produk *produk, int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << "Belum ada produk untuk dicari.\n";
        return;
    }

    int pilihanSearch = 0;
    while (pilihanSearch != 3) {
        cout << "\n=== MENU SEARCHING PRODUK ===\n";
        cout << "1. Linear Search - Cari Kata (Berdasarkan Nama Produk)\n";
        cout << "2. Binary Search - Cari Angka (Berdasarkan Harga Produk)\n";
        cout << "3. Kembali ke Menu Admin\n";
        cout << "Pilih metode searching: ";
        cin >> pilihanSearch;

        if (pilihanSearch == 1) {
            string cariNama;
            cout << "Masukkan nama produk yang dicari (Sama Persis & Case Sensitive): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, cariNama);
            linearSearchNama(produk, jumlahProduk, cariNama);
        } 
        else if (pilihanSearch == 2) {
            long long cariHarga;
            cout << "Masukkan harga produk yang dicari: ";
            cin >> cariHarga;
            binarySearchHarga(produk, jumlahProduk, cariHarga);
        } 
        else if (pilihanSearch == 3) {
            cout << "Kembali ke Menu Admin.\n";
        } 
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}

void menuAdmin(Produk *produk, int &jumlahProduk) {
    int menu = 0;
    while (menu != 7) {
        cout << "\n=== MENU ADMIN TOKO BAJU BRAND ===\n";
        cout << "1. Lihat Produk\n";
        cout << "2. Tambah Produk\n";
        cout << "3. Update Produk\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Sorting Produk\n";
        cout << "6. Searching Produk\n"; 
        cout << "7. Logout\n";
        cout << "Pilih menu: ";
        cin >> menu;

        if      (menu == 1) lihatProduk(produk, jumlahProduk); 
        else if (menu == 2) tambahProduk(produk, jumlahProduk);
        else if (menu == 3) updateProduk(produk, jumlahProduk);
        else if (menu == 4) hapusProduk(produk, &jumlahProduk);
        else if (menu == 5) menuSorting(produk, jumlahProduk);
        else if (menu == 6) menuSearching(produk, jumlahProduk);
        else if (menu == 7) cout << "Logout Admin berhasil.\n";
        else                cout << "Pilihan tidak valid.\n";
    }
}

void menuUser(string namaAkun, Produk *produk, int &jumlahProduk) {
    Produk keranjang[MAX_KERANJANG];
    int isiKeranjang = 0;
    int pilihUser = -1;

    while (pilihUser != 0) {
        cout << "\n=== SELAMAT DATANG " << namaAkun << " DI TOKO BAJU BRAND ===\n";
        lihatProduk(produk, jumlahProduk, true); 
        
        cout << "0. Checkout (Selesai Belanja)\n";
        cout << "\nPilih produk untuk dimasukkan ke keranjang (Berdasarkan No Asli): ";
        cin >> pilihUser;

        if (pilihUser > 0 && pilihUser <= jumlahProduk) {
            int target = pilihUser - 1;
            Produk *pTarget = &produk[target];
            
            if (pTarget->detail.stok > 0) {
                keranjang[isiKeranjang] = *pTarget;
                isiKeranjang++;
                pTarget->detail.stok--; 
                cout << pTarget->nama << " masuk ke keranjang!\n";
            } else {
                cout << "Maaf, stok habis!\n";
            }
        } 
        else if (pilihUser == 0) {
            cout << "\n=== STRUK BELANJA ===\n";
            cout << left << setw(25) << "Item" << "Harga\n";
            cout << "-------------------------------------\n";
            for(int j = 0; j < isiKeranjang; j++) {
                Produk *pK = &keranjang[j];
                cout << left << setw(25) << pK->nama << "Rp " << pK->detail.harga << "\n";
            }
            cout << "-------------------------------------\n";
            
            long long total = hitungTotalBelanja(keranjang, isiKeranjang);
            
            cout << left << setw(25) << "Total Belanja" << "Rp " << total << "\n";
            cout << "Terima kasih telah berbelanja!\n";
            cout << "Tekan Enter untuk keluar akun...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        } 
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}

void registerAkun(User *users, int &jumlahUser) {
    system("cls || clear");
    cout << "=== REGISTER AKUN BARU ===\n";
    if (jumlahUser >= MAX_USER) {
        cout << "Kapasitas user penuh!\n";
        return;
    } 

    string userBaru, passBaru;
    cout << "Buat username: "; cin >> userBaru;
    cout << "Buat password: "; cin >> passBaru;

    bool duplikat = false;
    for (int i = 0; i < jumlahUser; i++) {
        User *u = &users[i];
        if (u->username == userBaru) {
            duplikat = true;
            break;
        }
    }

    if (duplikat) {
        cout << "Username sudah terdaftar!\n";
    } else {
        User *newUser = &users[jumlahUser];
        newUser->username = userBaru;
        newUser->password = passBaru;
        newUser->role = "user";
        jumlahUser++;
        cout << "Akun berhasil dibuat! Silakan login.\n";
    }
    cout << "\nTekan enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void menuLogin(User *users, int &jumlahUser, Produk *produk, int &jumlahProduk) {
    system("cls || clear");
    string username, password;
    int percobaan = 0;
    bool loginBerhasil = false;
    string roleAkun = "";
    string namaAkun = "";

    while (percobaan < 3 && !loginBerhasil) {
        cout << "\n=== LOGIN (Kesempatan: " << 3 - percobaan << ") ===\n";
        cout << "Username: "; cin >> username;
        cout << "Password: "; cin >> password;

        loginBerhasil = cekLogin(users, jumlahUser, username, password, roleAkun, namaAkun);

        if (loginBerhasil) {
            cout << "\nLogin berhasil sebagai " << roleAkun << "!\n";
        } else {
            percobaan++;
            cout << "Login gagal! Username atau password salah.\n";
        }
    }

    if (!loginBerhasil) {
        cout << "\nAnda telah gagal login 3 kali. Program berhenti otomatis.\n";
        exit(0); 
    }

    if (roleAkun == "admin") {
        menuAdmin(produk, jumlahProduk);
    } else if (roleAkun == "user") {
        menuUser(namaAkun, produk, jumlahProduk);
    }
}

int main() {
    User users[MAX_USER];
    Produk produk[MAX_PRODUK];
    int jumlahUser = 0;
    int jumlahProduk = 0;

    inisialisasiData(users, &jumlahUser, produk, &jumlahProduk); 

    int pilih = 0;
    while (pilih != 3) {
        system("cls || clear"); 
        cout << "=== SELAMAT DATANG DI TOKO BAJU BRAND ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilih;

        if (pilih == 1) {
            menuLogin(users, jumlahUser, produk, jumlahProduk);
        } 
        else if (pilih == 2) {
            registerAkun(users, jumlahUser);
        } 
        else if (pilih == 3) {
            cout << "Terima kasih telah mengunjungi Toko Baju Brand!\n";
        } 
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}