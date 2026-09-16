public class Film {
    // Atribut private untuk encapshidroid
    private int id;
    private String nama;
    private int durasi;
    private float rating;

    // Constructor default - menginisialisasi atribut dengan nilai default
    public Film() {
        this.id = 0;
        this.nama = "";
        this.durasi = 0;
        this.rating = 0.0f;
    }

    // Constructor parameterized - menginisialisasi atribut dengan nilai yang diberikan
    public Film(int id, String nama, int durasi, float rating) {
        this.id = id;
        this.nama = nama;
        this.durasi = durasi;
        this.rating = rating;
    }

    // Getter and Setter for id
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    // Getter and Setter for nama
    public String getNama() { return nama; }
    public void setNama(String nama) { this.nama = nama; }

    // Getter and Setter for durasi
    public int getDurasi() { return durasi; }
    public void setDurasi(int durasi) { this.durasi = durasi; }

    // Getter and Setter for rating
    public float getRating() { return rating; }
    public void setRating(float rating) { this.rating = rating; }
}
