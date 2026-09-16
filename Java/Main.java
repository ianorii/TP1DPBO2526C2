import java.util.ArrayList;
import java.util.Scanner;

// Sistem Manajemen Data Film
// Program ini merupakan program CRUD (Create, Read, Update, Delete)
// untuk mengelola data film menggunakan Java dengan pendekatan OOP.
public class Main {
    // ArrayList untuk menyimpan objek Film (in-memory database)
    static ArrayList<Film> dataFilm = new ArrayList<>();
    // Scanner untuk membaca input dari user
    static Scanner scanner = new Scanner(System.in);
    // Header tabel
    static String[] headers = {"ID", "Nama Film", "Durasi (menit)", "Rating"};
    // Lebar kolom untuk tampilan tabel
    static int[] col = new int[4];

    // Konstanta ANSI Escape Code untuk pewarnaan teks pada terminal
    static final String RESET = "\033[0m";    // Reset warna ke default
    static final String RED = "\033[31m";     // Warna merah untuk pesan error
    static final String GREEN = "\033[32m";   // Warna hijau untuk pesan sukses
    static final String CYAN = "\033[36m";    // Warna cyan untuk menu dan header
    static final String YELLOW = "\033[33m";  // Warna kuning untuk peringatan
    static final String BOLD = "\033[1m";     // Teks tebal/bold

    // Menginisialisasi lebar kolom berdasarkan panjang header
    public static void initCol() {
        for (int i = 0; i < 4; i++) col[i] = headers[i].length();
    }

    // Menampilkan judul program dan daftar menu
    public static void intro() {
        System.out.println(BOLD + CYAN);
        System.out.println("+====================================================+");
        System.out.println("|           SISTEM MANAJEMEN DATA FILM               |");
        System.out.println("+====================================================+");
        System.out.println(RESET);
        System.out.println(BOLD + "  Daftar Menu :" + RESET);
        System.out.println(CYAN + "  [1]" + RESET + " Insert Data Film");
        System.out.println(CYAN + "  [2]" + RESET + " Tampilkan Semua Data");
        System.out.println(CYAN + "  [3]" + RESET + " Update Data Film");
        System.out.println(CYAN + "  [4]" + RESET + " Hapus Data Film");
        System.out.println(CYAN + "  [5]" + RESET + " Cari Data Film");
        System.out.println(CYAN + "  [6]" + RESET + " Help");
        System.out.println(CYAN + "  [7]" + RESET + " Keluar");
        System.out.println(BOLD + CYAN + "+====================================================+" + RESET);
        System.out.println();
    }

    // Mencari index data berdasarkan ID, mengembalikan -1 jika tidak ditemukan
    public static int findIndex(int target) {
        for (int i = 0; i < dataFilm.size(); i++) {
            if (dataFilm.get(i).getId() == target) return i;
        }
        return -1;
    }

