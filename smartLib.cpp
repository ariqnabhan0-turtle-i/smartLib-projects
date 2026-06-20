#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// Palet Warna Premium CLI (Murni ANSI)
const string RESET         = "\033[0m"; 
const string HIJAU_NEON    = "\033[1;32m"; 
const string CYAN_NEON     = "\033[1;36m"; 
const string MAGENTA_CERAH = "\033[1;35m"; 
const string MERAH_CERAH   = "\033[1;31m"; 
const string KUNING_EMAS   = "\033[1;33m";

// ==========================================
// 4. IMPLEMENTASI STRUCT
// ==========================================
struct AkunUser {
    string namaLengkap;
    string username;
    string password;
};

struct buku{
    string judul;
    string penulis;
    int tahunTerbit;
    string idBuku;
    int jumlahBuku;

    float rating;
    int jumlahPerating;
    float totalSkorRating;

    bool tersedia;
    int jumlahDipinjam;
};

struct peminjaman{
    string username;
    string idBuku;
    string judulBuku;
    bool disetujui;
    
    int hariPinjam;
    int bulanPinjam;
    int tahunPinjam;
    
    int denda;
    bool sudahDibayar;
    
    int hariKembali;
	int bulanKembali;
	int tahunKembali;
	
	bool sudahKembali;
	int hariTelat;
};

// ==========================================
// 2. IMPLEMENTASI ARRAY (Database Banyak Akun)
// ==========================================
const int MAX_USER = 50, MAX_BUKU = 100;
AkunUser daftarUser[MAX_USER]; // Array bertipe Struct untuk menampung data user
buku daftarBuku[MAX_BUKU];
int jumlahUser = 0;            // Counter untuk menghitung jumlah user yang mendaftar
int jumlahBuku = 0;
int index;

// Database Peminjaman
const int MAX_PINJAM = 100;
peminjaman daftarPinjam[MAX_PINJAM];
int jumlahPinjam = 0;

// ==========================================
// 5. IMPLEMENTASI POINTER (Sesi Aktif Login)
// ==========================================
AkunUser* userAktif = nullptr; // Pointer untuk menunjuk akun siapa yang sedang login

// ==========================================
// 3. IMPLEMENTASI FUNCTION
// ==========================================

// buat ganti getch() itu
void tungguEnter() {
    string dummy;
    getline(cin, dummy);
}

void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void cetakTengah(string teks, string kodeWarna = "") {
    int lebarTerminal = 94;
    int panjangTeks = teks.length();
    int padding = (lebarTerminal - panjangTeks) / 2;
    
    if (padding > 0) {
        cout << setw(padding) << setfill(' ') << ""; 
    }
    cout << kodeWarna << teks << RESET << endl;
}
void tampilkanHeaderTengah() {
    cout << "\n";
    cetakTengah("======================================================================================", HIJAU_NEON);
    cetakTengah(R"( ________  _____ ______   ________  ________  _________  ___       ___  ________     )", CYAN_NEON);
    cetakTengah(R"(|\   ____\|\   _ \  _   \|\   __  \|\   __  \|\___   ___\\  \     |\  \|\   __  \    )", CYAN_NEON);
    cetakTengah(R"(\ \  \___|\ \  \\\__\ \  \ \  \|\  \ \  \|\  \|___ \  \_\ \  \    \ \  \ \  \|\ /_   )", CYAN_NEON);
    cetakTengah(R"( \ \_____  \ \  \\|__| \  \ \   __  \ \   _  _\   \ \  \ \ \  \    \ \  \ \   __  \  )", CYAN_NEON);
    cetakTengah(R"(  \|____|\  \ \  \    \ \  \ \  \ \  \ \  \\  \|   \ \  \ \ \  \____\ \  \ \  \|\  \ )", CYAN_NEON);
    cetakTengah(R"(    ____\_\  \ \__\    \ \__\ \__\ \__\ \__\\ _\    \ \__\ \ \_______\ \__\ \_______\)", CYAN_NEON);
    cetakTengah(R"(   |\_________\|__|     \|__|\|__|\|__|\|__|\|__|    \|__|  \|_______|\|__|\|_______|)", CYAN_NEON);
    cetakTengah(R"(   \|_________|                                                                      )", CYAN_NEON);
    cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
    cetakTengah("            SISTEM INFORMASI PERPUSTAKAAN PINTAR | KELOMPOK 19 PROJECTS               ", MAGENTA_CERAH);
    cetakTengah("======================================================================================", HIJAU_NEON);
    cout << "\n";
}

void ratingBuku(){
    int pilihBuku;
    bool ulang;
    int rate;

    do{
    ulang = false;
    bersihkanLayar();
    tampilkanHeaderTengah();
    cetakTengah("======================================================================================", HIJAU_NEON);
    cetakTengah("Rating Buku");
    cetakTengah("======================================================================================", HIJAU_NEON);

    cout << setw(30) << "Pilih Buku yang ingin diberikan rating" << endl;
    cout << "\n";

    for (int i = 0; i < jumlahBuku; i++){
        cout << setw(25) << setfill(' ') << "" << "[" << i+1 << "] " << daftarBuku[i].judul << endl;
    }

    cout << setw(25) << "[0] Keluar" << endl;

    cetakTengah("======================================================================================", HIJAU_NEON);
    cetakTengah("Pilih : ");

    cin >> pilihBuku;

    if (cin.fail() || pilihBuku < 0 || pilihBuku > jumlahBuku)
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << setw(30) << "[ERROR] Pilihan tidak valid!" << endl;
        ulang = true;
        tungguEnter();
        continue;
    } else if (pilihBuku == 0){
        return;
    }

    index = pilihBuku - 1;

    bersihkanLayar();
    cetakTengah("======================================================================================", HIJAU_NEON);
    cout << setw(30) << "Beri Rating untuk buku : " << daftarBuku[index].judul << endl;
    cetakTengah("======================================================================================", HIJAU_NEON);
    cout << "\n\n";
    cout << setw(30) << "Rating (1-5): ";
    cin >> rate;


    if (cin.fail()|| rate < 1 || rate > 5){
        cout << setw(30) << MERAH_CERAH << "[ERROR] Input tidak Valid!" << RESET << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        tungguEnter();
        ulang = true;
        continue;
    }

    cetakTengah("======================================================================================");
    cetakTengah("BERHASIL MEMBERI RATING PADA BUKU", HIJAU_NEON);
    cetakTengah("Tekan ENTER untuk Kembali", MAGENTA_CERAH);
    cin.ignore(1000,'\n');
    tungguEnter();

    daftarBuku[index].jumlahPerating += 1;
    daftarBuku[index].totalSkorRating += rate;

    daftarBuku[index].rating = daftarBuku[index].totalSkorRating / daftarBuku[index].jumlahPerating;
    }while(ulang);
}

