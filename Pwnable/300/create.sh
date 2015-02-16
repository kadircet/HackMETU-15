python generator.py $1
chmod -R 700 .

for i in `seq 0 $(($1-1))`
do
	pass=`echo $RANDOM | md5sum`
	pass=${pass:0:8}
	echo $pass >> passwd.txt
	mkdir -p /home/p3001t$i
	gcc team$i/pwn300.c -o/home/p3001t$i/p300 -m32 -fno-stack-protector -zexecstack -s
	useradd -M p300t$i -s/usr/sbin/nologin
	useradd p3001t$i -s/bin/bash
	(echo $pass; echo $pass) | passwd p3001t$i
	mv team$i/* /home/p3001t$i/
	rm -rf team$i
	chown -R p300t$i.p300t$i /home/p3001t$i
	chmod 700 -R /home/p3001t$i
	chown p300t$i.p3001t$i /home/p3001t$i/p300
	chmod 555 /home/p3001t$i/p300
	chmod +s /home/p3001t$i/p300
	echo p300 $i
done
