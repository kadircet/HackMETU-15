python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	gcc team$i/pwn200.c -oteam$i/p200 -m32 -fno-stack-protector -s
	useradd -M p200t$i -s/usr/sbin/nologin
	chown -R p200t$i.p200t$i team$i
	chmod 700 -R team$i
	cd team$i
	echo p200 $i
	sudo -u p200t$i ./p200 &
	cd ..
done
