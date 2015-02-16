#!/usr/bin/python
from os import popen
from os import mkdir
from sys import argv
from random import random as rand

N = int(argv[1])

for t in range(N):
	sec=""
	L = 32
	for i in range(L):
		sec += chr(ord('a')+int(rand()*26))
	sec = popen("echo -n %s | md5sum"%sec).read().split(' ')[0]
	popen("echo 'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 16, '\"'\"%s\"'\"');\' >> web100.sql"%((t+1), sec))
	rep = "cat web100.php | sed 's/bupass/%s/'"%(sec)
	source= popen(rep).read()

	mkdir('team%d'%t)
	L = 32
	x=""
	for i in range(L):
		x += chr(ord('a')+int(rand()*26))
	sec = popen("echo -n %s | md5sum"%x).read().split(' ')[0]
	f = file(('team%d/web100'+x+'.php')%t, 'w+')
	f.write(source)
	popen("echo 'INSERT INTO `web100` (`teamID`, `file`) VALUES (%d, '\"'\"%s\"'\"');\' >> web100.sql"%((t+1), '/web100'+x+'.php'))
