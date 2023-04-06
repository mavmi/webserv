<?php
	echo $_POST . "\n";

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
