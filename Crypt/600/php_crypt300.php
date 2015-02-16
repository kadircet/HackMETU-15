$res=""; 
$res.="Asagidaki sifrelenmis mesaj elinize gecti.Mesajin bir tur blok sifreleme yontemi kullanilarak sifrelendigini bildiginize gore orjinal mesaji elde edip md5lenmis halini sisteme gonderiniz.\n\n";

$target=""; $sql = "SELECT `target` FROM `crypt600` WHERE `teamID`=?";
$stmt = $db->prepare($sql);
$stmt->bind_param("i", $team->id);
$stmt->bind_result($target);
$stmt->execute();
$stmt->store_result();
$stmt->fetch();
$stmt->close();

$res.=$target."\n\n";

return $res;

$res=""; 
$res.="You found the following cipher. You know that the cipher is encrypted using a block encryption method, according to that knowledge find the plain text and send the md5 hash of it.\n\n";

$target=""; $sql = "SELECT `target` FROM `crypt600` WHERE `teamID`=?";
$stmt = $db->prepare($sql);
$stmt->bind_param("i", $team->id);
$stmt->bind_result($target);
$stmt->execute();
$stmt->store_result();
$stmt->fetch();
$stmt->close();

$res.=$target."\n\n";

return $res;
