pas="""62f95d53
76f3b286
16a699df
8b8e7885
60021734
aacde443
1cb27dcb
2364e981
70af3bc0
79dfcaba
1a7b15d8
53f4271d
97ca5a89
e03c9fc9
8e8632c4
93e13d8d
069b68eb
f7284504
541d68f7
09f43611
4ae9820c
a29a3ba4
8771c81b
ec4ab610
53011af0
25fa2178
19e7cc78
b836c928
0a1a0d59
7777531b
015547c9
3f6f5257
e9d8a8d5
067ca863
1d097c04
2c547e76
ea5db596
8e482edb
a3c90651
8dff8ea3
148ec0a7
c40c00c5
b572da6f
86a278e9
d2d6cb99
942dca5f
7f2e31c6
ebcbea41
7833dc5c
65ed09b0
"""

pas = pas.split('\n')
f=open('pwn300.sql', 'a+')
for i in range(50):
	f.write("INSERT INTO `pwn300` (`file`, `ip`, `teamID`, `pass`) VALUES ('http://192.168.2.5/pwn300', '192.168.2.4', "+str(i+1)+", '"+pas[i]+"');\n")

