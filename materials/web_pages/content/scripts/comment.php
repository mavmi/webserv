<?php
	echo var_dump($_POST) . "\n\n";
	echo var_dump($_SERVER) . "\n\n";
	echo var_dump($_REQUEST) . "\n\n";

	$nickname = "Undefine";
	$comment = "Undefine";
	if (isset($_POST["nickname"])){
		$nickname = $_POST["nickname"];
	}
	if (isset($_POST["comment"])){
		$comment = $_POST["comment"];
	}

	echo "\"" 
		. $nickname
		. ": \""
		. $comment
		. "\"";
?>
