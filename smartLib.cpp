#include <iostream>
#include <string>
#include <limits>
#include <iomanip> 
#include <conio.h> 
#include <cstdlib> 

using namespace std;

// Palet Warna Premium CLI (Murni ANSI)
const string RESET           = "\033[0m"; 
const string HIJAU_NEON      = "\033[1;32m"; 
const string CYAN_NEON       = "\033[1;36m"; 
const string MAGENTA_CERAH   = "\033[1;35m"; 
const string MERAH_CERAH     = "\033[1;31m"; 
const string KUNING_EMAS     = "\033[1;33m";
const string SOROT_MENU      = "\033[1;30;46m"; 

// ==========================================
// 4. IMPLEMENTASI STRUCT
// ==========================================
struct AkunUser {
    string namaLengkap;
    string username;
    string password;
};

// ==========================================
// 2. IMPLEMENTASI ARRAY (Database Banyak Akun)
// ==========================================
const int MAX_USER = 50;
AkunUser daftarUser[MAX_USER]; // Array bertipe Struct untuk menampung data user
int jumlahUser = 0;            // Counter untuk menghitung jumlah user yang mendaftar

// ==========================================
// 5. IMPLEMENTASI POINTER (Sesi Aktif Login)
// ==========================================
AkunUser* userAktif = nullptr; // Pointer untuk menunjuk akun siapa yang sedang login

// ==========================================
// 3. IMPLEMENTASI FUNCTION
// ==========================================
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
    cetakTengah(R"(   \|_________|                                                                       )", CYAN_NEON);
    cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
    cetakTengah("             SISTEM INFORMASI PERPUSTAKAAN PINTAR | KELOMPOK 19 PROJECTS              ", MAGENTA_CERAH);
    cetakTengah("======================================================================================", HIJAU_NEON);
    cout << "\n";
}

