#include <iostream>
#include <string>
using namespace std;

struct Pengguna {
    string nama;
    string nim;
};

struct Service {
    string jenisService;
    string tanggal;
    double biaya;
    string status;
};

struct Pelanggan {
    string nama;
    string noKendaraan;
    string kontak;
    Service riwayat;
};

int main() {
    // ====== Data Pengguna ======
    Pengguna daftarPengguna[100];
    int jumlahPengguna = 0;

    // ====== Data Pelanggan ======
    Pelanggan daftarPelanggan[100];
    int jumlahPelanggan = 0;

    bool programBerjalan = true;

    while (programBerjalan) {
        cout << "\n=== Menu Login/Register ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Keluar Program\n";
        cout << "Pilih: ";
        int pilihLogin;
        cin >> pilihLogin;
        cin.ignore();

        if (pilihLogin == 1) {
            // Register
            cout << "Masukkan Nama: ";
            getline(cin, daftarPengguna[jumlahPengguna].nama);
            cout << "Masukkan NIM: ";
            getline(cin, daftarPengguna[jumlahPengguna].nim);
            jumlahPengguna++;
            cout << "Register berhasil!\n";
        }
        else if (pilihLogin == 2) {
            // Login
            string inputNama, inputNim;
            int percobaan = 0;
            bool berhasilLogin = false;

            while (percobaan < 3) {
                cout << "Masukkan Nama: ";
                getline(cin, inputNama);
                cout << "Masukkan NIM: ";
                getline(cin, inputNim);

                for (int i = 0; i < jumlahPengguna; i++) {
                    if (inputNama == daftarPengguna[i].nama && inputNim == daftarPengguna[i].nim) {
                        cout << "Login berhasil!\n";
                        berhasilLogin = true;
                        break;
                    }
                }

                if (berhasilLogin) break;
                else {
                    cout << "Login gagal. Coba lagi.\n";
                    percobaan++;
                }
            }

            if (!berhasilLogin) {
                cout << "Kesempatan habis. Kembali ke menu login.\n";
                continue; // balik ke menu login
            }

            // ====== Menu CRUD Pelanggan ======
            int pilihan;
            bool logout = false;
            while (!logout) {
                cout << "\n=== Menu Utama ===\n";
                cout << "1. Tambah Data Pelanggan\n";
                cout << "2. Lihat Data\n";
                cout << "3. Update Status Service\n";
                cout << "4. Hapus Data\n";
                cout << "5. Logout\n";
                cout << "Pilih: ";
                cin >> pilihan;
                cin.ignore();

                if (pilihan == 1) {
                    cout << "Nama Pelanggan: ";
                    getline(cin, daftarPelanggan[jumlahPelanggan].nama);
                    cout << "No Kendaraan: ";
                    getline(cin, daftarPelanggan[jumlahPelanggan].noKendaraan);
                    cout << "Kontak: ";
                    getline(cin, daftarPelanggan[jumlahPelanggan].kontak);
                    cout << "Jenis Service: ";
                    getline(cin, daftarPelanggan[jumlahPelanggan].riwayat.jenisService);
                    cout << "Tanggal Service: ";
                    getline(cin, daftarPelanggan[jumlahPelanggan].riwayat.tanggal);
                    cout << "Biaya Service: ";
                    cin >> daftarPelanggan[jumlahPelanggan].riwayat.biaya;
                    cin.ignore();
                    daftarPelanggan[jumlahPelanggan].riwayat.status = "Proses";
                    jumlahPelanggan++;
                    cout << "Data berhasil ditambahkan!\n";
                }
                else if (pilihan == 2) {
                    cout << "\n=== Data Pelanggan ===\n";
                    for (int i = 0; i < jumlahPelanggan; i++) {
                        cout << "Nama        : " << daftarPelanggan[i].nama << endl;
                        cout << "No Kendaraan: " << daftarPelanggan[i].noKendaraan << endl;
                        cout << "Kontak      : " << daftarPelanggan[i].kontak << endl;
                        cout << "Jenis Servis: " << daftarPelanggan[i].riwayat.jenisService << endl;
                        cout << "Tanggal     : " << daftarPelanggan[i].riwayat.tanggal << endl;
                        cout << "Biaya       : " << daftarPelanggan[i].riwayat.biaya << endl;
                        cout << "Status      : " << daftarPelanggan[i].riwayat.status << endl;
                        cout << "-----------------------------\n";
                    }
                }
                else if (pilihan == 3) {
                    string cariNama;
                    cout << "Masukkan nama pelanggan yang ingin diupdate: ";
                    getline(cin, cariNama);
                    for (int i = 0; i < jumlahPelanggan; i++) {
                        if (daftarPelanggan[i].nama == cariNama) {
                            cout << "Status baru: ";
                            getline(cin, daftarPelanggan[i].riwayat.status);
                            cout << "Status berhasil diupdate!\n";
                        }
                    }
                }
                else if (pilihan == 4) {
                    string hapusNama;
                    cout << "Masukkan nama pelanggan yang ingin dihapus: ";
                    getline(cin, hapusNama);
                    for (int i = 0; i < jumlahPelanggan; i++) {
                        if (daftarPelanggan[i].nama == hapusNama) {
                            for (int j = i; j < jumlahPelanggan - 1; j++) {
                                daftarPelanggan[j] = daftarPelanggan[j+1];
                            }
                            jumlahPelanggan--;
                            cout << "Data berhasil dihapus!\n";
                            break;
                        }
                    }
                }
                else if (pilihan == 5) {
                    cout << "Logout berhasil. Kembali ke menu login.\n";
                    logout = true;
                }
            }
        }
        else if (pilihLogin == 0) {
            programBerjalan = false;
        }
    }

    cout << "Program selesai.\n";
    return 0;
}