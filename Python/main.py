from Bioskop import Bioskop
from tabulate import tabulate

RESET ="\033[0m"
RED ="\033[31m"
GREEN ="\033[32m"
CYAN ="\033[36m"
YELLOW ="\033[33m"
BOLD ="\033[1m"

dataBioskop = []

def intro():
    print(BOLD + CYAN)
    print("+====================================================+")
    print("|           SISTEM MANAJEMEN DATA BIOSKOP            |")
    print("+====================================================+")
    print(RESET)
    print(BOLD + "  Daftar Menu :" + RESET)
    print(CYAN + "  [1]" + RESET + " Insert Data Bioskop")
    print(CYAN + "  [2]" + RESET + " Tampilkan Semua Data")
    print(CYAN + "  [3]" + RESET + " Update Data Bioskop")
    print(CYAN + "  [4]" + RESET + " Hapus Data Bioskop")
    print(CYAN + "  [5]" + RESET + " Cari Data Bioskop")
    print(CYAN + "  [6]" + RESET + " Keluar")
    print(BOLD + CYAN)
    print("+====================================================+")
    print(RESET)

def searchId(target:int):
    for data in dataBioskop:
        if data.getId() == target : return True
    return False

def inputInteger(message:str):
    while True:
        ans = input(message)
        try: ans = int(ans)
        except ValueError:
            print("masukin angka aja")
            continue
        return ans

def inputFloat(message:str):
    while True:
        ans = input(message)
        try: ans = float(ans)
        except ValueError:
            print("ini bukan bilangan float")
            continue
        return ans

def insert():
    while True:
        id = inputInteger("masukan ID : ")
        if searchId(id): print("data ID sudah ada")
        else: break

    name = str(input("masukan nama bioskop : "))
    address = str(input("masukan alamat bioskop : "))
    totalStudios = inputInteger("masukan total studio : ")
    rating = inputFloat("masukan rating : ")

    now = Bioskop(id, name, address, totalStudios, rating)
    dataBioskop.append(now)

def show():
    table_data = []
    for data in dataBioskop:
        table_data.append([data.getId(), data.getName(), data.getAddress(), data.getTotalStudios(), data.getRating()])
    headers = ["ID", "Nama Bioskop", "Alamat", "Total Studio", "Rating"]
    print(tabulate(table_data, headers=headers, tablefmt="grid"))

def main():
    intro()

    exit = False
    while not exit:
        option = int(input(BOLD + "  Pilih opsi [1-6] >> " + RESET))

        match option:
            case 1: insert()
            case 2: show()

            # case 3:

            # case 4:

            # case 5:

            case 6:
                print(GREEN + "\n  Sampai jumpa! Terima kasih telah menggunakan program ini.\n" + RESET)
                exit = True
            case _:
                print(RED + "\n  Opsi tidak valid, silakan pilih antara 1 sampai 6." + RESET)


if __name__ == "__main__":
    main()