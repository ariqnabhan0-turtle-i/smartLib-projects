#include <iostream>
#include <string>
#include <limits>
#include <iomanip> 
#include <conio.h> 
#include <cstdlib> 

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Palet Warna Neon Cyberpunk Kontras Tinggi
const string RESET           = "\033[0m"; // KUNCI UTAMA UNTUK MENORMALKAN TERMINAL
const string HIJAU_NEON      = "\033[1;32m"; 
const string CYAN_NEON       = "\033[1;36m"; 
const string MAGENTA_CERAH   = "\033[1;35m"; 
const string MERAH_CERAH     = "\033[1;31m"; 
const string SOROT_MENU      = "\033[1;7;36m";

void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void cetakTengah(string teks, string kodeWarna = "") {
    int lebarTerminal = 85;
    int panjangTeks = teks.length();
    int padding = (lebarTerminal - panjangTeks) / 2;
    if (padding > 0) cout << setw(padding) << ""; 
    cout << kodeWarna << teks << RESET << endl; // Setiap cetak selesai, otomatis reset warna
}

void tampilkanHeaderTengah() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
    string pad = "   "; 
    cout << HIJAU_NEON << pad << "╔════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << pad << "║" << CYAN_NEON << "  ██████╗███╗   ███╗ █████╗ ██████╗ ████████╗██╗     ██╗██████╗         " << HIJAU_NEON << "║" << endl;
    cout << pad << "║" << CYAN_NEON << " ██╔════╝████╗ ████║██╔══██╗██╔══██╗╚══██╔══╝██║     ██║██╔══██╗        " << HIJAU_NEON << "║" << endl;
    cout << pad << "║" << CYAN_NEON << " ╚█████╗ ██╔████╔██║███████║██████╔╝   ██║   ██║     ██║██████╔╝        " << HIJAU_NEON << "║" << endl;
    cout << pad << "║" << CYAN_NEON << "  ╚═══██╗██║╚██╔╝██║██╔══██║██╔══██╗   ██║   ██║     ██║██╔══██╗        " << HIJAU_NEON << "║" << endl;
    cout << pad << "║" << CYAN_NEON << " ██████╔╝██║ ╚═╝ ██║██║  ██║██║  ██║   ██║   ███████╗██║██████╔╝        " << HIJAU_NEON << "║" << endl;
    cout << pad << "║" << CYAN_NEON << " ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝╚═════╝         " << HIJAU_NEON << "║" << endl;
    cout << pad << "║" << HIJAU_NEON << " ══════════════════════════════════════════════════════════════════════ " << HIJAU_NEON << "║" << endl;
    cout << pad << "║" << MAGENTA_CERAH << "  SISTEM INFORMASI PERPUSTAKAAN PINTAR  | " << MERAH_CERAH << "[ KELOMPOK 19 PROJECTS ]      " << HIJAU_NEON << "║" << endl;
    cout << pad << "╚════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
    cout << "\n";
}

void halamanAdmin() {
    bersihkanLayar(); tampilkanHeaderTengah();
    cetakTengah("─── [ DIALAHKAN KE: HALAMAN AKSES ADMIN ] ───", MAGENTA_CERAH);
    cout << "\n\n"; cetakTengah("Tekan tombol apa saja untuk kembali..."); _getch();
}

void halamanUser() {
    bersihkanLayar(); tampilkanHeaderTengah();
    cetakTengah("─── [ DIALAHKAN KE: HALAMAN AKSES USER ] ───", MAGENTA_CERAH);
    cout << "\n\n"; cetakTengah("Tekan tombol apa saja untuk kembali..."); _getch();
}

int main() {
    string menu[] = {
        "  [1] Log In sebagai Admin (Pustakawan)  ",
        "  [2] Log In sebagai User (Mahasiswa)   ",
        "  [3] Keluar dari Sistem (Exit Program)  "
    };
    
    int totalMenu = 3; int posisiTerpilih = 0; char tombolKetik;

    while (true) {
        bersihkanLayar();
        tampilkanHeaderTengah();
        cetakTengah("Gunakan tombol [▲/▼ Atas Bawah] atau [W/S] lalu tekan [ENTER]", HIJAU_NEON);
        cout << "\n\n";

        for (int i = 0; i < totalMenu; i++) {
            if (i == posisiTerpilih) {
                string teksMenuTerpilih = "► " + menu[i] + " ◄";
                cetakTengah(teksMenuTerpilih, SOROT_MENU);
            } else {
                string teksMenuBiasa = "  " + menu[i] + "  ";
                cetakTengah(teksMenuBiasa, CYAN_NEON);
            }
            cout << "\n";
        }

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
                // ==================== PERBAIKAN TOTAL BOX EXIT ====================
                bersihkanLayar();
                cout << "\n\n";
                cetakTengah("+------------------------------------------------------+", HIJAU_NEON);
                cetakTengah("|   Terima kasih telah menggunakan layanan SmartLib!   |", HIJAU_NEON);
                cetakTengah("|          Salam hangat dari KELOMPOK 19               |", HIJAU_NEON);
                cetakTengah("+------------------------------------------------------+", HIJAU_NEON);
                cout << "\n\n";
                
                // 1. Beri instruksi dan paksa terminal menunggu ketukan keyboard agar jendela tidak langsung hilang
                cetakTengah("Tekan tombol apa saja pada keyboard untuk menutup program...", MAGENTA_CERAH);
                _getch(); 
                
                // 2. Clear screen terakhir agar terminal kembali bersih saat diserahkan ke OS
                bersihkanLayar();
                
                // 3. WAJIB: Tembakkan kode RESET ke konsol Windows agar warna command prompt kembali normal ke bawaan laptop
                cout << RESET; 
                
                // 4. Tutup program dengan aman
                exit(0); 
                // ==================================================================
            }
        }
    }
    return 0;
}