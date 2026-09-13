from Bioskop import Bioskop

RESET ="\033[0m"
RED ="\033[31m"
GREEN ="\033[32m"
CYAN ="\033[36m"
YELLOW ="\033[33m"
BOLD ="\033[1m"

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

def main():
    intro()

    exit = False
    while not exit:
        option = int(input(BOLD + "  Pilih opsi [1-6] >> " + RESET))

        if option == 6:
            print(GREEN + "\n  Sampai jumpa! Terima kasih telah menggunakan program ini.\n" + RESET);
            exit = True;


if __name__ == "__main__":
    main()