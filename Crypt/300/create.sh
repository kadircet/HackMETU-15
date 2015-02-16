python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	cd team$i
	echo c300 $i
	echo -n 'INSERT INTO `crypt300` (`target`, `teamID`) VALUES ('"'" >> ../crypt300.sql
	python crypt300.py >> ../crypt300.sql
	echo "'"", $(($i+1)));" >> ../crypt300.sql
	cd ..
done
