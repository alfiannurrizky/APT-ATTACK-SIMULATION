<?php
$uploadDir = '../uploads/';
if (!is_dir($uploadDir)) {
    mkdir($uploadDir, 0777, true);
}

$allowedExtensions = ['txt','jpg','png','jpeg','pdf', 'xlsx', 'csv', 'doc', 'docx', 'ppt', 'pptx'];

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['file'])) {
    $fileName = $_FILES['file']['name'];
    $fileTmp = $_FILES['file']['tmp_name'];
    $fileExt = pathinfo($fileName, PATHINFO_EXTENSION);
    
    if (in_array(strtolower($fileExt), $allowedExtensions)) {
        $uploadFile = $uploadDir . basename($fileName);
        if (move_uploaded_file($fileTmp, $uploadFile)) {
            echo "File " . htmlspecialchars($fileName) . " uploaded successfully!";
        } else {
            echo "Error uploading file.";
        }
    } else {
        echo "Invalid file type. Only document files are allowed.";
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Upload File</title>
</head>
<body>
    <h1>Upload File</h1>
    <form action="" method="post" enctype="multipart/form-data">
        <input type="file" name="file">
        <input type="submit" value="Upload">
    </form>
</body>
</html>