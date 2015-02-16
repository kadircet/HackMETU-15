#!/usr/bin/python
from os import popen
from os import mkdir
from sys import argv
from random import random as rand
N = int(argv[1])

key = "Bengelirmogidrarkamdantiktikeder".upper()
for t in range(N):
	mkdir('team%d'%t)
	sec=""
	L = 32
	for i in range(L):
		sec += chr(ord('a')+int(rand()*26))
	sec = popen("echo -n %s | md5sum"%sec).read().split(' ')[0]
	file('team%d/flag.txt'%t, 'w+').write(sec)
	popen("echo 'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 11, '\"'\"%s\"'\"');\' >> rev200.sql"%((t+1), sec))
	sec = list(sec)
	for i in range(len(key)):
		sec[i] = chr(ord(sec[i])^ord(key[i]))
	sec = "\\\\x".join(['{:02x}'.format(ord(c)) for c in sec])
	rep = "cat rev200.c | sed 's/\\\\x20\\\\x10\\\\x08\\\\x0b\\\\x04\\\\x0b\\\\x0b\\\\x13\\\\x1e\\\\x04\\\\x06\\\\x0f\\\\x08\\\\x04\\\\x15/\\\\x%s/'"%(sec)
	source= popen(rep).read()

	f = file('team%d/rev200.c'%t, 'w+')
	f.write(source)
	