void editBuku(){
    bool ulang_edit;
    string Sebelumnya; // ini buat edit tipe data string
    int Sebelumnya_angka; //ini buat edit tipe data int
    int perubahan = 0;

    Sebelumnya == daftarBuku[index].judul;
    bersihkanLayar();
    tampilkanHeaderTengah();
    cetakTengah("======================================================================================", HIJAU_NEON);
    cetakTengah("Langsung Tekan Enter jika tidak ingin mengubah bagian ini");
    cout << setw(25) << setfill(' ') << "" << "Masukan Judul Baru   : ";
    getline (cin, daftarBuku[index].judul);

    if (daftarBuku[index].judul.empty()){
        daftarBuku[index].judul = Sebelumnya;
    } else {
        perubahan++;
    }

    Sebelumnya = daftarBuku[index].penulis;
    bersihkanLayar();
    tampilkanHeaderTengah();
    cetakTengah("======================================================================================", HIJAU_NEON);
    cetakTengah("Langsung Tekan Enter jika tidak ingin mengubah bagian ini");
    cout << setw(25) << setfill(' ') << "" << "Masukan Nama Penulis Baru   : ";
    getline (cin, daftarBuku[index].penulis);

    if (daftarBuku[index].penulis.empty()){
        daftarBuku[index].penulis = Sebelumnya;
    } else {
        perubahan++;
    }

string inputTahun;

do {
    ulang_edit = false;
    Sebelumnya_angka = daftarBuku[index].tahunTerbit;
    
    bersihkanLayar();
    tampilkanHeaderTengah();
    cetakTengah("======================================================================================", HIJAU_NEON);
    cetakTengah("Menekan ENTER atau memasukkan karakter bukan angka tidak akan mengubah bagian ini");
    
    cout << setw(25) << setfill(' ') << "" << "Masukan Tahun Terbit Baru   : ";
    getline(cin, inputTahun);

    if (inputTahun.empty()) {
        daftarBuku[index].tahunTerbit = Sebelumnya_angka;
    } 
    else {
        stringstream ss(inputTahun);
        if (ss >> daftarBuku[index].tahunTerbit) {
            if (daftarBuku[index].tahunTerbit < 1900 || daftarBuku[index].tahunTerbit > 2026) {
                cout << "\n";
                cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
                cetakTengah("[ERROR] Tahun Tidak Valid!", MERAH_CERAH);
                daftarBuku[index].tahunTerbit = Sebelumnya_angka;
                ulang_edit = true;
                tungguEnter();
            } else {
                perubahan++;
            }
            
        } else {
            daftarBuku[index].tahunTerbit = Sebelumnya_angka;
        }
    }
} while (ulang_edit);

    Sebelumnya = daftarBuku[index].idBuku;
    bersihkanLayar();
    tampilkanHeaderTengah();
    cetakTengah("======================================================================================", HIJAU_NEON);
    cetakTengah("Langsung Tekan Enter jika tidak ingin mengubah bagian ini");
    cout << setw(25) << setfill(' ') << "" << "Masukan id Buku Baru   : ";
    getline (cin, daftarBuku[index].idBuku);

    if (daftarBuku[index].idBuku.empty()){
        daftarBuku[index].idBuku = Sebelumnya;
    } else {
        perubahan++;
    }

    string inputJumlah;

Sebelumnya_angka = daftarBuku[index].jumlahBuku;

bersihkanLayar();
tampilkanHeaderTengah();
cetakTengah("======================================================================================", HIJAU_NEON);
cetakTengah("Menekan ENTER, Angka 0, atau Bukan Angka akan membuat bagian ini tidak berubah");

cout << setw(25) << setfill(' ') << "" << "Masukan Jumlah Baru   : ";
getline(cin, inputJumlah);

if (inputJumlah.empty()) {
    daftarBuku[index].jumlahBuku = Sebelumnya_angka;
} 
else {
    stringstream ss(inputJumlah);
    if (ss >> daftarBuku[index].jumlahBuku) {
        if (daftarBuku[index].jumlahBuku <= 0) {
            daftarBuku[index].jumlahBuku = Sebelumnya_angka;
        } else {
            perubahan++; 
        }
        
    } else {
        daftarBuku[index].jumlahBuku = Sebelumnya_angka;
    }
}

    bersihkanLayar();
    cetakTengah("======================================================================================");
    cetakTengah("Buku Berhasil Diedit!", HIJAU_NEON);
    cout << setw(30) << perubahan << " Perubahan Berhasil Diterapkan" << endl;
    cetakTengah("======================================================================================");
    tungguEnter();
    cetakTengah("Tekan ENTER Untuk Melanjutkan");
    bersihkanLayar();
}


