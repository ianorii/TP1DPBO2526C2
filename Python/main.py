from Film import Film
from tabulate import tabulate

RESET ="\033[0m"
RED ="\033[31m"
GREEN ="\033[32m"
CYAN ="\033[36m"
YELLOW ="\033[33m"
BOLD ="\033[1m"

dataFilm = []

def intro():
    print(BOLD + CYAN)
    print("+====================================================+")
    print("|           SISTEM MANAJEMEN DATA FILM               |")
    print("+====================================================+")
    print(RESET)
    print(BOLD + "  Daftar Menu :" + RESET)
    print(CYAN + "  [1]" + RESET + " Insert Data Film")
    print(CYAN + "  [2]" + RESET + " Tampilkan Semua Data")
    print(CYAN + "  [3]" + RESET + " Update Data Film")
    print(CYAN + "  [4]" + RESET + " Hapus Data Film")
    print(CYAN + "  [5]" + RESET + " Cari Data Film")
    print(CYAN + "  [6]" + RESET + " Help")
    print(CYAN + "  [7]" + RESET + " Keluar")
    print(BOLD + CYAN)
    print("+====================================================+")
    print(RESET)

def searchId(target:int):
    for i, data in enumerate(dataFilm):
        if data.getId() == target : return i
    return -1

def inputNumber(message:str, is_float:bool=False):
    while True:
        try:
            return float(input(message)) if is_float else int(input(message))
        except ValueError:
            print(RED + "  [ERROR] Input harus berupa bilangan " + ("desimal" if is_float else "bulat") + "." + RESET)

def insert():
    print(BOLD + CYAN + "\n=============== Masukan Data Film ===============\n" + RESET)

    id = inputNumber("  Masukan ID : ")
    while searchId(id) != -1:
        print(RED + "  [ERROR] ID sudah terpakai, gunakan ID lain" + RESET)
        id = inputNumber("  Masukan ID : ")

    nama = str(input("  Masukan Nama Film : "))
    durasi = inputNumber("  Masukan Durasi (menit) : ")
    rating = inputNumber("  Masukan Rating Film : ", True)

    now = Film(id, nama, durasi, rating)
    dataFilm.append(now)
    print(GREEN + "\n  [SUCSESS] Data Film berhasil ditambahkan!\n" + RESET)

def show():
    print(BOLD + CYAN + "\n=============== Data Film ===============\n" + RESET)
    if not dataFilm:
        print(YELLOW + "  Belum ada data yang tersimpan.\n" + RESET)
        return

    table_data = []
    for data in dataFilm:
        table_data.append([data.getId(), data.getNama(), data.getDurasi(), data.getRating()])
    headers = ["ID", "Nama Film", "Durasi (menit)", "Rating"]
    print(tabulate(table_data, headers=headers, tablefmt="grid"))
    print()

def updateNumber(message, currentVal, is_float=False):
    while True:
        ans = input(message)
        if ans == "": return currentVal
        try:
            return float(ans) if is_float else int(ans)
        except ValueError:
            print(RED + "  [ERROR] Input harus berupa bilangan " + ("desimal" if is_float else "bulat") + "." + RESET)

def update():
    print(BOLD + CYAN + "\n=============== Update Data Film ===============\n" + RESET)
    idInput = inputNumber("  Masukan ID : ")
    idx = searchId(idInput)
    if idx == -1:
        print(RED + "\n  [ERROR] ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" + RESET)
        return

    while True:
        newId = updateNumber("  Masukan ID baru [" + str(dataFilm[idx].getId()) + "] : ", dataFilm[idx].getId())
        cek = searchId(newId)
        if cek != -1 and dataFilm[cek].getId() != dataFilm[idx].getId():
            print(RED + "  [ERROR] ID sudah terpakai, gunakan ID lain" + RESET)
        else:
            dataFilm[idx].setId(newId)
            break

    nama = str(input("  Masukan Nama baru [" + dataFilm[idx].getNama() + "] : "))
    if nama == "": nama = dataFilm[idx].getNama()
    durasi = updateNumber("  Masukan Durasi baru [" + str(dataFilm[idx].getDurasi()) + "] menit : ", dataFilm[idx].getDurasi())
    rating = updateNumber("  Masukan Rating Film [" + str(dataFilm[idx].getRating()) + "] : ", dataFilm[idx].getRating(), True)

    dataFilm[idx].setNama(nama)
    dataFilm[idx].setDurasi(durasi)
    dataFilm[idx].setRating(rating)
    print(GREEN + "\n  [SUCSESS] Data Film berhasil diupdate!\n" + RESET)

def delete():
    print(BOLD + CYAN + "\n=============== Hapus Data Film ===============\n" + RESET)
    idInput = inputNumber("  Masukan ID Film : ")
    idx = searchId(idInput)
    if idx == -1:
        print(RED + "\n  [ERROR] ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" + RESET)
        return

    dataFilm.pop(idx)
    print(GREEN + "\n  [SUCSESS] Data Film berhasil dihapus!\n" + RESET)

def search():
    print(BOLD + CYAN + "\n=============== Cari Data Film ===============\n" + RESET)
    idInput = inputNumber("  Masukan ID Film : ")
    idx = searchId(idInput)
    if idx == -1:
        print(RED + "\n  [ERROR] ID tidak ditemukan, pastikan ID yang dimasukkan benar.\n" + RESET)
        return

    print(GREEN + "  [SUCSESS] Data ditemukan!\n" + RESET)
    data = dataFilm[idx]
    table_data = [[data.getId(), data.getNama(), data.getDurasi(), data.getRating()]]
    headers = ["ID", "Nama Film", "Durasi (menit)", "Rating"]
    print(tabulate(table_data, headers=headers, tablefmt="grid"))
    print()

def main():
    intro()

    exit = False
    while not exit:
        option = int(input(BOLD + "  Pilih opsi [1-7] >> " + RESET))

        match option:
            case 1: insert()
            case 2: show()
            case 3: update()
            case 4: delete()
            case 5: search()
            case 6: intro()
            case 7:
                print(GREEN + "\n  Sampai jumpa! Terima kasih telah menggunakan program ini.\n" + RESET)
                exit = True
            case _:
                print(RED + "\n  [ERROR] Opsi tidak valid, silakan pilih antara 1 sampai 7.\n" + RESET)


if __name__ == "__main__":
    main()
