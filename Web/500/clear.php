<?php

$loginform = <<<EOL
	Login:
	<form method="POST" action="#">
		<label>Username:</label><input type="text" name="user" /><br/>
		<label>Password:</label><input type="password" name="pass" /><br/>
		<input type="submit" name="action" value="login" />
	</form>
EOL;

$table = <<<EOL
	CREATE TABLE IF NOT EXISTS `users` ( 
		`user` varchar(64) DEFAULT NULL, 
		`pass` varchar(64) DEFAULT NULL 
	); 
EOL;

function createUser($user, $pass, $link)
{
	$sql = "INSERT INTO users (user, pass) VALUES ('$user', '$pass')";
	$res = mysql_query($sql, $link);
	return mysql_affected_rows()>0;
}

$link = mysql_connect("localhost", "web500", "password");
mysql_select_db("web500", $link);
mysql_query($table, $link);
$sql = "DELETE FROM users";
mysql_query($sql, $link);

createUser("admin", "bupass", $link);
?>