void subEdit(){
    bool ulang;
    char pilihan;
    int idx = 0;

    do{
        ulang = false;
        bersihkanLayar();
        tampilkanHeaderTengah();
        cetakTengah("=== EDIT BUKU ===", MAGENTA_CERAH);
        cout << "\n\n";

        for (int i = 0; i < jumlahBuku; i++)
        {
            cout << setw(25) << setfill(' ') << "" << "[" << i+1 << "] " << daftarBuku[i].judul << endl;
        }
        cout << setw(25) << setfill(' ') << "" << "[0] Keluar" << endl;
        cout << "\n";
        cetakTengah("======================================================================================", HIJAU_NEON);

        cout << setw(35) << setfill(' ') << "" << "Pilih Buku untuk diedit : ";
        cin >> idx;

        if (cin.fail()) {
            ulang = true;
            cetakTengah("[ERROR] INPUT Tidak valid");
            cetakTengah("<<<< Tekan ENTER untuk mengulang >>>>", KUNING_EMAS);
            cin.clear();
            cin.ignore(1000,'\n');
            tungguEnter();
            continue;

        } else if (idx < 0 || idx > jumlahBuku){
            cetakTengah("[ERROR] Buku Tidak ditemukan!");
            cetakTengah("<<<< Tekan ENTER untuk mengulang >>>>", KUNING_EMAS);
            ulang = true;
            tungguEnter(); 
            continue;
        }

        if (idx == 0){return;}

        index = idx-1;
        
        do{
            ulang = false;
            bersihkanLayar();
            tampilkanHeaderTengah();
            cetakTengah("======================================================================================", HIJAU_NEON);
            cout << setw(30) << setfill(' ') << "" << "Judul        : " <<  daftarBuku[index].judul << endl;
            cout << setw(30) << setfill(' ') << "" << "Penulis      : " <<  daftarBuku[index].penulis << endl;
            cout << setw(30) << setfill(' ') << "" << "Tahun Terbit : " <<  daftarBuku[index].tahunTerbit << endl;
            cout << setw(30) << setfill(' ') << "" << "Id           : " <<  daftarBuku[index].idBuku << endl;
            cout << setw(30) << setfill(' ') << "" << "Jumlah Buku  : " <<  daftarBuku[index].jumlahBuku << endl;
            cetakTengah("======================================================================================", HIJAU_NEON);
            cout << "\n\n";

            cetakTengah("Apakah anda yakin ingin mengedit informasi buku ini? (y/n)");
            cout << "\n\n";
            cetakTengah("======================================================================================", HIJAU_NEON);
            cout << "\n\n";
            cout << setw(25) << setfill(' ') << "" << "Pilih Menu     : ";
            cin >> pilihan;

            switch (pilihan)
            {
            case 'y':
                cin.ignore();
                editBuku();
                break;
            case 'Y':
                cin.ignore();
                editBuku();
                break;
            case 'n':
                break;
            case 'N':
                break;
            default:
                cetakTengah("[ERROR] INPUT Tidak valid");
                cetakTengah("<<<< Tekan ENTER untuk mengulang >>>>", KUNING_EMAS);
                ulang = true;
                break;
            }



        } while (ulang);
    }while(ulang);
    
    
}

void TambahBuku() {
    string judulInput, penulisInput, idInput;
    int tahunInput, banyakInput;
    
    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();
        cetakTengah("=== TAMBAH BUKU BARU ===", MAGENTA_CERAH);
        cout << "\n\n";
        
        if (jumlahBuku >= MAX_BUKU) {
            cetakTengah("[ ERROR: Kapasitas buku memori sistem penuh! ]", MERAH_CERAH);
            cetakTengah("<<<< Tekan ENTER untuk kembali >>>>", KUNING_EMAS);
            tungguEnter();
            return;
        }
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Judul Buku       : ";
        getline(cin, judulInput);
        if (judulInput.empty()){
            cout << "\n";
            cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
            cetakTengah("[ ERROR:  Judul Buku tidak boleh kosong! ]", MERAH_CERAH);
            cetakTengah("Tekan ENTER untuk mengulangi pengisian...", KUNING_EMAS);
            tungguEnter();
            continue;
        }
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Nama Penulis     : ";
        getline(cin, penulisInput);
        if (penulisInput.empty()){
            cout << "\n";
            cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
            cetakTengah("[ ERROR:  Penulis Buku tidak boleh kosong! ]", MERAH_CERAH);
            cetakTengah("Tekan ENTER untuk mengulangi pengisian...", KUNING_EMAS);
            tungguEnter();
            continue;
        }
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Tahun Terbit     : ";
        cin >> tahunInput;
        if (tahunInput < 1900 || tahunInput > 2026){
            cin.ignore();
            cout << "\n";
            cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
            cetakTengah("[ ERROR:  Tahun Terbit tidak valid! ]", MERAH_CERAH);
            cetakTengah("Tekan ENTER untuk mengulangi pengisian...", KUNING_EMAS);
            tungguEnter();
            continue;
        }

        cout << setw(25) << setfill(' ') << "" << "Masukkan id Buku          : ";
        cin >> idInput;
        if (idInput.length() < 4|| idInput.length() > 4 ){
            cin.ignore();
            cout << "\n";
            cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
            cetakTengah("[ ERROR:  Id Buku harus terdiri dari 4 digit ]", MERAH_CERAH);
            cetakTengah("Tekan ENTER untuk mengulangi pengisian...", KUNING_EMAS);
            tungguEnter();
            continue;
        }

        cout << setw(25) << setfill(' ') << "" << "Masukkan jumlah Buku      : ";
        cin >> banyakInput;
        if (banyakInput <= 0){
            cin.ignore();
            cout << "\n";
            cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
            cetakTengah("[ ERROR:  Jumlah Buku tidak boleh kosong atau kurang! ]", MERAH_CERAH);
            cetakTengah("Tekan ENTER untuk mengulangi pengisian...", KUNING_EMAS);
            tungguEnter();
            continue;
        }
        cin.ignore();
        
        bool bukuKembar = false;
        for (int i = 0; i < jumlahBuku; i++) {
            if (daftarBuku[i].idBuku == idInput) {
                bukuKembar = true;
                break;
            }
        }

        
        if (bukuKembar) {
            cetakTengah("[ ERROR: id '" + idInput + "' sudah ada! ]", MERAH_CERAH);
            cetakTengah("Silakan tekan ENTER untuk kembali.", KUNING_EMAS);
            tungguEnter();
            return;
        }
        
        daftarBuku[jumlahBuku].judul           = judulInput;
        daftarBuku[jumlahBuku].penulis         = penulisInput;
        daftarBuku[jumlahBuku].tahunTerbit     = tahunInput;
        daftarBuku[jumlahBuku].idBuku          = idInput;
        daftarBuku[jumlahBuku].jumlahBuku      = banyakInput;
        daftarBuku[jumlahBuku].tersedia        = true;
        daftarBuku[jumlahBuku].rating          = 0;
        daftarBuku[jumlahBuku].jumlahPerating  = 0;
        daftarBuku[jumlahBuku].totalSkorRating = 0;
        jumlahBuku++;
        
        cout << "\n";
        cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
        cetakTengah("[ BUKU BERHASIL DITAMBAHKAN! ]", HIJAU_NEON);
        cout << "\n";
        cetakTengah("<<<< Tekan ENTER untuk kembali ke Menu Utama >>>>", HIJAU_NEON);
        tungguEnter();
        bersihkanLayar();
        return; 
    }
}
void HapusBuku(){
    string idCari;
    bool ditemukan = false;

    bersihkanLayar();
    tampilkanHeaderTengah();

    cetakTengah("=== HAPUS BUKU ===", CYAN_NEON);
    cout << "\n";

    if(jumlahBuku == 0){
        cetakTengah("[ BELUM ADA BUKU TERDAFTAR ]", MERAH_CERAH);
        cin.ignore();
        tungguEnter();
        return;
    }

    cout << setw(20) << "" << "DAFTAR BUKU\n\n";
    for(int i = 0; i < jumlahBuku; i++){
        cout << setw(20) << "" << "ID : " << daftarBuku[i].idBuku << " | Judul : " << daftarBuku[i].judul << endl;
    }
    cout << setw(25) << "" << "Masukkan ID Buku : ";
    getline(cin, idCari);

    for(int i = 0; i < jumlahBuku; i++){

        if(daftarBuku[i].idBuku == idCari){

            ditemukan = true;

            for(int j = i; j < jumlahBuku - 1; j++){
                daftarBuku[j] = daftarBuku[j + 1];
            }
            jumlahBuku--;
            cetakTengah("[ BUKU BERHASIL DIHAPUS ]", HIJAU_NEON);
            cin.ignore();
            tungguEnter();
            break;
        }
    }

    if(!ditemukan){
        cetakTengah("[ BUKU TIDAK DITEMUKAN ]", MERAH_CERAH);
    }

    tungguEnter();

}

