# TP1 DPBO 2025/2026 C2 - Sistem Manajemen Data Film

## Struktur Folder

```
TP1DPBO2526C2/
├── Readme.md
├── CPP/
│   ├── Film.cpp
│   └── main.cpp
├── Java/
│   ├── Film.java
│   └── Main.java
├── Python/
│   ├── Film.py
│   └── main.py
├── PHP/
│   ├── Film.php
│   ├── Main.php
│   └── image/
│       ├── Big Hero 6.jpg
│       ├── Cars.jpg
│       ├── Inside Out.jpg
│       ├── Minions (2015).jpg
│       └── Spider-Man Across the Spider-Verse.jpg
└── Dokumentasi/
    └── ...
```

---

## Penjelasan Fitur

### Fitur Utama

| Fitur | Deskripsi |
|-------|-----------|
| Tambah Data | Menambahkan data film baru (ID, nama, durasi, rating, gambar) |
| Lihat Data | Menampilkan semua data film dalam format card |
| Edit Data | Mengubah data film yang sudah ada |
| Hapus Data | Menghapus data film dari daftar |
| Cari Data | Mencari film berdasarkan ID |

### Class Film

| Atribut | Tipe | Deskripsi |
|---------|------|-----------|
| `id` | int | ID unik film |
| `nama` | string | Nama film |
| `durasi` | int | Durasi film (menit) |
| `rating` | float | Rating film (1-10) |
| `gambar` | string | Path file gambar poster |

---

## Error Handling di Semua Program

### 1. Input Kosong
- **Kondisi**: User tidak mengisi field yang wajib
- **Penanganan**: atribut `required` pada HTML form

### 2. ID Tidak Ditemukan
- **Kondisi**: User mencoba edit/hapus dengan ID yang tidak ada
- **Pesan**: `"ID tidak ditemukan!"`

### 3. File Bukan Gambar
- **Kondisi**: User upload file selain gambar
- **Penanganan**: Validasi ekstensi file (jpg, jpeg, png, gif, webp)
- **Pesan**: Tidak ada notifikasi, file tidak diupload

### 4. Upload Gagal
- **Kondisi**: Error saat memindahkan file ke server
- **Penanganan**: Cek return value `move_uploaded_file()`

### 5. Rating Diluar Range
- **Kondisi**: Rating diisi di luar range 1-10
- **Penanganan**: Validasi di semua bahasa (C++, Java, Python, PHP)
- **Pesan**: `"Rating harus di range 1-10!"`

### 6. SQL Injection
- **Kondisi**: Input mengandung karakter berbahaya
- **Penanganan**: Menggunakan `htmlspecialchars()` untuk sanitasi input

---

## Dokumentasi C++
### Compile dan Run
```bash
# Compile
cd CPP/
g++ Main.cpp -o Main

# Run
./Main
```
### Menambahkan Data
<img src="./Dokumentasi/cpp/insert.png" alt="inset" width=600>

### Menampilkan Data
<img src="./Dokumentasi/cpp/show.png" alt="show" width=600>

### Memperbarui Data
Jika ada atribut yang tidak diperbarui makan tekan enter agar otomatis mengambil default value<br>
<img src="./Dokumentasi/cpp/update.png" alt="update" width=600>

### Menghapus Data
<img src="./Dokumentasi/cpp/delete.png" alt="delete" width=600>

### Mencari Data
<img src="./Dokumentasi/cpp/search.png" alt="search" width=600>

---

## Dokumenatasi Java
### Compile dan Run
```bash
# Compile
cd Java/
javac Main.java

# Run
java Main
```
### Menambahkan Data
<img src="./Dokumentasi/java/insert.png" alt="inset" width=600>

### Menampilkan Data
<img src="./Dokumentasi/java/show.png" alt="show" width=600>

### Memperbarui Data
Jika ada atribut yang tidak diperbarui makan tekan enter agar otomatis mengambil default value<br>
<img src="./Dokumentasi/java/update.png" alt="update" width=600>

### Menghapus Data
<img src="./Dokumentasi/java/delete.png" alt="delete" width=600>

### Mencari Data
<img src="./Dokumentasi/java/search.png" alt="search" width=600>

---

## Dokumentasi Python
### Compile dan Run
```bash
# Run
python Main.py
```

### Menambahkan Data
<img src="./Dokumentasi/python/insert.png" alt="inset" width=600>

### Menampilkan Data
<img src="./Dokumentasi/python/show.png" alt="show" width=600>

### Memperbarui Data
Jika ada atribut yang tidak diperbarui makan tekan enter agar otomatis mengambil default value<br>
<img src="./Dokumentasi/python/update.png" alt="update" width=600>

### Menghapus Data
<img src="./Dokumentasi/python/delete.png" alt="delete" width=600>

### Mencari Data
<img src="./Dokumentasi/python/search.png" alt="search" width=600>

---

## Dokumentasi Web PHP

### Cara Menjalankan

1. Pastikan PHP sudah terinstall
2. Buka terminal di folder `PHP/`
3. Jalankan perintah:
   ```bash
   php -S localhost:8000
   ```
4. Buka browser dan akses `http://localhost:8000/Main.php`

### Halaman Web

| Halaman | URL | Deskripsi |
|---------|-----|-----------|
| Main | `/Main.php` | Halaman utama untuk kelola data film |

### Form Tambah/Edit

| Field | Tipe | Keterangan |
|-------|------|------------|
| Nama Film | text | Wajib diisi |
| Durasi | number | Wajib diisi (menit) |
| Rating | number | 1 - 10, desimal |
| Gambar Poster | file | jpg, jpeg, png, gif, webp |

### Upload Gambar
- Gambar disimpan di folder `image/`
- Nama file menggunakan nama asli dari file yang diupload
- Jika nama sudah ada, akan menimpa file sebelumnya

---

## Referensi

- [PHP Documentation](https://www.php.net/docs/)
- [HTML Documentation](https://developer.mozilla.org/en-US/docs/Web/HTML)
- [CSS Documentation](https://developer.mozilla.org/en-US/docs/Web/CSS)
