from hashlib import md5
from subprocess import Popen, PIPE
a=open("answers","r")
read=a.readlines()
a.close()
b=open("crypt400.sql","w")
b.write("CREATE TABLE 'crypt400' ( 'id' int(11) NOT NULL AUTO_INCREMENT,  'teamID' int(11) NOT NULL,  'target' varchar(255) DEFAULT NULL,  PRIMARY KEY ('id'),  KEY 'teamID' ('teamID')) ENGINE=MyISAM DEFAULT CHARSET=utf8;\n");
c=1
for i in read:
	#i=i[:-1]
	i=i.strip()
	st=md5()
	st.update(i)
	print i
	b.write("INSERT INTO `flags` (`teamID`, `taskID`, `flag`) VALUES ("+str(c)+", 1, '"+st.hexdigest()+"');\n");
	p = Popen(['./c','noreboot', "-"], stdin=PIPE, stdout=PIPE, stderr=PIPE)
	stdout, stderr = p.communicate(i)
	b.write("INSERT INTO `crypt400` (`teamID`, `target`) VALUES ("+str(c)+", '"+stdout[0:-1]+"');\n");
	c=c+1
b.close()
