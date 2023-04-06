<?php
	$a = explode('&', $_SERVER["QUERY_STRING"]);
	$n = substr($a[0], strpos($a[0], '=') + 1);
	$c = substr($a[1], strpos($a[1], '=') + 1);
	$nickname = "Undefine";
	$comment = "Undefine";

	if (strlen($n)){
		$nickname = $n;
	}
	if (strlen($c)){
		$comment =$c;
	}

	echo "\"" 
		. $nickname
		. ": \""
		. $comment
		. "\"";
?>
