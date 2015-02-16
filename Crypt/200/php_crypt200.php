$res=""; 
$res.="Asagidaki sifrelenmis mesaj elinize gecti.Mesajin bir tur monoalfabetik sifreleme yontemi kullanilarak sifrelendigini bildiginize gore orjinal mesaji elde edip md5lenmis halini sisteme gonderiniz.\n\n";

$target=""; $sql = "SELECT `target` FROM `crypt200` WHERE `teamID`=?"; $stmt = $db->prepare($sql); $stmt->bind_param("i", $team->id); $stmt->bind_result($target); $stmt->execute(); $stmt->store_result(); $stmt->fetch(); $stmt->close();

$res.=$target."\n\n";

return $res;
