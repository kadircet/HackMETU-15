CREATE TABLE `pwn500` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `file` varchar(255) DEFAULT NULL,
  `ip` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `pwn500` (`file`, `ip`) VALUES ('http://file.0xdeffbeef.com/pwn500', 'IP PLS');
