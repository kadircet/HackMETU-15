#!/usr/bin/python
from os import popen
from os import mkdir
from sys import argv
from random import random as rand
pl = "echo -n '%secho %s' | md5sum"
N = int(argv[1])

for t in range(N):
	sec=""
	L = 32
	for i in range(L):
		sec += chr(ord('a')+int(rand()*26))
	sec = popen("echo -n %s | md5sum"%sec).read().split(' ')[0]

	rep = "cat crypt300.py | sed 's/bupass/%s/'"%(sec)
	source= popen(rep).read()

	mkdir('team%d'%t)
	f = file('team%d/crypt300.py'%t, 'w+')
	f.write(source)
	
	popen("echo \'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 3, '\"'\"%s\"'\"');\' >> crypt300.sql"%((t+1), sec))
