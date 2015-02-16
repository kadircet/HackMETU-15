#!/usr/bin/python
from os import popen
from os import mkdir
from sys import argv
from random import random as rand
from post import post
N = int(argv[1])

for t in range(N):
	sec=""
	pas=""
	L = 32
	for i in range(L):
		sec += chr(ord('a')+int(rand()*26))
		pas += chr(ord('a')+int(rand()*26))
	sec = popen("echo -n %s | md5sum"%sec).read().split(' ')[0]
	pas = popen("echo -n %s | md5sum"%pas).read().split(' ')[0]
	rep = "cat pwn100.c | sed 's/1337/%d/'"%(1200+t)
	source= popen(rep).read()
	
	post(t+1, 8, sec)
	print "posted",t+1,8,sec

	mkdir('team%d'%t)
	f = file('team%d/pwn100.c'%t, 'w+')
	f.write(source)
	f = file('team%d/flag.txt'%t, 'w+')
	f.write(sec)
	f = file('team%d/pass.txt'%t, 'w+')
	f.write(pas)
	
	popen("echo 'INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES (%d, 6, '\"'\"%s\"'\"');\' >> pwn100.sql"%((t+1), sec))
