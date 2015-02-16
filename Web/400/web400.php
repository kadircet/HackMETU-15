<?php

$xml = <<<XML
<users>
	<user>
		<uname>helpmeicantfigureit</uname>
		<pass>outwellyouknow</pass>
		<flag>bupass</flag>
	</user>
</users>
XML;

//just tell the structure, there is a db called users, a table called user, each user has 3 cols uname, pass, flag

$loginform = <<<EOL
	Login:
	<form method="POST" action="#">
		<label>Username:</label><input type="text" name="user" /><br/>
		<label>Password:</label><input type="password" name="pass" /><br/>
		<input type="submit" name="login" value="login" />
	</form>
EOL;

$xml = new SimpleXMLElement($xml);

if(isset($_POST['login']))
{
	$user = $_POST['user'];
	$pass = $_POST['pass'];
	$result = $xml->xpath("/users/user[(uname='$user') and (pass='$pass')]");
	//' or substring(/users/user/uname/text(),1,1)='a
	
	if(count($result)==1)
	{
		if($result[0]->uname == $user && $result[0]->pass==$pass)
		{
			echo "Congratz... Here is your flag:<br/>\n";
			echo $result[0]->flag;
		}
		else
		{
			echo "I guess u r trying to hackmetu o_O...";
			echo $loginform;
		}
	}
	else
	{
		echo "Wrong credentials<br/>\n";
		echo $loginform;
	}
}
else
	echo $loginform;

?>
