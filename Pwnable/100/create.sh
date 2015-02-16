python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	gcc team$i/pwn100.c -oteam$i/p100 -s
	useradd -M p100t$i -s/usr/sbin/nologin
	chown -R p100t$i.p100t$i team$i
	chmod 700 -R team$i
	cd team$i
	echo p100 $i
	sudo -u p100t$i ./p100 &
	cd ..
done
