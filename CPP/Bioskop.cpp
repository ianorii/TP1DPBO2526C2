using namespace std;

class Bioskop {
    private:
        int id;
        string name;
        string address;
        int totalStudios;
        float rating;

    public:
        Bioskop() {
            id = 0;
            name = "";
            address = "";
            totalStudios = 0;
            rating = 0.00;
        }

        Bioskop(int id, string name, string address, int totalStudios, float rating) {
            this->id = id;
            this->name = name;
            this->address = address;
            this->totalStudios = totalStudios;
            this->rating = rating;
        }

        // Setter and Getter for id
        void setId(int id) {
            this->id = id;
        }
        int getId() {
            return id;
        }

        // Setter and Getter for name
        void setName(string name) {
            this->name = name;
        }
        string getName() {
            return name;
        }

        // Setter and Getter for address
        void setAddress(string address) {
            this->address = address;
        }
        string getAddress() {
            return address;
        }

        // Setter and Getter for totalStudios
        void setTotalStudios(int totalStudios) {
            this->totalStudios = totalStudios;
        }
        int getTotalStudios() {
            return totalStudios;
        }

        // Setter and Getter for rating
        void setRating(float rating) {
            this->rating = rating;
        }
        float getRating() {
            return rating;
        }

        ~Bioskop() {}
};