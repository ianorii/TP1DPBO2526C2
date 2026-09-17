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
| `rating` | float | Rating film (0-10) |
| `gambar` | string | Path file gambar poster |

---

## Error Handling

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
- **Kondisi**: Rating diisi selain 0-10
- **Penanganan**: atribut `min="0"` `max="10"` pada HTML input

### 6. SQL Injection
- **Kondisi**: Input mengandung karakter berbahaya
- **Penanganan**: Menggunakan `htmlspecialchars()` untuk sanitasi input

---

## Dokumentasi CLI

### C++
```bash
# Compile
g++ -o film main.cpp Film.cpp

# Run
./film
```

### Java
```bash
# Compile
javac Main.java Film.java

# Run
java Main
```

### Python
```bash
# Run
python main.py
```

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
| Rating | number | 0 - 10, desimal |
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
