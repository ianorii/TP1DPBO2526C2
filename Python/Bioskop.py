class Bioskop:
    # constructor
    def __init__(self, id:int, name:str, address:str, totalStudios:int, rating:float):
        self.__id = id
        self.__name = name
        self.__address = address
        self.__totalStudios = totalStudios
        self.__rating = rating

    # Setter and Getter for ID
    def setId(self, id): self.__id = id
    def getId(self): return self.__id

    # Setter and Getter for name
    def setName(self, name): self.__name = name
    def getName(self): return self.__name

    # Setter and Getter for address
    def setAddress(self, address): self.__address = address
    def getAddress(self): return self.__address

    # Setter and Getter for totalStudios
    def setTotalStudios(self, totalStudios): self.__totalStudios = totalStudios
    def getTotalStudios(self): return self.__totalStudios

    # Setter and Getter for rating
    def setRating(self, rating): self.__rating = rating
    def getRating(self): return self.__rating