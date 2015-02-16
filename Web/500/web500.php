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
	CREATE TABLE IF NOT EXISTS `web500_users` ( 
		`user` varchar(64) DEFAULT NULL, 
		`pass` varchar(64) DEFAULT NULL 
	); 
EOL;

function userExists($user, $link)
{
	$sql = "SELECT * FROM web500_users WHERE user='$user'";
	$res = mysql_query($sql, $link);
	return mysql_num_rows($res)>0;
}

function auth($user, $pass, $link)
{
	$sql = "SELECT * FROM web500_users WHERE user='$user' and pass='$pass'";
	$res = mysql_query($sql, $link);
	return mysql_num_rows($res)>0;
}

function printData($user,$link)
{
	$sql = "SELECT * FROM web500_users WHERE user='$user'";
	$res = mysql_query($sql, $link);
	if(mysql_num_rows($res)>0)
		print_r(mysql_fetch_assoc($res));
}

function deleteUsers($link)
{
	$flag = "<sansurBOYLEkotuBISIiste>";
	$user = "<sansurBOYLEkotuBISIiste>";
	$sql = "DELETE FROM web500_users;";
	$res = mysql_query($sql, $link);
	createUser($user, $flag, $link, false);
}

function createUser($user, $pass, $link, $clear=true)
{
	if($clear)
		deleteUsers($link);
	$sql = "INSERT INTO web500_users (user, pass) VALUES ('$user', '$pass')";
	$res = mysql_query($sql, $link);
	return mysql_affected_rows()>0;
}

if(array_key_exists('user', $_POST) && array_key_exists('pass', $_POST))
{
	$link = mysql_connect("<sansurBOYLEkotuBISIiste>", "<sansurBOYLEkotuBISIiste>", "<sansurBOYLEkotuBISIiste>");
	mysql_select_db("<sansurBOYLEkotuBISIiste>", $link);
	mysql_query($table, $link);
	
	$user = htmlspecialchars(mysql_real_escape_string($_POST['user']));
	$pass = htmlspecialchars(mysql_real_escape_string($_POST['pass']));
	
	if(userExists($user, $link))
	{
		if(auth($user, $pass, $link))
			printData($user, $link);
		else
			echo "Invalid password :/<br/>\n";
	}
	else
	{
		if(createUser($user, $pass, $link))
			echo "User $user created<br/>\n";
		else
			echo "Smthng bad happened :/<br/>\n";
	}
}
else
{
	echo $loginform;
}
?>
