python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	gcc team$i/crypt400.c -oteam$i/c400 -lcrypto -s
	useradd -M c400t$i -s/usr/sbin/nologin
	chown -R c400t$i.c400t$i team$i
	chmod 700 -R team$i
	cd team$i
	echo c400 $i
	sudo -u c400t$i ./c400 &
	cd ..
done
