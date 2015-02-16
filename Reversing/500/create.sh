python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	file=$RANDOM
	gcc team$i/rev500.c -oteam$i/r500$file -s
	echo 'INSERT INTO `rev500` (`teamID`, `file`) VALUES ('$(($i+1))', '"'"'http://file.0xdeffbeef.com/r500'$file"'"');' >> rev500.sql
done
