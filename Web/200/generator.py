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
	popen("echo 'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 17, '\"'\"%s\"'\"');\' >> web200.sql"%((t+1), sec))
	rep = "cat web200.php | sed 's/bupass/%s/'"%(sec)
	source= popen(rep).read()

	mkdir('team%d'%t)
	x=""
	L = 32
	for i in range(L):
		x += chr(ord('a')+int(rand()*26))
	x = popen("echo -n %s | md5sum"%x).read().split(' ')[0]
	f = file(('team%d/web200'+x+'.php')%t, 'w+')
	f.write(source)
	popen("echo 'INSERT INTO `web200` (`teamID`, `file`) VALUES (%d, '\"'\"%s\"'\"');\' >> web200.sql"%((t+1), 'http://192.168.2.5/web200/team'+str(t)+'/web200'+x+'.php'))
