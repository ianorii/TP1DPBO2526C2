<?php
require 'Film.php';
session_start();

// Inisialisasi data film dari session atau array kosong
if (!isset($_SESSION['dataFilm'])) {
    $_SESSION['dataFilm'] = [];
}

// Fungsi untuk mencari index berdasarkan ID
function findIndex(array $data, int $target): int {
    for ($i = 0; $i < count($data); $i++) {
        if ($data[$i]->getId() == $target) return $i;
    }
    return -1;
}

// Fungsi untuk mendapatkan ID baru (auto-increment)
function getNewId(array $data): int {
    $maxId = 0;
    foreach ($data as $film) {
        if ($film->getId() > $maxId) {
            $maxId = $film->getId();
        }
    }
    return $maxId + 1;
}

// Fungsi untuk upload gambar
function uploadGambar(array $file): string {
    $targetDir = "image/";
    $fileName = basename($file["name"]);
    $targetFilePath = $targetDir . $fileName;
    $fileType = pathinfo($targetFilePath, PATHINFO_EXTENSION);

    // Validasi tipe file gambar
    $allowTypes = ['jpg', 'jpeg', 'png', 'gif', 'webp'];
    if (!in_array(strtolower($fileType), $allowTypes)) {
        return "";
    }

    // Upload file
    if (move_uploaded_file($file["tmp_name"], $targetFilePath)) {
        return $targetFilePath;
    }
    return "";
}

// Proses form submission
$message = "";
$messageType = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $action = $_POST['action'] ?? '';

    // INSERT
    if ($action == 'insert') {
        $id = getNewId($_SESSION['dataFilm']);
        $nama = htmlspecialchars($_POST['nama'] ?? '');
        $durasi = (int)($_POST['durasi'] ?? 0);
        $rating = (float)($_POST['rating'] ?? 0);
        $gambar = "";

        // Upload gambar jika ada
        if (isset($_FILES['gambar']) && $_FILES['gambar']['error'] == 0) {
            $gambar = uploadGambar($_FILES['gambar']);
        }

        $film = new Film($id, $nama, $durasi, $rating, $gambar);
        $_SESSION['dataFilm'][] = $film;
        $message = "Data Film berhasil ditambahkan!";
        $messageType = "success";
    }

    // UPDATE
    if ($action == 'update') {
        $id = (int)($_POST['id'] ?? 0);
        $idx = findIndex($_SESSION['dataFilm'], $id);

        if ($idx != -1) {
            $film = $_SESSION['dataFilm'][$idx];
            $film->setNama(htmlspecialchars($_POST['nama'] ?? $film->getNama()));
            $film->setDurasi((int)($_POST['durasi'] ?? $film->getDurasi()));
            $film->setRating((float)($_POST['rating'] ?? $film->getRating()));

            // Upload gambar baru jika ada
            if (isset($_FILES['gambar']) && $_FILES['gambar']['error'] == 0) {
                $gambar = uploadGambar($_FILES['gambar']);
                if ($gambar != "") {
                    $film->setGambar($gambar);
                }
            }

            $_SESSION['dataFilm'][$idx] = $film;
            $message = "Data Film berhasil diupdate!";
            $messageType = "success";
        } else {
            $message = "ID tidak ditemukan!";
            $messageType = "error";
        }
    }

    // DELETE
    if ($action == 'delete') {
        $id = (int)($_POST['id'] ?? 0);
        $idx = findIndex($_SESSION['dataFilm'], $id);

        if ($idx != -1) {
            array_splice($_SESSION['dataFilm'], $idx, 1);
            $message = "Data Film berhasil dihapus!";
            $messageType = "success";
        } else {
            $message = "ID tidak ditemukan!";
            $messageType = "error";
        }
    }
}

// Proses pencarian
$searchResult = null;
$searchId = $_GET['search_id'] ?? '';
if ($searchId != '') {
    $searchId = (int)$searchId;
    $idx = findIndex($_SESSION['dataFilm'], $searchId);
    if ($idx != -1) {
        $searchResult = $_SESSION['dataFilm'][$idx];
    }
}

// Proses edit
$editFilm = null;
$editId = $_GET['edit_id'] ?? '';
if ($editId != '') {
    $editId = (int)$editId;
    $idx = findIndex($_SESSION['dataFilm'], $editId);
    if ($idx != -1) {
        $editFilm = $_SESSION['dataFilm'][$idx];
    }
}
?>

