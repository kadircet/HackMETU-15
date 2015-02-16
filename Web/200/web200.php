<?php

define("FLAG", 'bupass');
$loginform = <<<EOL
	Login:
	<form method="POST" action="#">
		<label>Username:</label><input type="text" name="user" /><br/>
		<label>Password:</label><input type="password" name="pass" /><br/>
		<input type="submit" name="action" value="login" />
	</form>
EOL;

function newID()
{
	$r=rand(1, 1337);
	while($r==486)
		$r=rand(1, 1337);
	return $r;
}

$admin = 0;
function lolsession_start()
{
	global $admin;
	if(array_key_exists("PHPSESSID", $_COOKIE) and is_numeric($_COOKIE['PHPSESSID']))
	{
		if(session_start())
		{
			if($_COOKIE['PHPSESSID']==486)
				$admin = 1;
			return true;
		}
		return -1;
	}
	return false;
}

function flag()
{
	global $admin;
	if($admin)
		echo "Welcome admin, flag is: ".FLAG."<br/>\n";
	else
		echo "You are just a crap :((<br/>\n";
}

$t=lolsession_start();
if($t==true)
{
	flag();
}
else
{
	if(array_key_exists('user', $_POST) and array_key_exists('pass', $_POST))
	{
		session_id(newID());
		session_start();
		flag();
	}
	else
	{
		if($t==-1)
			echo "kotu seyler oldu sanirim :((<br/>\n";
		echo $loginform;
	}
}

?>