    // Memvalidasi apakah string merupakan bilangan (bulat atau desimal)
    public static boolean isNumber(String s, boolean isFloat) {
        if (s == null || s.isEmpty()) return false;
        int dot = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '.') {
                if (++dot > 1) return false;
                continue;
            }
            if (c < '0' || c > '9') return false;
        }
        if (!isFloat && dot > 0) return false;
        return true;
    }

    // Menerima input angka dari user dengan validasi tipe (0=bulat, 1=desimal)
    // defaultVal digunakan untuk fitur update (tekan enter = nilai lama)
    public static String inputNumber(String message, int type, String defaultVal) {
        String input;
        while (true) {
            System.out.print(message);
            input = scanner.nextLine();
            if (input.isEmpty() && defaultVal != null && !defaultVal.isEmpty()) return defaultVal;
            if (isNumber(input, type == 1)) return input;
            System.out.println(RED + "  [ERROR] Input harus berupa bilangan " + (type == 1 ? "desimal" : "bulat") + ".\n" + RESET);
        }
    }

    // Menerima input teks dari user, defaultVal jika input kosong
    public static String inputString(String message, String defaultVal) {
        System.out.print(message);
        String ans = scanner.nextLine();
        return (ans.isEmpty() && defaultVal != null) ? defaultVal : ans;
    }

    // Memperbarui lebar kolom tabel berdasarkan data terbaru
    public static void updateCol(int id, String nama, int durasi) {
        int len = String.valueOf(id).length();
        if (col[0] < len) col[0] = len;
        if (col[1] < nama.length()) col[1] = nama.length();
        len = String.valueOf(durasi).length();
        if (col[2] < len) col[2] = len;
    }

    // Mencetak garis pembatas tabel (+---+)
    public static void separator() {
        for (int i = 0; i < 4; i++) {
            System.out.print("+");
            for (int j = 0; j < col[i] + 2; j++) System.out.print("-");
        }
        System.out.println("+");
    }

    // Mencetak garis header tabel (+===+)
    public static void headerSeparator() {
        for (int i = 0; i < 4; i++) {
            System.out.print("+");
            for (int j = 0; j < col[i] + 2; j++) System.out.print("-");
        }
        System.out.println("+");
    }

    // Mencetak satu baris data dalam tabel
    public static void row(String[] cols) {
        for (int i = 0; i < 4; i++) {
            System.out.print("| " + cols[i]);
            for (int j = 0; j < col[i] - cols[i].length(); j++) System.out.print(" ");
            System.out.print(" ");
        }
        System.out.println("|");
    }

    // Mencetak satu data film dalam tabel
    public static void printTable(Film data) {
        String rate = String.format("%.2f", data.getRating());
        String[] r = {String.valueOf(data.getId()), data.getNama(), String.valueOf(data.getDurasi()), rate};
        row(r);
    }

    // Menu Insert - Menambahkan data film baru ke dalam ArrayList
    public static void insert() {
        System.out.println(BOLD + CYAN + "\n=============== Masukan Data Film ===============\n" + RESET);

        // Input ID dengan validasi jika sudah ada
        int id;
        while (true) {
            id = Integer.parseInt(inputNumber("  Masukan ID : ", 0, ""));
            if (findIndex(id) == -1) break;
            System.out.println(RED + "  [ERROR] ID sudah terpakai, gunakan ID lain\n" + RESET);
        }

        // Input data lainnya
        String nama = inputString("  Masukan Nama Film : ", "");
        int durasi = Integer.parseInt(inputNumber("  Masukan Durasi (menit) : ", 0, ""));
        float rating = Float.parseFloat(inputNumber("  Masukan Rating Film : ", 1, ""));

        // Update lebar kolom dan tambahkan data
        updateCol(id, nama, durasi);
        dataFilm.add(new Film(id, nama, durasi, rating));
        System.out.println(GREEN + "  [SUCSESS] Data Film berhasil ditambahkan!\n" + RESET);
    }

    // Menu Show - Menampilkan seluruh data film dalam bentuk tabel
    public static void show() {
        System.out.println(BOLD + CYAN + "\n=============== Data Film ===============\n" + RESET);
        if (dataFilm.isEmpty()) {
            System.out.println(YELLOW + "  Belum ada data yang tersimpan.\n" + RESET);
            return;
        }

        separator();
        row(headers);
        headerSeparator();
        for (Film data : dataFilm) printTable(data);
        separator();
        System.out.println();
    }

    // Menu Update - Memperbarui data film berdasarkan ID
    // Tekan enter pada input untuk mempertahankan nilai lama
    public static void update() {
        System.out.println(BOLD + CYAN + "\n=============== Update Data Film ===============\n" + RESET);
        int id = Integer.parseInt(inputNumber("  Masukan ID : ", 0, ""));
        int idx = findIndex(id);

        if (idx != -1) {
            Film data = dataFilm.get(idx);

            // Input ID baru dengan validasi
            id = Integer.parseInt(inputNumber("  Masukan ID baru [" + data.getId() + "] : ", 0, String.valueOf(data.getId())));
            while (id != data.getId() && findIndex(id) != -1) {
                System.out.println(RED + "  [ERROR] ID sudah terpakai, gunakan ID lain\n" + RESET);
                id = Integer.parseInt(inputNumber("  Masukan ID baru [" + data.getId() + "] : ", 0, String.valueOf(data.getId())));
            }

            // Input field lainnya (tekan enter = nilai lama)
            String nama = inputString("  Masukan Nama baru [" + data.getNama() + "] : ", data.getNama());
            int durasi = Integer.parseInt(inputNumber("  Masukan Durasi baru [" + data.getDurasi() + "] menit : ", 0, String.valueOf(data.getDurasi())));
            float rating = Float.parseFloat(inputNumber("  Masukan Rating Film [" + data.getRating() + "] : ", 1, String.valueOf(data.getRating())));

            // Update object
            data.setId(id);
            data.setNama(nama);
            data.setDurasi(durasi);
            data.setRating(rating);
            System.out.println(GREEN + "  [SUCSESS] Data Film berhasil diupdate!\n" + RESET);
        } else {
            System.out.println(RED + "  [ERROR] ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" + RESET);
        }
    }

    // Menu Delete - Menghapus data film berdasarkan ID
    public static void del() {
        System.out.println(BOLD + CYAN + "\n=============== Hapus Data Film ===============\n" + RESET);
        int id = Integer.parseInt(inputNumber("  Masukan ID Film : ", 0, ""));
        int idx = findIndex(id);

        if (idx != -1) {
            dataFilm.remove(idx);
            System.out.println(GREEN + "  [SUCSESS] Data Film berhasil dihapus!\n" + RESET);
        } else {
            System.out.println(RED + "  [ERROR] ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" + RESET);
        }
    }

    // Menu Search - Mencari dan menampilkan data film berdasarkan ID
    public static void searchData() {
        System.out.println(BOLD + CYAN + "\n=============== Cari Data Film ===============\n" + RESET);
        int id = Integer.parseInt(inputNumber("  Masukan ID Film : ", 0, ""));
        int idx = findIndex(id);

        if (idx != -1) {
            System.out.println(GREEN + "  [SUCSESS] Data ditemukan!\n" + RESET);
            separator();
            row(headers);
            headerSeparator();
            printTable(dataFilm.get(idx));
            separator();
            System.out.println();
        } else {
            System.out.println(RED + "  [ERROR] ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" + RESET);
        }
    }

    // Fungsi utama - Menampilkan menu dan memproses pilihan user
    public static void main(String[] args) {
        initCol();
        intro();

        boolean exit = false;
        while (!exit) { // Loop utama program
            System.out.print(BOLD + "  Pilih opsi [1-7] >> " + RESET);
            int option;
            try {
                option = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                option = 0;
            }

            // Menjalankan operasi sesuai pilihan user
            switch (option) {
                case 1: insert(); break;
                case 2: show(); break;
                case 3: update(); break;
                case 4: del(); break;
                case 5: searchData(); break;
                case 6: intro(); break;
                case 7:
                    System.out.println(GREEN + "\n  Sampai jumpa! Terima kasih telah menggunakan program ini.\n" + RESET);
                    exit = true;
                    break;
                default:
                    System.out.println(RED + "\n  [ERROR] Opsi tidak valid, silakan pilih antara 1 sampai 7.\n" + RESET);
            }
        }
        scanner.close();
    }
}
