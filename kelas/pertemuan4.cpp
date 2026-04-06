// // #include<iostream>
// // using namespace std;

// // struct Address{
// //     string kota;
// //     string provinsi;
// //     string negara;
// // };

// // int main(){
// //     Address address1, address2;
// //     address1.kota = "Samarinda";
// //     address1.provinsi = "Kalimantan Timur";
// //     address1.negara = "Indonesia";

// //     address2 = address1;
// //     address2.kota = "IKN";

// //     cout << address1.kota << endl;
// //     cout << address2.kota << endl;
// //     return 0;
// // }

// #include<iostream>
// using namespace std;

// int main(){
//     string nama = "Rangga Aryawinata";
//     cout << &nama << " adalah alamatnya " << nama << endl;
//     return 0;
// }

#include<iostream>
using namespace std;

int main(){
    string var = "Aku Variabel";
    string* varPtr = &var;

    cout << "Hasil dari varPtr (Alamat): " << varPtr << endl;
    cout << "Hasil dari *varPtr (Nilai): " << *varPtr << endl;
    cout << endl << "Kesimpulannya varPtr isi nya alamatnya var" << endl;
    cout << "*varPtr hasilnya value dari var" << endl;
    cout << endl;
    cout << "Hasil/value dari var: " << var << endl;
    cout << "Hasil/value dari alamat var (&var): " << &var << endl;
    cout << "Hasil/value dari varPtr: " << varPtr << endl;
    cout << "Hasil/value dari *varPtr: " << *varPtr << endl;
    return 0;
}