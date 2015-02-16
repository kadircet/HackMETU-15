#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
/*
./sol 32 "echo naber" "a47330e2eb7758f7210dcfe4db1dc91d" "ls -la;cat crypt300.c" | nc localhost 1337
*/
unsigned char conv(unsigned char x)
{
	int i;
	char *vals = "0123456789abcdef";
	x = tolower(x);
	
	for(i=0;i<strlen(vals);i++)
		if(x==vals[i])
			return i;
	
	return -1;
}

int main(int argc, char *argv[])
{
	MD5_CTX c;
	unsigned char buffer[MD5_DIGEST_LENGTH], *hash, *orgdata;
	int i, seclen, orglen, datalen;
	long size;
	char *orgmsg, *append;
	
	if(argc!=5)
	{
		printf("Usage: %s secretlen orgdata orghash appenddata\n", argv[0]);
		exit(1);
	}
	seclen = atoi(argv[1]);
	orglen = strlen(argv[2]);
	orgdata = argv[2];
	hash = argv[3];
	append = argv[4];

	for(i=0;i<16;i++)
		hash[i] = conv(hash[2*i])*0x10 + conv(hash[2*i+1]);
		
	datalen = (orglen+seclen)/64*64+64;
		
	MD5_Init(&c);
	for(i=0;i<datalen;i++)
		MD5_Update(&c, "A", 1);
	c.A = *(int*)(hash+0x00);
	c.B = *(int*)(hash+0x04);
	c.C = *(int*)(hash+0x08);
	c.D = *(int*)(hash+0x0c);
	
    MD5_Update(&c, append, strlen(append));
	MD5_Final(buffer, &c);

	for (i = 0; i < 16; i++)
		printf("%02x", buffer[i]);
	printf("%s\x80", orgdata);
	fflush(stdout);
	for(i=orglen+seclen+1;i<datalen-8;i++)
		write(1, "\x00", 1);
	
	size = orglen+seclen;
	size <<= 3;
	write(1, (char*)&size, 8);
	printf("%s", append);
	return 0;
}

