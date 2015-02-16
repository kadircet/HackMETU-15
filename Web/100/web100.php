<?php

define("FLAG", 'bupass');//{-_-}This|OnE/\w4s:R34LLy_[]_e4sy_1snt-1t?
mysql_connect("localhost", "ctftest", "Cr4zyp4Ss{}1!_@");
mysql_select_db("hackmetu");

$loginform = <<<EOL
	Login:
	<form method="POST" action="#">
		<label>Username:</label><input type="text" name="user" /><br/>
		<label>Password:</label><input type="password" name="pass" /><br/>
		<input type="submit" name="action" value="login" />
	</form>
EOL;
$searchform = <<<EOL
	Search Users:
	<form method="POST" action="#">
		<label>Username:</label><input type="text" name="user" /><br/>
		<input type="submit" name="action" value="search" />
	</form>
EOL;
$logoutform = <<<EOL
	<form method="POST" action="#">
		<input type="submit" name="action" value="logout" />
	</form>
EOL;

$table = <<<EOL
	CREATE TABLE users
	(
		id int not null primary key auto_increment,
		user varchar(255),
		pass varchar(255)
	);
EOL;

if(mysql_num_rows(mysql_query("SHOW TABLES LIKE 'users'"))===0)
{
	mysql_query($table);
	$users = array();
		$users[0] = array('breakv0id', 'washere');
		$users[1] = array('0xdeffbeef', 'pwnsuall');
		$users[2] = array('omegaownsyouall^^', 'naber1234');
		$users[3] = array('hackmetu', 'rulAzzZ');
		$users[4] = array('sponsorbulsakdaparaalsak', 'neguzelolur');
	
	foreach($users as $key=>$value)
		$users[$key] = "('$value[0]', '$value[1]')";
	
	$users = implode(',', $users);
	$sql = "INSERT INTO users (user, pass) VALUES $users";
	mysql_query($sql) or die(mysql_error());
}

session_start();

$restricted = array('select', 'union', 'information_schema', 'users', 'user', 'pass', 'from');
foreach($_POST as $val)
{
	$val = strtolower($val);
	foreach($restricted as $word)
		if(strpos($val, $word)!==false)
		{
			$_SESSION['error'] = 'Are you trying to hack me tu??';
			header("Location: ".$_SERVER['PHP_SELF']);
			exit;
		}
}

?>
<html>
	<head>
		<title>LogiN2gEthaCKed</title>
	</head>
	<style>
		body {
			padding-top:100px;
		  text-align: center;
		 }
	</style>
	<body>
<?php

if(isset($_SESSION['error']))
{
	$err = $_SESSION['error'];
	unset($_SESSION['error']);
	
	echo "<font color='red'>ERRROR!!R!R!R!RRR!!!: <b>$err</b></font><br/><br/>\n";
}

if(isset($_SESSION['res']))
{
	$res = $_SESSION['res'];
	unset($_SESSION['res']);
	
	echo "Search results:<br/>\n<ul>\n";
	foreach($res as $row)
		echo "<li>".$row."</li><br/>\n";
	unset($res);
	
	echo "</ul><br/><br/>\n\n";
}

if(isset($_SESSION['id']))
{
	$id = $_SESSION['id'];
	$sql = "SELECT user FROM users WHERE id=$id";
	$res = mysql_query($sql);
	$row = mysql_fetch_array($res);
	
	echo "Hello, $row[0]<br/>\n";
	
	if($row[0] == "omegaownsyouall^^")
		echo "Flag is: ".FLAG;
	echo "\n<br/><br/>\n\n";
	echo $logoutform;
}
else if(isset($_POST['action']) && $_POST['action'] === "login")
{
	$user = $_POST['user'];
	$pass = $_POST['pass'];
	
	$sql = "SELECT id,user FROM users WHERE (user='$user') and (pass='$pass')";
	$res = mysql_query($sql);
	
	$nrow= mysql_num_rows($res);
	if($nrow!==1)
	{
		$_SESSION['error'] = "Invalid username/password combination";
		header("Location: ".$_SERVER['PHP_SELF']);
		exit;
	}
	
	$row = mysql_fetch_array($res);
	mysql_free_result($res);

	$_SESSION['id'] = $row[0];
	header("Location: ".$_SERVER['PHP_SELF']);
	exit;
}
else
{
	echo $loginform;
	echo "<br/><br/>\n\n";
}

if(isset($_POST['action']) && $_POST['action'] === "search")
{
	$user = $_POST['user'];
	
	$sql = "SELECT user FROM users WHERE user like '$user'";
	$res = mysql_query($sql) or die(mysql_error());
	
	$_SESSION['res'] = array();
	while($row = mysql_fetch_array($res))
		$_SESSION['res'][] = $row[0];
	
	header("Location: ".$_SERVER['PHP_SELF']);
	exit;
}
else if(isset($_POST['action']) && $_POST['action'] === "logout")
{
	if(isset($_SESSION['id']))
		unset($_SESSION['id']);
		
	header("Location: ".$_SERVER['PHP_SELF']);
	exit;
}
echo $searchform;
echo "<br/><br/>\n\n";
?>
	</body>
</html>
