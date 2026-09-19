# TP1 DPBO 2025/2026 C2

## Janji
Saya Muhammad Rian Anugrah dengan NIM 2507241 mengerjakan Tugas Praktikum 1 pada Mata Kuliah Desain dan Pemrograman Berorientasi Objek (DPBO) untuk keberkahan-Nya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin

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

## Error Handling Program CLI

### 1. Input Bukan Angka
<img src="./Dokumentasi/error/img1.png" width=600>

### 2. Rating Bukan Desimal
<img src="./Dokumentasi/error/img2.png" width=600>

### 3. Rating Diluar Range
<img src="./Dokumentasi/error/img3.png" width=600>

### 4. ID Sudah Terpakai
<img src="./Dokumentasi/error/img4.png" width=600>

### 5. ID Tidak Ditemukan
<img src="./Dokumentasi/error/img5.png" width=600>

### 6. Opsi Menu Tidak Valid
<img src="./Dokumentasi/error/img6.png" width=600>

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
cd Python/
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

1. Buka folder 'PHP/'
    ```bash
    cd PHP/
    ```
3. Jalankan perintah:
   ```bash
   php -S localhost:8000
   ```
3. Buka browser dan akses `http://localhost:8000/Main.php`

### Tampilan Website
<img src="./Dokumentasi/php/img1.png" width=800>

### Menambahkan Data
<img src="./Dokumentasi/php/insert.png" width=600><br>
<img src="./Dokumentasi/php/hasilinsert.png" width=600>

### Memperbarui Data
<img src="./Dokumentasi/php/update.png" width=600><br>
<img src="./Dokumentasi/php/hasilupdate.png" width=600>

### Menghapus Data
<img src="./Dokumentasi/php/delete.png" width=600><br>
<img src="./Dokumentasi/php/hasildelete.png" width=600>

### Mencari Data
<img src="./Dokumentasi/php/search.png" width=600><br>

### Error Handling
<img src="./Dokumentasi/php/error1.png" width= 600><br>
<img src="./Dokumentasi/php/error2.png" width= 600><br>
<img src="./Dokumentasi/php/error3.png" width= 600><br>
<img src="./Dokumentasi/php/error4.png" width= 600><br>
<img src="./Dokumentasi/php/error5.png" width= 600><br>