void KelolaDenda(){
	
	while (true){
		bersihkanLayar();
    tampilkanHeaderTengah();

    cetakTengah("=== MANAJEMEN DENDA PERPUSTAKAAN ===", CYAN_NEON);
    cout << "\n";

    int totalDenda = 0;
    int nomor = 1;

    cout << left
     << setw(5)  << "No"
     << setw(15) << "Username"
     << setw(12) << "ID Buku"
     << setw(25) << "Judul"
     << setw(10) << "Telat"
     << setw(15) << "Denda"
     << setw(15) << "Status"
     << endl;

    cout << string(80,'-') << endl;

    for(int i=0; i<jumlahPinjam; i++){

        if(daftarPinjam[i].denda > 0){

            cout << setw(5)  << nomor++
     << setw(15) << daftarPinjam[i].username
     << setw(12) << daftarPinjam[i].idBuku
     << setw(25) << daftarPinjam[i].judulBuku
     << setw(10) << daftarPinjam[i].hariTelat
     << setw(15) << ("Rp " + to_string(daftarPinjam[i].denda));

            if(daftarPinjam[i].sudahDibayar)
                cout << setw(15) << "LUNAS";
            else
                cout << setw(15) << "BELUM";

            cout << endl;

            if(!daftarPinjam[i].sudahDibayar)
                totalDenda += daftarPinjam[i].denda;
        }
    }

    cout << "\n";
    cout << "Total Denda Aktif : Rp " << totalDenda << endl;

    cout << "\n";
    cout << "1. Tandai Denda Lunas\n";
    cout << "0. Kembali\n";

    int pilih;
    cout << "Pilih : ";
    cin >> pilih;
    cin.ignore();
    
        if(pilih == 1){

        string user;

        cout << "\nMasukkan Username : ";
        getline(cin,user);

        bool ditemukan = false;

        for(int i=0; i<jumlahPinjam; i++){

            if(daftarPinjam[i].username == user &&
               daftarPinjam[i].denda > 0){

                daftarPinjam[i].sudahDibayar = true;

                cetakTengah("[ DENDA BERHASIL DILUNASI ]",
                            HIJAU_NEON);

                ditemukan = true;
                break;
            }
        }

        if(!ditemukan){

            cetakTengah("[ DATA TIDAK DITEMUKAN ]",
                        MERAH_CERAH);
        }
    }

    tungguEnter();
	}
}

void verifikasiPeminjaman(){
	while (true){
		bersihkanLayar();
    tampilkanHeaderTengah();

    cetakTengah("=== VERIFIKASI PEMINJAMAN ===", CYAN_NEON);

    cout << endl;
    if(jumlahPinjam == 0){
        cetakTengah("[ BELUM ADA PENGAJUAN ]", MERAH_CERAH);
        tungguEnter();
        return;
    }

    for(int i = 0; i < jumlahPinjam; i++){
        cout << i + 1 << ". " << daftarPinjam[i].username << " | " << daftarPinjam[i].judulBuku << endl;
    }
    int pilihan;

	cout << "\nPilih Pengajuan : ";
	cin >> pilihan;
	cin.ignore();
	if(pilihan < 1 || pilihan > jumlahPinjam){
	    cetakTengah("[ PILIHAN TIDAK VALID ]", MERAH_CERAH);
	    tungguEnter();
	    return;
	}
	
	int aksi;
	cout << "\n1. Setujui";
	cout << "\n2. Tolak";
	cout << "\nPilih : ";
	cin >> aksi;
	cin.ignore();
	if(aksi == 1){
    	daftarPinjam[pilihan - 1].disetujui = true;
	    for(int i = 0; i < jumlahBuku; i++){
	        if(daftarBuku[i].idBuku == daftarPinjam[pilihan - 1].idBuku){
	            daftarBuku[i].jumlahBuku--;
	            break;
	        }
	    }
	    cetakTengah("[ PEMINJAMAN DISETUJUI ]", HIJAU_NEON);
	}
	else if(aksi == 2){
	    for(int i = pilihan - 1; i < jumlahPinjam - 1; i++){
	        daftarPinjam[i] = daftarPinjam[i + 1];
	    }
	    jumlahPinjam--;
	    cetakTengah("[ PEMINJAMAN DITOLAK ]", MERAH_CERAH);
	}
	else{
	    cetakTengah("[ AKSI TIDAK VALID ]", MERAH_CERAH);
	}

    tungguEnter();
	}
}

