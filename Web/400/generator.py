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
	rep = "cat web400.php | sed 's/bupass/%s/'"%(sec)
	source= popen(rep).read()

	mkdir('team%d'%t)
	x=""
	L = 32
	for i in range(L):
		x += chr(ord('a')+int(rand()*26))
	x = popen("echo -n %s | md5sum"%x).read().split(' ')[0]
	f = file(('team%d/web400'+x+'.php')%t, 'w+')
	f.write(source)
	
	popen("echo 'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 19, '\"'\"%s\"'\"');\' >> web400.sql"%((t+1), sec))
	popen("echo 'INSERT INTO `web400` (`teamID`, `file`) VALUES (%d, '\"'\"%s\"'\"');\' >> web400.sql"%((t+1), 'http://192.168.2.5/web400/team'+str(t)+'/web400'+x+'.php'))

