#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

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

void md5(char* data, int len, char* hash)
{
	MD5_CTX c;
	int i, size;
	/*its the flag in case u didnt notice noobz .s.s*/
	char *secret = "ge{}cen[]gun!@#komikti", msg[512];
	
	MD5_Init(&c);
	MD5_Update(&c, secret, strlen(secret));
	MD5_Update(&c, data, len);
	MD5_Final(hash, &c);
}

void handle_client(int client)
{
	unsigned char buffer[256], hash[MD5_DIGEST_LENGTH], ourhash[MD5_DIGEST_LENGTH];
	int i, admin=0, buflen;
	for(i=0;i<3;i++)
		close(i), dup(client);
	
	puts("Welcome stranger(if u r the admin sorry)");
	puts("Send your messages by adding the hash of the message(salted with the secret)");
	puts("Dont forget to include \\n if you send it too!");
	puts("Here is an example:(be careful it does not include a \\n)");
	puts("And btw, your commands can include NULL bytes :)) isnt it perfect :)))");
	puts("a47330e2eb7758f7210dcfe4db1dc91decho naber");
	fflush(stdout);
	
	i = recv(client, buffer, sizeof(hash)*2, 0);
	if(i<=0)
		goto finish;
		
	if(i==sizeof(hash)*2)
		for(i=0;i<sizeof(hash);i++)
		{
			if(conv(buffer[2*i])<0 || conv(buffer[2*i+1])<0)
			{
				puts("What sort of an hash is this??");
				goto finish;
			}
			hash[i] = conv(buffer[2*i])*0x10 + conv(buffer[2*i+1]);
		}
	else
	{
		puts("Msg too short r u sure u added md5 hash as prefix??");
		goto finish;
	}
	buflen = i = recv(client, buffer, sizeof(buffer), 0);
	if(i>=sizeof(buffer))
	{
		puts("Msg too long r u trying to hack me???");
		goto finish;
	}
		
	buffer[i] = 0;
	
	md5(buffer, i, ourhash);
	for(i=0;i<sizeof(hash);i++)
		if(ourhash[i]!=hash[i])
		{
			puts("I dont think u r admin, get out of here!!!");
			goto finish;
		}
	
	for(i=0;i<buflen;i++)
		if(buffer[i]==0)
			buffer[i] = '\n';
	
	puts("I bless you admin here is the result of your command:");
	system(buffer);
	
finish:
	fflush(stdout);
	shutdown(client, 2);
	while(recv(client, buffer, sizeof(buffer), 0)>0);
	close(client);
	exit(0);
}

int running=1;
void sigterm(int x)
{
	__sync_fetch_and_sub(&running, 1);
}

int main(int argc, const char *argv[])
{
	int sck, client, addrlen;
	struct sockaddr_in this_addr, peer_addr;
	pid_t child_pid;
	unsigned short port = 1337;
	
	addrlen = sizeof( struct sockaddr_in );
	memset( &this_addr, 0, addrlen );
	memset( &peer_addr, 0, addrlen );
	
	this_addr.sin_port        = htons(port);
	this_addr.sin_family      = AF_INET;
	this_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	sck = socket( AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(sck==-1)
		puts("sck");
	if(bind(sck, (struct sockaddr *)&this_addr, addrlen)!=0)
		puts("bind");
	if(listen(sck, 5)!=0)
		puts("listen");
	
	signal(SIGINT, sigterm);
	while(running)
	{
		while(running && -1 == (client = accept(sck, (struct sockaddr *)&peer_addr, &addrlen)));
		if(running)
		{
			printf("Connection from: %d.%d.%d.%d\n",
				(int)(peer_addr.sin_addr.s_addr&0xFF),
				(int)((peer_addr.sin_addr.s_addr&0xFF00)>>8),
				(int)((peer_addr.sin_addr.s_addr&0xFF0000)>>16),
				(int)((peer_addr.sin_addr.s_addr&0xFF000000)>>24));
		
			if(!fork())
				handle_client(client);
		}
	}
	close(sck);
	return 0;
}

