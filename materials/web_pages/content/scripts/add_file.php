<?php
	$uploaddir = '../../../uploaded/';
	$uploadfile = $uploaddir . basename($n);

	if (move_uploaded_file($n, $uploadfile)) {
		include (dirname(__DIR__).'/success_upload.html');
	} else {
		include (dirname(__DIR__).'/unsuccess_upload.html');
	}
?>