void dashboardAdmin() {
    bool ulang;
    int pilihan;

    do{
        tampilkanHeaderTengah();
        cetakTengah("[ SUCCESS: WELCOME TO ADMIN DASHBOARD ]", HIJAU_NEON);
        cout << "\n\n";
        cetakTengah("Halo Pustakawan! Modul manajemen buku Kelompok 19 siap dijalankan di sini..."); 
        cout << "\n\n";
        cetakTengah("1. TAMBAH BUKU", CYAN_NEON);
        cetakTengah("2. EDIT BUKU", CYAN_NEON);  
        cetakTengah("3. HAPUS BUKU", CYAN_NEON);  
        cetakTengah("4. MENGELOLA DENDA", CYAN_NEON);  
        cetakTengah("5. VERIFIKASI PEMINJAMAN", CYAN_NEON);  
        cetakTengah("6. VERIFIKASI PEMBATALAN", CYAN_NEON);  
        cetakTengah("0. LOG OUT", CYAN_NEON);   
        cout << "\n";
        cetakTengah("======================================================================================", HIJAU_NEON);
  
        cout << setw(35) << setfill(' ') << "" << "Pilih Menu (0-6) : ";
        cin >> pilihan;
        ulang = false;
        if (cin.fail()){
            cetakTengah("[ ERROR: INPUT tidak valid! ]", MERAH_CERAH);
            cin.clear();
            cin.ignore(1000,'\n');
            continue;
        }
        
        switch (pilihan)
        {
        case 1:
            cin.ignore();
            TambahBuku();
            ulang = true;
            break;

        case 2:
            cin.ignore();
            subEdit();
            ulang = true;
            break;
            
        case 3:
		    cin.ignore();
            HapusBuku();
            ulang = true;
            break;
		
		case 4:
		    KelolaDenda();
		    ulang = true;
		    break;
		
		case 5:
		    cin.ignore();
		    verifikasiPeminjaman();
		    ulang = true;
		    break;
        
        default:
            break;
        }
        
    }while (ulang);
    cout << "\n\n";
    cetakTengah("<<<< Tekan ENTER untuk Log Out >>>>", MERAH_CERAH);
    tungguEnter();
}

void PinjamBuku(){
    string idCari;
    bool ditemukan = false;

    bersihkanLayar();
    tampilkanHeaderTengah();

    cetakTengah("=== DAFTAR BUKU ===", CYAN_NEON);
    cout << "\n";

    for(int i = 0; i < jumlahBuku; i++){
        cout << setw(20) << "" << "ID : " << daftarBuku[i].idBuku << " | Judul : " << daftarBuku[i].judul << " | Stok : " << daftarBuku[i].jumlahBuku << endl;
    }

    cout << "\n";
    cout << setw(25) << "" << "Masukkan ID Buku : ";
    getline(cin, idCari);

    for(int i = 0; i < jumlahBuku; i++){

        if(daftarBuku[i].idBuku == idCari){

            ditemukan = true;

            if(daftarBuku[i].jumlahBuku <= 0){
                cetakTengah("[ STOK BUKU HABIS ]", MERAH_CERAH);
                tungguEnter();
                return;
            }
            
            if(jumlahPinjam >= MAX_PINJAM){
			    cetakTengah("[ DATABASE PEMINJAMAN PENUH ]", MERAH_CERAH);
			    tungguEnter();
			    return;
			}
			
			time_t sekarang = time(0);
			tm *waktu = localtime(&sekarang);	
			
			daftarPinjam[jumlahPinjam].hariPinjam  = waktu->tm_mday;
			daftarPinjam[jumlahPinjam].bulanPinjam = waktu->tm_mon + 1;
			daftarPinjam[jumlahPinjam].tahunPinjam = waktu->tm_year + 1900;

            daftarPinjam[jumlahPinjam].username = userAktif->username;
            daftarPinjam[jumlahPinjam].idBuku = daftarBuku[i].idBuku;
            daftarPinjam[jumlahPinjam].judulBuku = daftarBuku[i].judul;
            daftarPinjam[jumlahPinjam].disetujui = false;
            daftarPinjam[jumlahPinjam].sudahKembali = false;
			daftarPinjam[jumlahPinjam].hariTelat = 0;
			daftarPinjam[jumlahPinjam].denda = 0;
			daftarPinjam[jumlahPinjam].sudahDibayar = false;
            
            daftarBuku[i].jumlahDipinjam++;
            daftarBuku[i].jumlahBuku--; // stok berkurang

            jumlahPinjam++;
            

            cetakTengah("[ PENGAJUAN PEMINJAMAN BERHASIL ]", HIJAU_NEON);
            
            cout << "\n";
			cout << setw(25) << "" << "Nama Peminjam : " << userAktif->namaLengkap << endl;
			cout << setw(25) << "" << "ID Buku       : " << daftarBuku[i].idBuku << endl;
			cout << setw(25) << "" << "Judul Buku    : " << daftarBuku[i].judul << endl;   
			cout << setw(25) << "" << "Tanggal Pinjam : " << waktu->tm_mday << "/" << waktu->tm_mon + 1 << "/" << waktu->tm_year + 1900<< endl;
			     
            tungguEnter();
            return;
        }
    }

    if(!ditemukan){
        cetakTengah("[ BUKU TIDAK DITEMUKAN ]", MERAH_CERAH);
        tungguEnter();
    }
}

