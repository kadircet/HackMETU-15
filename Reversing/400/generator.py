#!/usr/bin/python
from os import popen
from os import mkdir
from sys import argv
from random import random as rand
N = int(argv[1])

key = file('rev400.txt').read()

for t in range(N):
	mkdir('team%d'%t)
	sec=""
	L = 32
	for i in range(L):
		sec += chr(ord('a')+int(rand()*26))
	sec=sec.upper()
	file('team%d/flag.txt'%t, 'w+').write(sec)
	popen("echo 'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 14, '\"'\"%s\"'\"');\' >> rev400.sql"%((t+1), sec))
	sec = list(sec)
	for i in range(len(sec)):
		sec[i] = chr(ord(sec[i])^ord(key[i])^0x02)
	sec = "\\\\x".join(['{:02x}'.format(ord(c)) for c in sec])
	rep = "cat rev400.c | sed 's/bupass/\\\\x%s/'"%(sec)
	source= popen(rep).read()

	f = file('team%d/rev400.c'%t, 'w+')
	f.write(source)
	
