#include <iostream>
#include <string>
#include <limits>
#include <iomanip> 
#include <conio.h> 
#include <cstdlib> 

using namespace std;

// Palet Warna Premium CLI (Murni ANSI, Tanpa Windows.h)
const string RESET           = "\033[0m"; 
const string HIJAU_NEON      = "\033[1;32m"; 
const string CYAN_NEON       = "\033[1;36m"; 
const string MAGENTA_CERAH   = "\033[1;35m"; 
const string MERAH_CERAH     = "\033[1;31m"; 
const string SOROT_MENU      = "\033[1;30;46m"; // Gaya BIOS: Teks Hitam, Background Cyan

void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi cetak tengah otomatis menggunakan <iomanip>
void cetakTengah(string teks, string kodeWarna = "") {
    int lebarTerminal = 80; 
    int panjangTeks = teks.length();
    int padding = (lebarTerminal - panjangTeks) / 2;
    
    if (padding > 0) {
        cout << setw(padding) << setfill(' ') << ""; 
    }
    cout << kodeWarna << teks << RESET << endl;
}

// UPDATE: Header baru "SMART LIB" dengan karakter standar yang presisi & anti-error
void tampilkanHeaderTengah() {
    cout << "\n";
    cetakTengah("=============================================================", HIJAU_NEON);
    cetakTengah(" ____  __  __   _   ____  _____     _     ___  ____  ", CYAN_NEON);
    cetakTengah("/ ___||  \\/  | /_\\ |  _ \\|_   _|   | |   |_ _| | __ ) ", CYAN_NEON);
    cetakTengah("\\___ \\| |\\/| |/ _ \\| |_) | | |     | |    | |  |  _ \\ ", CYAN_NEON);
    cetakTengah(" ___) | |  | / ___ |  _ <  | |     | |___ | |  | |_) |", CYAN_NEON);
    cetakTengah("|____/|_|  |/_/   \\_|_| \\_\\|_|     |_____|___| |____/ ", CYAN_NEON);
    cetakTengah("-------------------------------------------------------------", HIJAU_NEON);
    cetakTengah("  SISTEM INFORMASI PERPUSTAKAAN PINTAR | KELOMPOK 19 PROJECTS", MAGENTA_CERAH);
    cetakTengah("=============================================================", HIJAU_NEON);
    cout << "\n";
}

void halamanAdmin() {
    bersihkanLayar(); 
    tampilkanHeaderTengah();
    cetakTengah("[ DATABASE ACCESS: ADMIN PORTAL ]", MAGENTA_CERAH);
    cout << "\n\n";
    cetakTengah("Sistem siap dihubungkan dengan modul Kelompok 19...");
    cout << "\n\n";
    cetakTengah("<<<< Tekan tombol apa saja untuk kembali ke Menu >>>>", HIJAU_NEON);
    _getch();
}

void halamanUser() {
    bersihkanLayar(); 
    tampilkanHeaderTengah();
    cetakTengah("[ STUDENT ACCESS: USER PORTAL ]", MAGENTA_CERAH);
    cout << "\n\n";
    cetakTengah("Sistem siap diintegrasikan dengan database Mahasiswa...");
    cout << "\n\n";
    cetakTengah("<<<< Tekan tombol apa saja untuk kembali ke Menu >>>>", HIJAU_NEON);
    _getch();
}

int main() {
    string menu[] = {
        "  1. LOG IN SEBAGAI ADMIN (PUSTAKAWAN)  ",
        "  2. LOG IN SEBAGAI USER (MAHASISWA)    ",
        "  3. EXIT SYSTEM (KELUAR PROGRAM)       "
    };
    
    int totalMenu = 3; 
    int posisiTerpilih = 0; 
    char tombolKetik;

    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();
        
        cetakTengah("[ CONTROL PANEL - MAIN MENU ]", MAGENTA_CERAH);
        cetakTengah("Navigasi: [W/S] atau [Panah Atas/Bawah] | Pilih: [ENTER]", HIJAU_NEON);
        cout << "\n\n";

        for (int i = 0; i < totalMenu; i++) {
            if (i == posisiTerpilih) {
                string teksMenuTerpilih = "==> " + menu[i] + " <==";
                cetakTengah(teksMenuTerpilih, SOROT_MENU);
            } else {
                string teksMenuBiasa = "    " + menu[i] + "    ";
                cetakTengah(teksMenuBiasa, CYAN_NEON);
            }
            cout << "\n"; 
        }
        
        cetakTengah("=============================================================", HIJAU_NEON);

        tombolKetik = _getch();

        if (tombolKetik == -32 || tombolKetik == 0) { 
            tombolKetik = _getch(); 
            if (tombolKetik == 72) posisiTerpilih = (posisiTerpilih - 1 + totalMenu) % totalMenu;
            else if (tombolKetik == 80) posisiTerpilih = (posisiTerpilih + 1) % totalMenu;
        }
        else if (tombolKetik == 'w' || tombolKetik == 'W') posisiTerpilih = (posisiTerpilih - 1 + totalMenu) % totalMenu;
        else if (tombolKetik == 's' || tombolKetik == 'S') posisiTerpilih = (posisiTerpilih + 1) % totalMenu;
        else if (tombolKetik == 13) { 
            if (posisiTerpilih == 0) {
                halamanAdmin();
            } else if (posisiTerpilih == 1) {
                halamanUser();
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