void CariBuku(){

    string cari;

    bersihkanLayar();
    tampilkanHeaderTengah();

    cetakTengah("=== PENCARIAN KOLEKSI BUKU ===", CYAN_NEON);

    cout << "\n";
    cout << setw(25) << "" << "Masukkan Judul Buku : ";
    getline(cin,cari);

    for(int i=0;i<jumlahBuku;i++){

        if(daftarBuku[i].judul == cari){

            cout << "\n";
            cetakTengah("[ BUKU DITEMUKAN ]", HIJAU_NEON);

            cout << "\n";
            cout << setw(25) << "" << "ID Buku      : " << daftarBuku[i].idBuku << endl;
            cout << setw(25) << "" << "Judul Buku   : " << daftarBuku[i].judul << endl;
            cout << setw(25) << "" << "Penulis      : " << daftarBuku[i].penulis << endl;
            cout << setw(25) << "" << "Tahun Terbit : " << daftarBuku[i].tahunTerbit << endl;
            cout << setw(25) << "" << "Stok Buku    : " << daftarBuku[i].jumlahBuku << endl;

            tungguEnter();
            return;
        }
    }

    cetakTengah("[ BUKU TIDAK DITEMUKAN ]", MERAH_CERAH);
    tungguEnter();
}

void PengembalianBuku(){

    string id;

    bersihkanLayar();
    tampilkanHeaderTengah();

    cetakTengah("=== PENGEMBALIAN BUKU ===", CYAN_NEON);

	cout << "\n";
	
	bool ada = false;
	
	cout << setw(20) << "" << "BUKU YANG SEDANG DIPINJAM\n\n";
	
	for(int i=0;i<jumlahPinjam;i++){
	
	    if(daftarPinjam[i].username == userAktif->username &&
   daftarPinjam[i].sudahKembali == false){
	
	        ada = true;
	
	        cout << setw(20) << ""
	             << "ID : "
	             << daftarPinjam[i].idBuku
	             << " | "
	             << daftarPinjam[i].judulBuku
	             << endl;
	    }
	}
	
	if(!ada){
	
	    cetakTengah("[ TIDAK ADA BUKU YANG DIPINJAM ]", MERAH_CERAH);
	
	    tungguEnter();
	    return;
	}
	
	cout << "\n";
	
	cout << setw(25) << "" << "Masukkan ID Buku yang dikembalikan : ";
	
	getline(cin,id);
	
	bool pernahPinjam = false;
	int indexPinjam = -1;
	
	for(int j=0; j<jumlahPinjam; j++){
	
	    if(daftarPinjam[j].username == userAktif->username &&
	       daftarPinjam[j].idBuku == id &&
	       daftarPinjam[j].sudahKembali == false){
	
	        pernahPinjam = true;
	        indexPinjam = j;
	        break;
	    }
	}
	
	if(!pernahPinjam){
	
	    cetakTengah("[ ANDA TIDAK MEMINJAM BUKU INI ]", MERAH_CERAH);
	    tungguEnter();
	    return;
	}

    bool ditemukan = false;

    for(int i=0;i<jumlahBuku;i++){

        if(daftarBuku[i].idBuku == id){

	    ditemukan = true;
	
	    int stokSebelum = daftarBuku[i].jumlahBuku;
	    
	    time_t sekarang = time(0);
		tm *waktu = localtime(&sekarang);
	
	    daftarBuku[i].jumlahBuku++;
	
		cout << "\n";
		cetakTengah("[ PENGEMBALIAN BERHASIL ]", HIJAU_NEON);
	
	    cout << "\n";
	    cout << setw(25) << "" << "ID Buku          : "
	         << daftarBuku[i].idBuku << endl;
	
	    cout << setw(25) << "" << "Judul Buku       : "
	         << daftarBuku[i].judul << endl;
	
	    cout << setw(25) << "" << "Penulis          : "
	         << daftarBuku[i].penulis << endl;
	         
	    cout << setw(25) << "" << "Status           : " << "Berhasil Dikembalikan" << endl;
		
		for(int j=0; j<jumlahPinjam; j++){
		
		    if(daftarPinjam[j].username == userAktif->username &&
		       daftarPinjam[j].idBuku == id){
		
		        cout << setw(25) << "" << "Tanggal Pinjam   : "
		             << daftarPinjam[j].hariPinjam << "/"
		             << daftarPinjam[j].bulanPinjam << "/"
		             << daftarPinjam[j].tahunPinjam
		             << endl;
		
		        break;
		    }
		}
		
		cout << setw(25) << "" << "Tanggal Kembali  : " << waktu->tm_mday << "/" << waktu->tm_mon + 1 << "/" << waktu->tm_year + 1900 << endl;
	    
	    int lamaPinjam;

		cout << "\n";
		
		lamaPinjam =
    (waktu->tm_year + 1900 - daftarPinjam[indexPinjam].tahunPinjam) * 365 +
    (waktu->tm_mon + 1 - daftarPinjam[indexPinjam].bulanPinjam) * 30 +
    (waktu->tm_mday - daftarPinjam[indexPinjam].hariPinjam);

		int telat = lamaPinjam - 7;
		
		if(telat < 0)
		    telat = 0;
    
    cout << setw(25) << ""
     << "Lama Peminjaman  : "
     << lamaPinjam
     << " Hari" << endl;
		
		if(telat < 0)
		    telat = 0;
		
		daftarPinjam[indexPinjam].hariTelat = telat;
		
		if(telat > 0){

	    daftarPinjam[indexPinjam].denda = telat * 2000;
	    daftarPinjam[indexPinjam].sudahDibayar = false;

		}else{
		
		    daftarPinjam[indexPinjam].denda = 0;
		    daftarPinjam[indexPinjam].sudahDibayar = true;
		}
		
		daftarPinjam[indexPinjam].sudahKembali = true;
	}
    }

    if(!ditemukan){
        cetakTengah("[ ID BUKU TIDAK DITEMUKAN ]", MERAH_CERAH);
    }

    tungguEnter();
}

