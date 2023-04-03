<?php
	echo "Hi";
	echo htmlspecialchars($_POST['name']);
	echo " ";
	echo htmlspecialchars($_POST['lastname']);
	echo ". You are";
	echo htmlspecialchars($_POST['age']);
	echo " years old";
?>

