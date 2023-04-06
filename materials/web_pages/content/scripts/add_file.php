<?php
	$n = substr($_SERVER["QUERY_STRING"], strpos($_SERVER["QUERY_STRING"], '=') + 1);
	echo $n . "\n\n";

	$uploaddir = '../../../uploaded/';
	$uploadfile = $uploaddir . basename($n);

	if (move_uploaded_file($n, $uploadfile)) {
		include (dirname(__DIR__).'/success_upload.html');
	} else {
		include (dirname(__DIR__).'/unsuccess_upload.html');
	}
?>
