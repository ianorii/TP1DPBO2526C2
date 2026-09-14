using namespace std;

class Film {
    private:
        int id;
        string nama;
        int durasi;
        float rating;

    public:
        Film() {
            id = 0;
            nama = "";
            durasi = 0;
            rating = 0.00;
        }

        Film(int id, string nama, int durasi, float rating) {
            this->id = id;
            this->nama = nama;
            this->durasi = durasi;
            this->rating = rating;
        }

        // Setter and Getter for id
        void setId(int id) {
            this->id = id;
        }
        int getId() {
            return id;
        }

        // Setter and Getter for nama
        void setNama(string nama) {
            this->nama = nama;
        }
        string getNama() {
            return nama;
        }

        // Setter and Getter for durasi
        void setDurasi(int durasi) {
            this->durasi = durasi;
        }
        int getDurasi() {
            return durasi;
        }

        // Setter and Getter for rating
        void setRating(float rating) {
            this->rating = rating;
        }
        float getRating() {
            return rating;
        }

        ~Film() {}
};
