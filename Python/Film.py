class Film:
    # constructor
    def __init__(self, id:int, nama:str, durasi:int, rating:float):
        self.__id = id
        self.__nama = nama
        self.__durasi = durasi
        self.__rating = rating

    # Setter and Getter for ID
    def setId(self, id): self.__id = id
    def getId(self): return self.__id

    # Setter and Getter for nama
    def setNama(self, nama): self.__nama = nama
    def getNama(self): return self.__nama

    # Setter and Getter for durasi
    def setDurasi(self, durasi): self.__durasi = durasi
    def getDurasi(self): return self.__durasi

    # Setter and Getter for rating
    def setRating(self, rating): self.__rating = rating
    def getRating(self): return self.__rating
