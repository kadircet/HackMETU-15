$res=""; 
$res.="Asagidaki sifrelenmis mesaj elinize gecti.Mesajin asagidaki program tarafindan gonderilen bir mesaja donut olarak gonderildigini biliyorsunuz.Orjinal mesaji elde ediniz ve md5'lenmis halini sisteme gonderiniz.\n\n [program: http://192.168.2.5/crypt700]";

$target=""; $sql = "SELECT `target` FROM `crypt700` WHERE `teamID`=?"; $stmt = $db->prepare($sql); $stmt->bind_param("i", $team->id); $stmt->bind_result($target); $stmt->execute(); $stmt->store_result(); $stmt->fetch(); $stmt->close();

$res.=$target."\n\n";

return $res;


$res=""; 
$res.="You received the following cipher. You know that it is a response from the following program. Gather the plain text and send its md5 hash..\n\n [program: http://192.168.2.5/crypt700]";

$target=""; $sql = "SELECT `target` FROM `crypt700` WHERE `teamID`=?"; $stmt = $db->prepare($sql); $stmt->bind_param("i", $team->id); $stmt->bind_result($target); $stmt->execute(); $stmt->store_result(); $stmt->fetch(); $stmt->close();

$res.=$target."\n\n";

return $res;
