# smartLib 📚
**smartLib** adalah aplikasi berbasis CLI (Command Line Interface) yang dirancang untuk mengotomatisasi administrasi perpustakaan pintar. Program ini mengimplementasikan konsep struktur data (struct), manajemen memori statis (Array), kontrol akses berbasis peran (*Role-Based Access Control*), manipulasi waktu nyata (*Time Handling*), serta algoritma pengurutan untuk menentukan rekomendasi buku terpopuler.
Aplikasi ini dikembangkan oleh **Kelompok 19** menggunakan bahasa pemrograman **C++**.

## 👥 Hak Akses & Akun Bawaan
Aplikasi ini membagi fungsionalitas menjadi dua *role* utama yang terintegrasi:
 * **Administrator (Pustakawan):** Mengelola inventaris fisik buku, verifikasi sirkulasi, dan finansial denda.
   * **Username Bawaan:** admin19
   * **Password Bawaan:** pustaka19
 * **User (Mahasiswa):** Melakukan pencarian koleksi, mengajukan peminjaman, pelacakan denda, dan interaksi rating buku. Mahasiswa dapat mendaftarkan akun baru secara dinamis melalui fitur **Create Account**.
## ✨ Fitur-Fitur Utama Berdasarkan Kode
### 1. Sistem Autentikasi & Autorisasi (formLogin & halamanCreateAccount)
 * **Registrasi Mandiri:** Mahasiswa dapat mendaftarkan Nama Lengkap, Username, dan Password yang divalidasi agar tidak terjadi duplikasi username (usernameKembar).
 * **Session Tracking:** Menggunakan pointer global userAktif untuk menjaga sesi transaksi data mahasiswa yang sedang masuk ke sistem.
### 2. Modul Administrator (Dashboard Admin)
 * **Tambah Buku Baru (TambahBuku):** Memasukkan data buku baru dengan validasi ID unik sepanjang 4 karakter, pembatasan memori MAX_BUKU (100), serta penolakan *input* kosong atau tahun terbit tidak valid (rentang 1900–2026).
 * **Edit Informasi Buku (editBuku & subEdit):** Mengubah detail informasi buku (Judul, Penulis, Tahun, ID, Stok) secara fleksibel. Cukup menekan **ENTER** jika tidak ingin mengubah data sebelumnya.
 * **Hapus Buku Bersyarat (HapusBuku):** Menghapus buku dari basis data menggunakan metode pergeseran indeks array. Sistem memiliki *guardrail* keamanan: **Buku tidak dapat dihapus jika sedang dipinjam oleh mahasiswa.**
 * **Verifikasi Peminjaman (verifikasiPeminjaman):** Sistem *approval* dua arah. Permintaan pinjam dari mahasiswa harus disetujui admin sebelum status buku resmi berpindah tangan. Jika admin menolak, stok buku otomatis dikembalikan.
 * **Manajemen Keuangan Denda (KelolaDenda):** Menampilkan rekapitulasi data mahasiswa yang terlambat mengembalikan buku beserta akumulasi total denda aktif dan mengubah status bayar menjadi **LUNAS**.
### 3. Modul Mahasiswa (Dashboard Student)
 * **Pencarian Koleksi (CariBuku):** Mencari buku secara instan berdasarkan judul yang cocok secara presisi.
 * **Pengajuan Peminjaman Real-time (PinjamBuku):** Menggunakan pustaka <ctime> untuk mencatat tanggal peminjaman berdasarkan waktu lokal komputer saat tombol ditekan. Stok buku otomatis berkurang 1 unit setelah pengajuan diajukan.
 * **Pengembalian & Kalkulasi Denda (PengembalianBuku):** Menghitung durasi pinjam secara otomatis dengan rumus konversi hari (Tahun, Bulan, Hari). Batas peminjaman gratis adalah **7 Hari**. Keterlambatan dikenakan denda akumulatif sebesar **Rp 2.000 / hari**.
 * **Rekomendasi Buku Populer (BukuPopuler):** Memberikan rekomendasi berdasarakan rating yang diberikan oleh User dan juga berapa banyak suatu buku di pinjaman oleh beberapa User
   
 * **Rating Buku Interaktif (ratingBuku):** Mahasiswa memberikan evaluasi skor skala 1–5 yang langsung dikonversi menjadi rata-rata rating baru secara *real-time*.
## 🛠️ Komponen Arsitektur Kode
Program ini dibangun dengan struktur data saling mengikat yang didefinisikan sebagai berikut:
```cpp
struct AkunUser { string namaLengkap; string username; string password; };
struct buku     { string judul; string penulis; int tahunTerbit; string idBuku; int jumlahBuku; float rating; ... };
struct peminjaman { string username; string idBuku; string judulBuku; bool disetujui; int hariPinjam; ... };

```
### Keterangan Pengaturan Batas Array Statis:
 * Kapasitas Maksimal Akun Mahasiswa (MAX_USER) : **50 Akun**
 * Kapasitas Maksimal Koleksi Buku (MAX_BUKU)  : **100 Buku**
 * Kapasitas Maksimal Riwayat Transaksi (MAX_PINJAM) : **100 Data**
## 🎨 Antarmuka & UX Terminal
Aplikasi ini menggunakan manipulasi **ANSI Escape Code** untuk menghadirkan visualisasi terminal bergaya *Neon Theme*:
 * \033[1;32m - Hijau Neon (Indikator sukses dan bingkai utama)
 * \033[1;36m - Cyan Neon (Judul menu dan navigasi)
 * \033[1;31m - Merah Cerah (Sistem eror dan peringatan validasi)
 * Fungsi manajemen layar bersihkanLayar() mendukung lintas platform (**Windows cls** dan **Linux/OSX clear**).
## 📦 Prasyarat menjalankan Aplikasi
Pastikan perangkat Anda memiliki compiler GCC/G++ yang mendukung standar C++11 atau di atasnya.
```bash
# 1. Kompilasi kode program
g++ main.cpp -o smartLib

# 2. Jalankan aplikasi
./smartLib

```
