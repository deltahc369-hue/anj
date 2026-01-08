#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <string>
using namespace std;



struct Gaji{
    vector <int> gaji_karyawan = {
        1500 , 1550 , 1450
    };
    vector <int> gaji_manager = {
        1700 , 1680
    };
};

struct Karyawan{
    vector <string> kw = {
        "asep" , "badang" , "bagas simanjutak"
    };
    vector <string> mng = {
        "anam" , "adeknya asep"
    };
};
class Toko{
    private:
        Gaji gaji;
        Karyawan karyawan;
        friend void manager(Toko &toko , string nama);
        void karyawan_login(string nama);
        friend void tambah_karyawan(Toko &toko);
    public:
        int cek_gaji(string nama);
        friend void login(Toko &toko);
};

void ign_inp(){
    cin.clear();
    cin.ignore(numeric_limits<char>::max() , '\n');
}

void tambah_karyawan(Toko &toko){
    ign_inp();
    string nama;
    int gaji;
    cout << "masukan nama : ";
    getline(cin,nama);
    cout << "gajinya berapa : ";
    cin >> gaji;
    toko.karyawan.kw.push_back(nama);
    toko.gaji.gaji_karyawan.push_back(gaji);
    cout << toko.karyawan.kw[toko.karyawan.kw.size()-1] << endl;
    cout << toko.gaji.gaji_karyawan[toko.karyawan.kw.size()-1] << endl;
}

void manager(Toko &toko , string nama){
    cout << "login sebagai manager\n";
    toko.cek_gaji(nama);
    cout << "mau tambah karyawan? [1 untuk ya , 2 untuk tidak , default : ya] : ";
    int inp;
    cin >> inp;
    switch(inp){
        case 1 :
            tambah_karyawan(toko);
            break;
        case 2 :
            return;
        default:
            tambah_karyawan(toko);
    }
}

void Toko::karyawan_login(string nama){
    Toko toko;
    cout << "login sebagai karyawan\n";
    toko.cek_gaji(nama);
}

void login(Toko &toko){
    string nama;
    cout << "masukkan nama anda : ";
    getline(cin , nama);
    bool valid = false;
    for(int i = 0 ; i < toko.karyawan.mng.size() ; i++){
        if(nama == toko.karyawan.mng[i]){
            valid = true;
            manager(toko , nama);
            break;
        }
    }
    for(int i = 0 ; i < toko.karyawan.kw.size() ; i++){
        if(nama == toko.karyawan.kw[i]){
            valid = true;
            toko.karyawan_login(nama);
            break;
        }
    }
    if(!valid){
        cout << "nama " << nama << "tidak terdaftar!\n"; 
    }
}

int Toko::cek_gaji(string nama){
    for(int i = 0 ; i < karyawan.mng.size() ; i++){
        if(nama == karyawan.mng[i]){
            cout << "gaji anda adalah : " << gaji.gaji_manager[i] << endl << endl;
        }
    }
    for(int i = 0 ; i < karyawan.kw.size() ; i++){
        if(nama == karyawan.kw[i]){
            cout << "gaji anda adalah : " << gaji.gaji_karyawan[i] << endl << endl;
        }
    }
    return 0;
}

int main(){
    Toko toko;
    login(toko);
    return 0;
}