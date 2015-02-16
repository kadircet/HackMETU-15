<?php

define("FLAG", 'bupass');//{-_-}This|OnE/\w4s:R34LLy_[]_e4sy_1snt-1t?
$loginform = <<<EOL
	Login:
	<form method="POST" action="#">
		<label>Username:</label><input type="text" name="user" /><br/>
		<label>Password:</label><input type="password" name="pass" /><br/>
		<input type="submit" name="action" value="login" />
	</form>
EOL;

class user
{
	public $name;
	private $pass;
	
	public function __construct($name, $pass)
	{
		$this->name=$name;
		$this->pass=$pass;
	}
}

if(isset($_POST['user']) && isset($_POST['pass']))
{
	$a = new user($_POST['user'], $_POST['pass']);
	if($_POST['user']=="admin")
		die("senin pass olmamis diyorlar?");
	$b= serialize($a);
	$lol="";
	for ($i=0;$i<strlen($b);$i++)
		$lol.=chr(ord($b[$i])^0x0b);
	setcookie("user", $lol, time() + (86400 * 30), "/");
}
else if(isset($_COOKIE['user']))
{
	$lol=$_COOKIE['user'];
	$tol="";
	for ($i=0;$i<strlen($lol);$i++)
		$tol.=chr(ord($lol[$i])^0x0b);
	$a = unserialize($tol);
	if($a->name=="admin")
		echo FLAG;
	else
		echo "You are just ".$a->name;
}
else
{
	echo $loginform;
}
?>
