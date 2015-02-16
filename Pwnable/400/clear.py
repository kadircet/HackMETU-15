#!/usr/bin/python
from os import popen
from os import mkdir
from sys import argv
N = int(argv[1])

popen('killall p400')
popen('rm -rf team*')
for t in range(N):
	popen('userdel p400t%d'%t)
