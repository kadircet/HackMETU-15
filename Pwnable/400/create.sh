python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	gcc team$i/pwn400.c -oteam$i/p400 -m32 -Wno-format-security -s
	useradd -M p400t$i -s/usr/sbin/nologin
	chown -R p400t$i.p400t$i team$i
	chmod 700 -R team$i
	cd team$i
	echo p400 $i
	sudo -u p400t$i ./p400 &
	cd ..
done
