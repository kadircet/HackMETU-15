python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	chmod 700 -R team$i
done