string inputPasswordMasking() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) { 
            break;
        }
        else if (ch == 8) { 
            if (!password.empty()) {
                cout << "\b \b"; 
                password.pop_back();
            }
        }
        else if (ch != 0 && ch != -32) { 
            password.push_back(ch);
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

void dashboardAdmin() {
    bersihkanLayar();
    tampilkanHeaderTengah();
    cetakTengah("[ SUCCESS: WELCOME TO ADMIN DASHBOARD ]", HIJAU_NEON);
    cout << "\n\n";
    cetakTengah("Halo Pustakawan! Modul manajemen buku Kelompok 19 siap dijalankan di sini...");
    cout << "\n\n";
    cetakTengah("<<<< Tekan tombol apa saja untuk Log Out >>>>", MERAH_CERAH);
    _getch();
}

// Function menerima parameter berupa POINTER struct
void dashboardUser(AkunUser* user) {
    bersihkanLayar();
    tampilkanHeaderTengah();
    cetakTengah("[ SUCCESS: WELCOME TO STUDENT DASHBOARD ]", HIJAU_NEON);
    cout << "\n\n";
    
    // Mengakses data struct menggunakan operator panah (->) melalui pointer
    cetakTengah("Selamat Datang, " + user->namaLengkap + "!", KUNING_EMAS);
    cetakTengah("Username Anda : " + user->username, CYAN_NEON);
    cout << "\n";
    cetakTengah("Modul peminjaman buku perpustakaan pintar siap digunakan...", RESET);
    cout << "\n\n";
    cetakTengah("<<<< Tekan tombol apa saja untuk Log Out >>>>", MERAH_CERAH);
    _getch();
}

// ==========================================
// 1. IMPLEMENTASI STATEMENT CONTROL & LOOPING
// ==========================================
void formLogin(string role) {
    string username, password;
    
    while (true) { // Looping menu login
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
        password = inputPasswordMasking();
        
        cout << "\n";
        cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);

        // Failure Handling 1: Input Kosong (Statement Control)
        if (username.empty() || password.empty()) {
            cetakTengah("[ ERROR: Username atau Password tidak boleh kosong! ]", MERAH_CERAH);
            cetakTengah("Tekan tombol apa saja untuk mengulangi...", KUNING_EMAS);
            _getch();
            continue; 
        }
        
        // Verifikasi Akun ADMIN
        if (role == "ADMIN") {
            if (username == "admin19" && password == "pustaka19") {
                cetakTengah("[ LOGIN BERHASIL - ACCESS GRANTED ]", HIJAU_NEON);
                _getch();
                dashboardAdmin();
                break; 
            } else {
                cetakTengah("[ ERROR: Username atau Password Admin salah! ]", MERAH_CERAH);
                cetakTengah("Pilih: [1] Coba Lagi | [2] Kembali ke Menu", KUNING_EMAS);
                char opsi = _getch();
                if (opsi == '2') break;
            }
        } 
        // Verifikasi Akun USER mencari di dalam Array Struct
        else if (role == "USER") {
            bool ditemukan = false;
            
            // Looping & Statement Control untuk membaca data di dalam Array
            for (int i = 0; i < jumlahUser; i++) {
                if (daftarUser[i].username == username && daftarUser[i].password == password) {
                    ditemukan = true;
                    
                    // POINTER ditugaskan mencatat alamat memori elemen array yang cocok
                    userAktif = &daftarUser[i]; 
                    break;
                }
            }
            
            if (ditemukan) {
                cetakTengah("[ LOGIN BERHASIL - ACCESS GRANTED ]", HIJAU_NEON);
                _getch();
                dashboardUser(userAktif); // Melempar pointer sesi login ke fungsi dashboard
                userAktif = nullptr;      // Reset pointer setelah logout demi keamanan data
                break;
            } else {
                cetakTengah("[ ERROR: Username atau Password salah / belum terdaftar! ]", MERAH_CERAH);
                cetakTengah("Pilih: [1] Coba Lagi | [2] Kembali ke Menu", KUNING_EMAS);
                char opsi = _getch();
                if (opsi == '2') break;
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
        
        // Failure Handling: Cek kapasitas maksimum array database
        if (jumlahUser >= MAX_USER) {
            cetakTengah("[ ERROR: Kapasitas pendaftaran memori sistem penuh! ]", MERAH_CERAH);
            cetakTengah("<<<< Tekan tombol apa saja untuk kembali >>>>", KUNING_EMAS);
            _getch();
            break;
        }
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Nama Lengkap : ";
        getline(cin, namaInput);
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Username     : ";
        getline(cin, userInput);
        
        cout << setw(25) << setfill(' ') << "" << "Masukkan Password     : ";
        passInput = inputPasswordMasking();
        
        cout << "\n";
        cetakTengah("--------------------------------------------------------------------------------------", HIJAU_NEON);
        
        // Failure Handling: Kolom Kosong
        if (namaInput.empty() || userInput.empty() || passInput.empty()) {
            cetakTengah("[ ERROR: Semua kolom pendaftaran wajib diisi! ]", MERAH_CERAH);
            cetakTengah("Tekan tombol apa saja untuk mengulangi pengisian...", KUNING_EMAS);
            _getch();
            continue; 
        }
        
        // Failure Handling: Cek Duplikasi Username di dalam Array Struct
        bool usernameKembar = false;
        for (int i = 0; i < jumlahUser; i++) {
            if (daftarUser[i].username == userInput) {
                usernameKembar = true;
                break;
            }
        }
        
        if (usernameKembar) {
            cetakTengah("[ ERROR: Username '" + userInput + "' sudah terpakai! ]", MERAH_CERAH);
            cetakTengah("Silakan gunakan username unik yang lain.", KUNING_EMAS);
            _getch();
            continue;
        }
        
        // Memasukkan inputan baru ke dalam ARRAY ELEMEN KE-N berbentuk STRUCT
        daftarUser[jumlahUser].namaLengkap = namaInput;
        daftarUser[jumlahUser].username    = userInput;
        daftarUser[jumlahUser].password    = passInput;
        
        jumlahUser++; // Update counter total data di dalam array
        
        cetakTengah("[ REGISTRASI BERHASIL! Akun Anda sukses didaftarkan ]", HIJAU_NEON);
        cetakTengah("Silakan kembali ke menu Login untuk menguji akun.", KUNING_EMAS);
        cout << "\n";
        cetakTengah("<<<< Tekan tombol apa saja untuk kembali ke Menu Utama >>>>", HIJAU_NEON);
        _getch();
        break; 
    }
}

void subMenuLogin() {
    string menuSub[] = {
        "  1. LOGIN SEBAGAI ADMIN (PUSTAKAWAN)  ",
        "  2. LOGIN SEBAGAI USER (MAHASISWA)    ",
        "  3. KEMBALI KE MENU UTAMA             "
    };
    int totalMenuSub = 3;
    int terpilihSub = 0;
    char tombolSub;

    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();

        cetakTengah("[ LOGIN SELECTION PORTAL ]", MAGENTA_CERAH);
        cetakTengah("Navigasi: [W/S] atau [Panah] | Pilih: [ENTER]", HIJAU_NEON);
        cout << "\n\n";

        for (int i = 0; i < totalMenuSub; i++) {
            if (i == terpilihSub) {
                string teksTerpilih = "==> " + menuSub[i] + " <==";
                cetakTengah(teksTerpilih, SOROT_MENU);
            } else {
                string teksBiasa = "    " + menuSub[i] + "    ";
                cetakTengah(teksBiasa, CYAN_NEON);
            }
            cout << "\n";
        }
        cetakTengah("======================================================================================", HIJAU_NEON);

        tombolSub = _getch();

        if (tombolSub == -32 || tombolSub == 0) {
            tombolSub = _getch();
            if (tombolSub == 72) terpilihSub = (terpilihSub - 1 + totalMenuSub) % totalMenuSub;
            else if (tombolSub == 80) terpilihSub = (terpilihSub + 1) % totalMenuSub;
        }
        else if (tombolSub == 'w' || tombolSub == 'W') terpilihSub = (terpilihSub - 1 + totalMenuSub) % totalMenuSub;
        else if (tombolSub == 's' || tombolSub == 'S') terpilihSub = (terpilihSub + 1) % totalMenuSub;
        else if (tombolSub == 13) { 
            if (terpilihSub == 0) {
                formLogin("ADMIN");
            } else if (terpilihSub == 1) {
                formLogin("USER");
            } else if (terpilihSub == 2) {
                return; 
            }
        }
    }
}

int main() {
    string menuUtama[] = {
        "  1. LOGIN SYSTEM       ",
        "  2. CREATE ACCOUNT     ",
        "  3. EXIT PROGRAM       "
    };
    
    int totalMenuUtama = 3; 
    int posisiTerpilih = 0; 
    char tombolKetik;

    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();
        
        cetakTengah("[ MAIN CONTROL PANEL ]", MAGENTA_CERAH);
        cetakTengah("Navigasi: [W/S] atau [Panah] | Pilih: [ENTER]", HIJAU_NEON);
        cout << "\n\n";

        for (int i = 0; i < totalMenuUtama; i++) {
            if (i == posisiTerpilih) {
                string teksMenuTerpilih = "==> " + menuUtama[i] + " <==";
                cetakTengah(teksMenuTerpilih, SOROT_MENU);
            } else {
                string teksMenuBiasa = "    " + menuUtama[i] + "    ";
                cetakTengah(teksMenuBiasa, CYAN_NEON);
            }
            cout << "\n"; 
        }
        
        cetakTengah("======================================================================================", HIJAU_NEON);

        tombolKetik = _getch();

        if (tombolKetik == -32 || tombolKetik == 0) { 
            tombolKetik = _getch(); 
            if (tombolKetik == 72) posisiTerpilih = (posisiTerpilih - 1 + totalMenuUtama) % totalMenuUtama;
            else if (tombolKetik == 80) posisiTerpilih = (posisiTerpilih + 1) % totalMenuUtama;
        }
        else if (tombolKetik == 'w' || tombolKetik == 'W') posisiTerpilih = (posisiTerpilih - 1 + totalMenuUtama) % totalMenuUtama;
        else if (tombolKetik == 's' || tombolKetik == 'S') posisiTerpilih = (posisiTerpilih + 1) % totalMenuUtama;
        else if (tombolKetik == 13) { 
            if (posisiTerpilih == 0) {
                subMenuLogin(); 
            } else if (posisiTerpilih == 1) {
                halamanCreateAccount(); 
            } else if (posisiTerpilih == 2) {
                bersihkanLayar();
                cout << "\n\n\n";
                cetakTengah("+--------------------------------------------------------+", HIJAU_NEON);
                cetakTengah("|    TERIMA KASIH TELAH MENGGUNAKAN LAYANAN SMART LIB!   |", HIJAU_NEON);
                cetakTengah("|              SALAM HANGAT DARI KELOMPOK 19             |", HIJAU_NEON);
                cetakTengah("+--------------------------------------------------------+", HIJAU_NEON);
                cout << "\n\n";
                
                cetakTengah("[ Tekan tombol apa saja untuk menutup terminal ]", MAGENTA_CERAH);
                _getch(); 
                
                bersihkanLayar();
                cout << RESET; 
                exit(0); 
            }
        }
    }
    return 0;
}