void BukuPopuler(){

    bersihkanLayar();
    tampilkanHeaderTengah();

    cetakTengah("=== REKOMENDASI BUKU POPULER ===", MAGENTA_CERAH);
    cout << "\n";

    if(jumlahBuku == 0){
        cetakTengah("[ INFO: Belum ada buku tersedia di sistem. ]", KUNING_EMAS);
        cout << "\n";
        tungguEnter();
        return;
    }

    int urutan[MAX_BUKU];
    for(int i = 0; i < jumlahBuku; i++) urutan[i] = i;

    // Skor = rating (60%) + jumlah dipinjam (40%), diurutkan descending
    for(int i = 0; i < jumlahBuku - 1; i++){
        for(int j = 0; j < jumlahBuku - i - 1; j++){

            float skorJ     = (daftarBuku[urutan[j]].rating       * 0.6f)
                             + (daftarBuku[urutan[j]].jumlahDipinjam * 0.4f);
            float skorJNext = (daftarBuku[urutan[j+1]].rating       * 0.6f)
                             + (daftarBuku[urutan[j+1]].jumlahDipinjam * 0.4f);

            if(skorJ < skorJNext){
                int tmp     = urutan[j];
                urutan[j]   = urutan[j+1];
                urutan[j+1] = tmp;
            }
        }
    }

    int tampil = (jumlahBuku < 5) ? jumlahBuku : 5;

    cout << left
         << setw(5)  << "Rank"
         << setw(25) << "Judul"
         << setw(18) << "Penulis"
         << setw(10) << "Rating"
         << setw(15) << "Dipinjam"
         << endl;

    cout << string(70,'-') << endl;

    for(int i = 0; i < tampil; i++){

        int idx = urutan[i];
        string warna = (i == 0) ? KUNING_EMAS : (i == 1) ? CYAN_NEON : (i == 2) ? MAGENTA_CERAH : RESET;

        cout << warna
             << left
             << setw(5)  << ("#" + to_string(i+1))
             << setw(25) << daftarBuku[idx].judul.substr(0, 23)
             << setw(18) << daftarBuku[idx].penulis.substr(0, 16)
             << fixed << setprecision(1)
             << setw(10) << daftarBuku[idx].rating
             << setw(15) << daftarBuku[idx].jumlahDipinjam
             << RESET << endl;
    }

    cout << "\n";

    tungguEnter();
}

void dashboardUser(AkunUser* user) {
	int pilihan;
	do{
		bersihkanLayar();
	    tampilkanHeaderTengah();
	    cetakTengah("[ SUCCESS: WELCOME TO STUDENT DASHBOARD ]", HIJAU_NEON);
	    cout << "\n\n";
	    
	    cetakTengah("Selamat Datang, " + user->namaLengkap + "!", KUNING_EMAS);
	    cetakTengah("Username Anda : " + user->username, CYAN_NEON);
	    cout << "\n";
	    cetakTengah("Modul peminjaman buku perpustakaan pintar siap digunakan...", RESET);
	    cout << "\n\n";
	  	cetakTengah("1. CARI BUKU", CYAN_NEON);
		cetakTengah("2. LIHAT BUKU POPULER", CYAN_NEON);
		cetakTengah("3. PEMINJAMAN BUKU", CYAN_NEON);
		cetakTengah("4. PENGEMBALIAN BUKU", CYAN_NEON);
		cetakTengah("5. BERI RATING BUKU", CYAN_NEON);
		cetakTengah("0. LOGOUT", CYAN_NEON);
		
		cout << "\n";
		cetakTengah("======================================================================================", HIJAU_NEON);
		
		cout << setw(35) << "" << "Pilih Menu : ";
		cin >> pilihan;
		cin.ignore();
		
		switch(pilihan){
		
		    case 1:
		        CariBuku();
		        break;
		
		    case 2:
		        BukuPopuler();
		        break;
		
		    case 3:
		        PinjamBuku();
		        break;
		
		    case 4:
		        PengembalianBuku();
		        break;
		
		    case 5:
		        ratingBuku();
		        break;
	
		    case 0:
		        return;
		}
			    cetakTengah("<<<< Tekan ENTER untuk Log Out >>>>", MERAH_CERAH);
			    tungguEnter();
				
			}while(pilihan != 0);
		}

// ==========================================
// 1. IMPLEMENTASI STATEMENT CONTROL & LOOPING
// ==========================================
void formLogin(string role) {
    string username, password;
    
    while (true) { 
        bersihkanLayar();
        tampilkanHeaderTengah();
        
        if (role == "ADMIN") {
            cetakTengah("=== FORM LOGIN: ADMINISTRATOR SYSTEM ===", MAGENTA_CERAH);
        } else {
            cetakTengah("=== FORM LOGIN: STUDENT USER ===", CYAN_NEON);
        }
        cout << "\n\n";

        cout << setw(28) << setfill(' ') << "" << "Masukkan Username : ";
        getline(cin, username);
        
        cout << setw(28) << setfill(' ') << "" << "Masukkan Password : ";
        getline(cin, password); // passwordnya tampilin aja jangan di sensor
        
        cout << "\n";
        cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);

        if (username.empty() || password.empty()) {
            cetakTengah("[ ERROR: Username atau Password tidak boleh kosong! ]", MERAH_CERAH);
            cetakTengah("Tekan ENTER untuk mengulangi...", KUNING_EMAS);
            tungguEnter();
            continue; 
        }
        
        if (role == "ADMIN") {
            if (username == "admin19" && password == "pustaka19") {
                cetakTengah("[ LOGIN BERHASIL - ACCESS GRANTED ]", HIJAU_NEON);
                tungguEnter();
                dashboardAdmin();
                break; 
            } else {
                cetakTengah("[ ERROR: Username atau Password Admin salah! ]", MERAH_CERAH);
                cetakTengah("Ketik [1] Coba Lagi | [2] Kembali ke Menu : ", KUNING_EMAS);
                string opsi;
                getline(cin, opsi);
                if (opsi == "2") break;
            }
        } 
        else if (role == "USER") {
            bool ditemukan = false;
            
            for (int i = 0; i < jumlahUser; i++) {
                if (daftarUser[i].username == username && daftarUser[i].password == password) {
                    ditemukan = true;
                    userAktif = &daftarUser[i]; 
                    break;
                }
            }
            
            if (ditemukan) {
                cetakTengah("[ LOGIN BERHASIL - ACCESS GRANTED ]", HIJAU_NEON);
                tungguEnter();
                dashboardUser(userAktif); 
                userAktif = nullptr;      
                break;
            } else {
                cetakTengah("[ ERROR: Username atau Password salah / belum terdaftar! ]", MERAH_CERAH);
                cetakTengah("Ketik [1] Coba Lagi | [2] Kembali ke Menu : ", KUNING_EMAS);
                string opsi;
                getline(cin, opsi);
                if (opsi == "2") break;
            }
        }
    }
}

