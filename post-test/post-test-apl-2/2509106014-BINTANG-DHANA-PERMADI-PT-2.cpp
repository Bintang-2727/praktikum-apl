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

int main() {
    User users[MAX_USER];
    Produk produk[MAX_PRODUK];
    
    int jumlahUser = 0;
    int jumlahProduk = 0;

    users[0] = {"admin", "admin123", "admin"};
    users[1] = {"bintang", "014", "user"};
    jumlahUser = 2;

    produk[0] = {"Kaos Lacoste", {250000, 10}};
    produk[1] = {"Celana Rucas", {400000, 15}};
    produk[2] = {"Jaket H&M", {550000, 8}};
    produk[3] = {"Topi Nike", {150000, 20}};
    produk[4] = {"Sepatu Adidas", {750000, 5}};
    jumlahProduk = 5;

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

                int i = 0;
                while (i < jumlahUser) {
                    if (users[i].username == username && users[i].password == password) {
                        loginBerhasil = true;
                        roleAkun = users[i].role;
                        namaAkun = users[i].username;
                        break;
                    }
                    i++;
                }

                if (loginBerhasil) {
                    cout << "\nLogin berhasil sebagai " << roleAkun << "!\n";
                } else {
                    percobaan++;
                    cout << "Login gagal! Username atau password salah.\n";
                }
            }

            if (!loginBerhasil) {
                cout << "\nAnda telah gagal login 3 kali. Program berhenti otomatis.\n";
                return 0; 
            }

            if (roleAkun == "admin") {
                int menuAdmin = 0;
                while (menuAdmin != 5) {
                    cout << "\n=== MENU ADMIN TOKO BAJU BRAND ===\n";
                    cout << "1. Lihat Produk\n";
                    cout << "2. Tambah Produk\n";
                    cout << "3. Update Produk\n";
                    cout << "4. Hapus Produk\n";
                    cout << "5. Logout\n";
                    cout << "Pilih menu: ";
                    cin >> menuAdmin;

                    if (menuAdmin == 1) {
                        cout << "\n=== DAFTAR PRODUK ===\n";
                        if (jumlahProduk == 0) cout << "Belum ada produk.\n";
                        else {
                            cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
                            cout << "--------------------------------------------------\n";
                            int i = 0;
                            while (i < jumlahProduk) {
                                cout << left << setw(5) << i + 1 << setw(20) << produk[i].nama << "Rp " << setw(12) << produk[i].detail.harga << produk[i].detail.stok << "\n";
                                i++;
                            }
                        }
                    } 
                    else if (menuAdmin == 2) {
                        if (jumlahProduk >= MAX_PRODUK) {
                            cout << "Kapasitas gudang penuh!\n";
                        } else {
                            cout << "\n=== TAMBAH PRODUK ===\n";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Nama produk : "; getline(cin, produk[jumlahProduk].nama);
                            cout << "Harga produk: "; cin >> produk[jumlahProduk].detail.harga;
                            cout << "Stok produk : "; cin >> produk[jumlahProduk].detail.stok;
                            jumlahProduk++;
                            cout << "Produk berhasil ditambahkan!\n";
                        }
                    } 
                    else if (menuAdmin == 3) {
                        cout << "\n=== UBAH PRODUK ===\n";
                        cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
                        int i = 0;
                        while (i < jumlahProduk) {
                            cout << left << setw(5) << i + 1 << setw(20) << produk[i].nama << "Rp " << setw(12) << produk[i].detail.harga << produk[i].detail.stok << "\n";
                            i++;
                        }
                        
                        int idxUbah;
                        cout << "\nMasukkan nomor produk yang ingin diubah: ";
                        cin >> idxUbah;

                        if (idxUbah > 0 && idxUbah <= jumlahProduk) {
                            int target = idxUbah - 1;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Nama baru : "; getline(cin, produk[target].nama);
                            cout << "Harga baru: "; cin >> produk[target].detail.harga;
                            cout << "Stok baru : "; cin >> produk[target].detail.stok;
                            cout << "Produk berhasil diperbarui!\n";
                        } else {
                            cout << "Nomor tidak valid!\n";
                        }
                    } 
                    else if (menuAdmin == 4) {
                        cout << "\n=== HAPUS PRODUK ===\n";
                        cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
                        int i = 0;
                        while (i < jumlahProduk) {
                            cout << left << setw(5) << i + 1 << setw(20) << produk[i].nama << "Rp " << setw(12) << produk[i].detail.harga << produk[i].detail.stok << "\n";
                            i++;
                        }

                        int idxHapus;
                        cout << "\nMasukkan nomor produk yang ingin dihapus: ";
                        cin >> idxHapus;

                        if (idxHapus > 0 && idxHapus <= jumlahProduk) {
                            int k = idxHapus - 1;
                            while (k < jumlahProduk - 1) {
                                produk[k] = produk[k + 1];
                                k++;
                            }
                            jumlahProduk--;
                            cout << "Produk berhasil dihapus.\n";
                        } else {
                            cout << "Nomor tidak valid!\n";
                        }
                    } 
                    else if (menuAdmin == 5) {
                        cout << "Logout Admin berhasil.\n";
                    } else {
                        cout << "Pilihan tidak valid.\n";
                    }
                }
            }
            else if (roleAkun == "user") {
                Produk keranjang[MAX_KERANJANG];
                int isiKeranjang = 0;
                long long totalBelanja = 0;
                int pilihUser = -1;

                while (pilihUser != 0) {
                    cout << "\n=== SELAMAT DATANG " << namaAkun << " DI TOKO BAJU BRAND ===\n";
                    cout << left << setw(5) << "No" << setw(20) << "Nama Produk" << setw(15) << "Harga" << setw(10) << "Stok" << "\n";
                    cout << "--------------------------------------------------\n";
                    int i = 0;
                    while (i < jumlahProduk) {
                        cout << left << setw(5) << i + 1 << setw(20) << produk[i].nama << "Rp " << setw(12) << produk[i].detail.harga << produk[i].detail.stok << "\n";
                        i++;
                    }
                    cout << "0. Checkout (Selesai Belanja)\n";
                    cout << "\nPilih produk untuk dimasukkan ke keranjang: ";
                    cin >> pilihUser;

                    if (pilihUser > 0 && pilihUser <= jumlahProduk) {
                        int target = pilihUser - 1;
                        if (produk[target].detail.stok > 0) {
                            keranjang[isiKeranjang] = produk[target];
                            totalBelanja += produk[target].detail.harga;
                            isiKeranjang++;
                            produk[target].detail.stok--; 
                            cout << produk[target].nama << " masuk ke keranjang!\n";
                        } else {
                            cout << "Maaf, stok habis!\n";
                        }
                    } 
                    else if (pilihUser == 0) {
                        cout << "\n=== STRUK BELANJA ===\n";
                        cout << left << setw(25) << "Item" << "Harga\n";
                        cout << "-------------------------------------\n";
                        int j = 0;
                        while (j < isiKeranjang) {
                            cout << left << setw(25) << keranjang[j].nama << "Rp " << keranjang[j].detail.harga << "\n";
                            j++;
                        }
                        cout << "-------------------------------------\n";
                        cout << left << setw(25) << "Total Belanja" << "Rp " << totalBelanja << "\n";
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
        } 
        else if (pilih == 2) {
            system("cls || clear");
            cout << "=== REGISTER AKUN BARU ===\n";
            if (jumlahUser >= MAX_USER) {
                cout << "Kapasitas user penuh!\n";
            } else {
                string userBaru, passBaru;
                cout << "Buat username: "; cin >> userBaru;
                cout << "Buat password: "; cin >> passBaru;

                bool duplikat = false;
                int i = 0;
                while (i < jumlahUser) {
                    if (users[i].username == userBaru) {
                        duplikat = true;
                        break;
                    }
                    i++;
                }

                if (duplikat) {
                    cout << "Username sudah terdaftar!\n";
                } else {
                    users[jumlahUser].username = userBaru;
                    users[jumlahUser].password = passBaru;
                    users[jumlahUser].role = "user";
                    jumlahUser++;
                    cout << "Akun berhasil dibuat! Silakan login.\n";
                }
                cout << "\nTekan enter untuk melanjutkan...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
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