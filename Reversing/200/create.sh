python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	file=$RANDOM
	gcc team$i/rev200.c -oteam$i/r200$file -s
	echo 'INSERT INTO `rev200` (`teamID`, `file`) VALUES ('$(($i+1))', '"'"'http://file.0xdeffbeef.com/r200'$file"'"');' >> rev200.sql
done
