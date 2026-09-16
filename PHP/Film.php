<?php
class Film {
    private int $id;
    private string $nama;
    private int $durasi;
    private float $rating;
    private string $gambar;

    public function __construct(int $id = 0, string $nama = "", int $durasi = 0, float $rating = 0.0, string $gambar = "") {
        $this->id = $id;
        $this->nama = $nama;
        $this->durasi = $durasi;
        $this->rating = $rating;
        $this->gambar = $gambar;
    }

    // Getter dan Setter untuk id
    public function getId(): int { return $this->id; }
    public function setId(int $id): void { $this->id = $id; }

    // Getter dan Setter untuk nama
    public function getNama(): string { return $this->nama; }
    public function setNama(string $nama): void { $this->nama = $nama; }

    // Getter dan Setter untuk durasi
    public function getDurasi(): int { return $this->durasi; }
    public function setDurasi(int $durasi): void { $this->durasi = $durasi; }

    // Getter dan Setter untuk rating
    public function getRating(): float { return $this->rating; }
    public function setRating(float $rating): void { $this->rating = $rating; }

    // Getter dan Setter untuk gambar
    public function getGambar(): string { return $this->gambar; }
    public function setGambar(string $gambar): void { $this->gambar = $gambar; }
}
?>
