#include <iostream>
#include <string>

using namespace std;

int main() {

    const string VALID_NAME = "bintang";
    const string VALID_PASS = "123";
    
    string nama, password;
    int attempts = 0;
    bool statusLogin = false; 

    cout << "========================================\n";
    cout << "           SISTEM LOGIN                 \n";
    cout << "========================================\n";

    while (attempts < 3) {
        cout << "[User] Masukkan Nama       : ";
        cin >> nama;
        cout << "[Kunci] Masukkan Password  : ";
        cin >> password;

        if (nama == VALID_NAME && password == VALID_PASS) {
            cout << "\n[+] Login Berhasil! Selamat datang, " << nama << ".\n";
            statusLogin = true;
            break; 
        } else {
            attempts++;
            cout << "[-] Login Gagal! (Sisa percobaan: " << 3 - attempts << ")\n\n";
        }
    }

    if (statusLogin) {
        string pilihan;
        while (true) {
            cout << "\n========================================\n";
            cout << "          MENU KONVERSI WAKTU           \n";
            cout << "========================================\n";
            cout << " [1] Jam   --> Menit & Detik\n";
            cout << " [2] Menit --> Jam & Detik\n";
            cout << " [3] Detik --> Jam & Menit\n";
            cout << " [4] Keluar\n";
            cout << "----------------------------------------\n";
            cout << "Pilih menu (1/2/3/4): ";
            cin >> pilihan;

            if (pilihan == "1") {
                double jam;
                cout << "\n--- Konversi Jam ---\n";
                cout << "Masukkan jumlah Jam: ";
                cin >> jam;
                cout << "=> Hasil: " << jam << " Jam = " << jam * 60 << " Menit dan " << jam * 3600 << " Detik\n";

            } else if (pilihan == "2") {
                double menit;
                cout << "\n--- Konversi Menit ---\n";
                cout << "Masukkan jumlah Menit: ";
                cin >> menit;
                
                cout << "=> Hasil: " << menit << " Menit = " << menit / 60.0 << " Jam dan " << menit * 60.0 << " Detik\n";

            } else if (pilihan == "3") {
                double detik;
                cout << "\n--- Konversi Detik ---\n";
                cout << "Masukkan jumlah Detik: ";
                cin >> detik;
                
                cout << "=> Hasil: " << detik << " Detik = " << detik / 3600.0 << " Jam dan " << detik / 60.0 << " Menit\n";

            } else if (pilihan == "4") {
                cout << "\nTerima kasih telah menggunakan program ini. Sampai jumpa!\n";
                break;
            } else {
                cout << "\n[!] Pilihan tidak valid!\n";
            }
        }
    } else {
        cout << "[!] Anda telah gagal 3 kali. Program berhenti.\n";
    }

    return 0;
}