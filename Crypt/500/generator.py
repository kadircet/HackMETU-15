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

	rep = "cat crypt500.py | sed 's/bupass/%s/'"%(sec)
	source= popen(rep).read()

	f = file('test.py', 'w+')
	f.write(source)
	f.close()
	
	msg = popen("python test.py").read()
	
	popen("echo 'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 5, '\"'\"%s\"'\"');\' >> crypt500.sql"%((t+1), sec))
	popen("echo 'INSERT INTO `crypt500` (`msg`,`teamID`) VALUES ('\"'\"'%s'\"'\"', %d);' >> crypt500.sql"%(msg, t+1))