void halamanCreateAccount() {
    string namaInput, userInput, passInput;
    
    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();
        cetakTengah("=== REGISTRATION PORTAL: CREATE NEW USER ACCOUNT ===", MAGENTA_CERAH);
        cout << "\n\n";
        
        if (jumlahUser >= MAX_USER) {
            cetakTengah("[ ERROR: Kapasitas pendaftaran memori sistem penuh! ]", MERAH_CERAH);
            cetakTengah("<<<< Tekan ENTER untuk kembali >>>>", KUNING_EMAS);
            tungguEnter();
            break;
        }
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Nama Lengkap : ";
        getline(cin, namaInput);
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Username     : ";
        getline(cin, userInput);
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Password     : ";
        getline(cin, passInput); // Pengganti sensor password
        
        cout << "\n";
        cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
        
        if (namaInput.empty() || userInput.empty() || passInput.empty()) {
            cetakTengah("[ ERROR: Semua kolom pendaftaran wajib diisi! ]", MERAH_CERAH);
            cetakTengah("Tekan ENTER untuk mengulangi pengisian...", KUNING_EMAS);
            tungguEnter();
            continue; 
        }
        
        bool usernameKembar = false;
        for (int i = 0; i < jumlahUser; i++) {
            if (daftarUser[i].username == userInput) {
                usernameKembar = true;
                break;
            }
        }
        
        if (usernameKembar) {
            cetakTengah("[ ERROR: Username '" + userInput + "' sudah terpakai! ]", MERAH_CERAH);
            cetakTengah("Silakan tekan ENTER untuk mencoba username lain.", KUNING_EMAS);
            tungguEnter();
            continue;
        }
        
        daftarUser[jumlahUser].namaLengkap = namaInput;
        daftarUser[jumlahUser].username    = userInput;
        daftarUser[jumlahUser].password    = passInput;
        
        jumlahUser++; 
        
        cetakTengah("[ REGISTRASI BERHASIL! Akun Anda sukses didaftarkan ]", HIJAU_NEON);
        cetakTengah("Silakan kembali ke menu Login untuk menguji akun.", KUNING_EMAS);
        cout << "\n";
        cetakTengah("<<<< Tekan ENTER untuk kembali ke Menu Utama >>>>", HIJAU_NEON);
        tungguEnter();
        break; 
    }
}

void subMenuLogin() {
    string pilihanSub;

    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();

        cetakTengah("[ LOGIN SELECTION PORTAL ]", MAGENTA_CERAH);
        cout << "\n";
        
        cetakTengah("1. LOGIN SEBAGAI ADMIN (PUSTAKAWAN)", CYAN_NEON);
        cetakTengah("2. LOGIN SEBAGAI USER (MAHASISWA)", CYAN_NEON);
        cetakTengah("3. KEMBALI KE MENU UTAMA", CYAN_NEON);
        
        cout << "\n";
        cetakTengah("======================================================================================", HIJAU_NEON);
        
        cout << setw(35) << setfill(' ') << "" << "Pilih menu (1/2/3) : ";
        getline(cin, pilihanSub);

        if (pilihanSub == "1") {
            formLogin("ADMIN");
        } else if (pilihanSub == "2") {
            formLogin("USER");
        } else if (pilihanSub == "3") {
            return; 
        } else {
            cetakTengah("[!] Pilihan tidak valid, tekan ENTER untuk mengulangi.", MERAH_CERAH);
            tungguEnter();
        }
    }
}





int main() {
    string pilihanUtama;

    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();
        
        cetakTengah("[ MAIN CONTROL PANEL ]", MAGENTA_CERAH);
        cout << "\n";

        cetakTengah("1. LOGIN SYSTEM", CYAN_NEON);
        cetakTengah("2. CREATE ACCOUNT", CYAN_NEON);
        cetakTengah("3. EXIT PROGRAM", CYAN_NEON);
        
        cout << "\n";
        cetakTengah("======================================================================================", HIJAU_NEON);

        cout << setw(35) << setfill(' ') << "" << "Pilih menu (1/2/3) : ";
        getline(cin, pilihanUtama);

        if (cin.fail()){
            cetakTengah("[!] Hanya masukan angka, tekan ENTER untuk mengulangi.", MERAH_CERAH);
            cin.clear();
            cin.ignore(1000, '\n');
            tungguEnter();
        }

        if (pilihanUtama == "1") {
            subMenuLogin(); 
        } else if (pilihanUtama == "2") {
            halamanCreateAccount(); 
        } else if (pilihanUtama == "3") {
            bersihkanLayar();
            cout << "\n\n\n";
            cetakTengah("+--------------------------------------------------------+", HIJAU_NEON);
            cetakTengah("|    TERIMA KASIH TELAH MENGGUNAKAN LAYANAN SMART LIB!   |", HIJAU_NEON);
            cetakTengah("|             SALAM HANGAT DARI KELOMPOK 19              |", HIJAU_NEON);
            cetakTengah("+--------------------------------------------------------+", HIJAU_NEON);
            cout << "\n\n";
        
            cetakTengah("[ Tekan ENTER untuk menutup terminal ]", MAGENTA_CERAH);
            cin.ignore();
            
            exit(0); 
        } else {
            cetakTengah("[!] Pilihan tidak valid, tekan ENTER untuk mengulangi.", MERAH_CERAH);
            tungguEnter();
        }
    }
    return 0;
}
