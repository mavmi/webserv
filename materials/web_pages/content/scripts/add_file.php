<?php
	$uploaddir = '../../../uploaded/';
	$uploadfile = $uploaddir . basename($_FILES['filename']['name']);

	if (move_uploaded_file($_FILES['filename']['tmp_name'], $uploadfile)) {
		include (dirname(__DIR__).'/success_upload.html');
	} else {
		include (dirname(__DIR__).'/unsuccess_upload.html');
	}
?>