<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sistem Manajemen Data Film</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
        }
        .container {
            max-width: 1000px;
            margin: 0 auto;
        }
        .header {
            text-align: center;
            color: white;
            margin-bottom: 30px;
        }
        .header h1 {
            font-size: 2.5em;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
        }
        .header p {
            font-size: 1.1em;
            opacity: 0.9;
        }
        .card {
            background: white;
            border-radius: 15px;
            padding: 25px;
            margin-bottom: 20px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
        }
        .card h2 {
            color: #667eea;
            margin-bottom: 20px;
            padding-bottom: 10px;
            border-bottom: 2px solid #667eea;
        }
        .form-group {
            margin-bottom: 15px;
        }
        .form-group label {
            display: block;
            margin-bottom: 5px;
            font-weight: 600;
            color: #333;
        }
        .form-group input, .form-group select {
            width: 100%;
            padding: 12px;
            border: 2px solid #ddd;
            border-radius: 8px;
            font-size: 14px;
            transition: border-color 0.3s;
        }
        .form-group input:focus, .form-group select:focus {
            outline: none;
            border-color: #667eea;
        }
        .btn {
            padding: 12px 25px;
            border: none;
            border-radius: 8px;
            font-size: 14px;
            font-weight: 600;
            cursor: pointer;
            transition: transform 0.2s, box-shadow 0.2s;
        }
        .btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(0,0,0,0.2);
        }
        .btn-primary {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
        }
        .btn-success {
            background: linear-gradient(135deg, #11998e 0%, #38ef7d 100%);
            color: white;
        }
        .btn-warning {
            background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
            color: white;
        }
        .btn-danger {
            background: linear-gradient(135deg, #eb3349 0%, #f45c43 100%);
            color: white;
        }
        .btn-info {
            background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%);
            color: white;
        }
        .btn-group {
            display: flex;
            gap: 10px;
            margin-top: 15px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 15px;
        }
        table th, table td {
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #ddd;
        }
        table th {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            font-weight: 600;
        }
        table tr:hover {
            background: #f5f5f5;
        }
        table img {
            width: 80px;
            height: 80px;
            object-fit: cover;
            border-radius: 8px;
        }
        .message {
            padding: 15px;
            border-radius: 8px;
            margin-bottom: 20px;
            font-weight: 600;
        }
        .message.success {
            background: #d4edda;
            color: #155724;
            border: 1px solid #c3e6cb;
        }
        .message.error {
            background: #f8d7da;
            color: #721c24;
            border: 1px solid #f5c6cb;
        }
        .search-box {
            display: flex;
            gap: 10px;
            margin-bottom: 20px;
        }
        .search-box input {
            flex: 1;
            padding: 12px;
            border: 2px solid #ddd;
            border-radius: 8px;
            font-size: 14px;
        }
        .search-box input:focus {
            outline: none;
            border-color: #667eea;
        }
        .film-detail {
            display: flex;
            gap: 30px;
            align-items: flex-start;
        }
        .film-detail img {
            width: 200px;
            height: 300px;
            object-fit: cover;
            border-radius: 10px;
        }
        .film-info {
            flex: 1;
        }
        .film-info h3 {
            color: #333;
            margin-bottom: 15px;
            font-size: 1.5em;
        }
        .film-info p {
            margin-bottom: 10px;
            color: #666;
        }
        .film-info strong {
            color: #333;
        }
        .no-image {
            width: 200px;
            height: 300px;
            background: #f0f0f0;
            display: flex;
            align-items: center;
            justify-content: center;
            border-radius: 10px;
            color: #999;
        }
        .form-row {
            display: flex;
            gap: 15px;
        }
        .form-row .form-group {
            flex: 1;
        }
        .empty-state {
            text-align: center;
            padding: 40px;
            color: #999;
        }
        .empty-state h3 {
            margin-bottom: 10px;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>SISTEM MANAJEMEN DATA FILM</h1>
            <p>Kelola data film Anda dengan mudah</p>
        </div>

        <!-- Pesan Notifikasi -->
        <?php if ($message != ''): ?>
            <div class="message <?= $messageType ?>">
                <?= $message ?>
            </div>
        <?php endif; ?>

        <!-- Form Insert/Edit -->
        <div class="card">
            <h2><?= $editFilm ? 'Edit Data Film' : 'Tambah Data Film' ?></h2>
            <form method="POST" enctype="multipart/form-data">
                <input type="hidden" name="action" value="<?= $editFilm ? 'update' : 'insert' ?>">
                <?php if ($editFilm): ?>
                    <input type="hidden" name="id" value="<?= $editFilm->getId() ?>">
                <?php endif; ?>

                <div class="form-row">
                    <div class="form-group">
                        <label>Nama Film</label>
                        <input type="text" name="nama" value="<?= $editFilm ? $editFilm->getNama() : '' ?>" required>
                    </div>
                    <div class="form-group">
                        <label>Durasi (menit)</label>
                        <input type="number" name="durasi" value="<?= $editFilm ? $editFilm->getDurasi() : '' ?>" required>
                    </div>
                </div>

                <div class="form-row">
                    <div class="form-group">
                        <label>Rating (0-10)</label>
                        <input type="number" name="rating" step="0.01" min="0" max="10" value="<?= $editFilm ? $editFilm->getRating() : '' ?>" required>
                    </div>
                    <div class="form-group">
                        <label>Gambar Poster</label>
                        <input type="file" name="gambar" accept="image/*">
                    </div>
                </div>

                <div class="btn-group">
                    <button type="submit" class="btn <?= $editFilm ? 'btn-warning' : 'btn-success' ?>">
                        <?= $editFilm ? 'Update' : 'Tambah' ?>
                    </button>
                    <?php if ($editFilm): ?>
                        <a href="Main.php" class="btn btn-info">Batal</a>
                    <?php endif; ?>
                </div>
            </form>
        </div>

        <!-- Pencarian -->
        <div class="card">
            <h2>Cari Data Film</h2>
            <form method="GET" class="search-box">
                <input type="number" name="search_id" placeholder="Masukkan ID Film..." value="<?= $searchId ?>">
                <button type="submit" class="btn btn-primary">Cari</button>
                <?php if ($searchId != ''): ?>
                    <a href="Main.php" class="btn btn-info">Reset</a>
                <?php endif; ?>
            </form>

            <!-- Hasil Pencarian -->
            <?php if ($searchResult): ?>
                <div class="film-detail">
                    <?php if ($searchResult->getGambar() != ''): ?>
                        <img src="<?= $searchResult->getGambar() ?>" alt="<?= $searchResult->getNama() ?>">
                    <?php else: ?>
                        <div class="no-image">Tidak ada gambar</div>
                    <?php endif; ?>

                    <div class="film-info">
                        <h3><?= $searchResult->getNama() ?></h3>
                        <p><strong>ID:</strong> <?= $searchResult->getId() ?></p>
                        <p><strong>Durasi:</strong> <?= $searchResult->getDurasi() ?> menit</p>
                        <p><strong>Rating:</strong> <?= number_format($searchResult->getRating(), 2) ?></p>
                        <div class="btn-group">
                            <a href="Main.php?edit_id=<?= $searchResult->getId() ?>" class="btn btn-warning">Edit</a>
                            <form method="POST" style="display:inline;">
                                <input type="hidden" name="action" value="delete">
                                <input type="hidden" name="id" value="<?= $searchResult->getId() ?>">
                                <button type="submit" class="btn btn-danger" onclick="return confirm('Yakin ingin menghapus?')">Hapus</button>
                            </form>
                        </div>
                    </div>
                </div>
            <?php elseif ($searchId != ''): ?>
                <div class="empty-state">
                    <h3>Film tidak ditemukan</h3>
                    <p>ID <?= $searchId ?> tidak ada dalam database</p>
                </div>
            <?php endif; ?>
        </div>

        <!-- Tabel Semua Data -->
        <div class="card">
            <h2>Semua Data Film (<?= count($_SESSION['dataFilm']) ?> Film)</h2>

            <?php if (empty($_SESSION['dataFilm'])): ?>
                <div class="empty-state">
                    <h3>Belum ada data film</h3>
                    <p>Silakan tambahkan data film baru di form atas</p>
                </div>
            <?php else: ?>
                <table>
                    <thead>
                        <tr>
                            <th>ID</th>
                            <th>Gambar</th>
                            <th>Nama Film</th>
                            <th>Durasi</th>
                            <th>Rating</th>
                            <th>Aksi</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($_SESSION['dataFilm'] as $film): ?>
                            <tr>
                                <td><?= $film->getId() ?></td>
                                <td>
                                    <?php if ($film->getGambar() != ''): ?>
                                        <img src="<?= $film->getGambar() ?>" alt="<?= $film->getNama() ?>">
                                    <?php else: ?>
                                        <span>Tidak ada gambar</span>
                                    <?php endif; ?>
                                </td>
                                <td><?= $film->getNama() ?></td>
                                <td><?= $film->getDurasi() ?> menit</td>
                                <td><?= number_format($film->getRating(), 2) ?></td>
                                <td>
                                    <div class="btn-group">
                                        <a href="Main.php?edit_id=<?= $film->getId() ?>" class="btn btn-warning">Edit</a>
                                        <form method="POST" style="display:inline;">
                                            <input type="hidden" name="action" value="delete">
                                            <input type="hidden" name="id" value="<?= $film->getId() ?>">
                                            <button type="submit" class="btn btn-danger" onclick="return confirm('Yakin ingin menghapus?')">Hapus</button>
                                        </form>
                                    </div>
                                </td>
                            </tr>
                        <?php endforeach; ?>
                    </tbody>
                </table>
            <?php endif; ?>
        </div>
    </div>
</body>
</html>
