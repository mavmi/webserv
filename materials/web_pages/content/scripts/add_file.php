<?php
	$uploaddir = '../../../uploaded/';
	$uploadfile = $uploaddir . basename($_FILES['filename']['name']);

	if (move_uploaded_file($_FILES['filename']['tmp_name'], $uploadfile)) {
		header('Location: ../success_upload.html', 200);
	} else {
		header('Location: ../unsuccess_upload.html', 200);
	}
?>
