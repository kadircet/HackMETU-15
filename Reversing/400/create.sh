python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	file=$RANDOM
	gcc team$i/rev400.c -oteam$i/r400$file -s
	echo 'INSERT INTO `rev400` (`teamID`, `file`) VALUES ('$(($i+1))', '"'"'http://file.0xdeffbeef.com/r300'$file"'"');' >> rev400.sql
done
