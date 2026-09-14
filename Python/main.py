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
    print(CYAN + "  [6]" + RESET + " Keluar")
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
            print(f"Input harus bilangan {'desimal' if is_float else 'bulat'}")

def insert():
    id = inputNumber("masukan ID : ")
    if searchId(id) != -1:
        print("data ID sudah ada")
        return

    nama = str(input("masukan nama film : "))
    durasi = inputNumber("masukan durasi (menit) : ")
    rating = inputNumber("masukan rating : ", True)

    now = Film(id, nama, durasi, rating)
    dataFilm.append(now)

def show():
    table_data = []
    for data in dataFilm:
        table_data.append([data.getId(), data.getNama(), data.getDurasi(), data.getRating()])
    headers = ["ID", "Nama Film", "Durasi (menit)", "Rating"]
    print(tabulate(table_data, headers=headers, tablefmt="grid"))

def updateNumber(message, currentVal, is_float=False):
    while True:
        ans = input(message)
        if ans == "": return currentVal
        try:
            return float(ans) if is_float else int(ans)
        except ValueError:
            print(f"Input harus bilangan {'desimal' if is_float else 'bulat'}")

def update():
    idInput = inputNumber("masukan ID : ")
    idx = searchId(idInput)
    if idx == -1:
        print("data ID tidak ada")
        return

    while True:
        newId = updateNumber("Masukan ID baru : ", dataFilm[idx].getId())
        cek = searchId(newId)
        if cek != -1 and dataFilm[cek].getId() != dataFilm[idx].getId(): print("Data ID sudah ada")
        else:
            dataFilm[idx].setId(newId)
            break

    nama = str(input("masukan nama film : "))
    durasi = updateNumber("masukan durasi (menit) : ", dataFilm[idx].getDurasi())
    rating = updateNumber("masukan rating : ", dataFilm[idx].getRating(), True)

    dataFilm[idx].setNama(nama)
    dataFilm[idx].setDurasi(durasi)
    dataFilm[idx].setRating(rating)

def delete():
    idInput = inputNumber("masukan ID Film : ")
    idx = searchId(idInput)
    if idx == -1:
        print("data ID tidak ada")
        return

    dataFilm.pop(idx)
    print("data berhasil dihapus")

def search():
    idInput = inputNumber("masukan ID Film : ")
    idx = searchId(idInput)
    if idx == -1:
        print("data ID tidak ada")
        return

    data = dataFilm[idx]
    table_data = [[data.getId(), data.getNama(), data.getDurasi(), data.getRating()]]
    headers = ["ID", "Nama Film", "Durasi (menit)", "Rating"]
    print(tabulate(table_data, headers=headers, tablefmt="grid"))

def main():
    intro()

    exit = False
    while not exit:
        option = int(input(BOLD + "  Pilih opsi [1-6] >> " + RESET))

        match option:
            case 1: insert()
            case 2: show()
            case 3: update()
            case 4: delete()
            case 5: search()
            case 6:
                print(GREEN + "\n  Sampai jumpa! Terima kasih telah menggunakan program ini.\n" + RESET)
                exit = True
            case _:
                print(RED + "\n  Opsi tidak valid, silakan pilih antara 1 sampai 6." + RESET)


if __name__ == "__main__":
    main()
