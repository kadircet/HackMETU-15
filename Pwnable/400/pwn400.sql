CREATE TABLE `pwn400` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `file` varchar(255) DEFAULT NULL,
  `ip` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `pwn400` (`file`, `ip`) VALUES ('http://file.0xdeffbeef.com/pwn400', 'IP PLS');
