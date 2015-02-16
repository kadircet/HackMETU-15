#!/usr/bin/python
from os import popen
from os import mkdir
from sys import argv
from random import random as rand
pl = "echo -n '%secho %s' | md5sum"
N = int(argv[1])

for t in range(N):
	qu=""
	L = 8
	for i in range(L):
		qu += chr(ord('a')+int(rand()*26))

	sec=""
	L = 32
	for i in range(L):
		sec += chr(ord('a')+int(rand()*26))
	sec = popen("echo -n %s | md5sum"%sec).read().split(' ')[0]

	res = popen(pl%(sec,qu)).read()
	res = res.split(' ')[0]
	qu = "echo "+qu

	rep = "cat crypt400.c | sed 's/[a-z0-9]*echo naber/%s/' | sed 's/ge{}cen\[\]gun\!\@\#komikti/%s/' | sed 's/1337/%d/'"%(res+qu, sec, 1100+t)
	source= popen(rep).read()

	mkdir('team%d'%t)
	f = file('team%d/crypt400.c'%t, 'w+')
	f.write(source)
	
	popen("echo \'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 4, '\"'\"%s\"'\"');\' >> crypt400.sql"%((t+1), sec))
