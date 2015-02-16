python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	file=$RANDOM
	gcc team$i/rev100.c -oteam$i/r100$file -s
	echo 'INSERT INTO `rev100` (`teamID`, `file`) VALUES ('$(($i+1))', '"'"'http://file.0xdeffbeef.com/r100'$file"'"');' >> rev100.sql
done
