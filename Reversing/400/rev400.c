#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flagdedinmiislerkarisirhaa
char *pass = "bupass";
char * qrqr="\xde\xff\xbe\xef";
void fail(char *s)
{
	puts(s);
	exit(1);
}

char* decrypt(char *a)
{
	char *res=malloc(strlen(a)+2);
	int i=0;
	while(a[i])
	{
		res[i]= a[i]^qrqr[i%4];
		i++;
	}
	return res;
}

int main()
{
	int socket_handle ;
	struct sockaddr_in socket_detials ;
	char * input_buffer;
	char * httpget = decrypt("\x99\xba\xea\xcf\xf1\x8d\xdb\x99\xea\xcf\x8e\xc1\xaa\x87\xca\xcf\x96\xab\xea\xbf\xf1\xce\x90\xde\xd3\xf5\xf6\xa0\x8d\xab\x84\xcf\xbd\x8b\xd8\xc1\xee\x87\xda\x8a\xb8\x99\xdc\x8a\xbb\x99\x90\x8c\xb1\x92\xb3\xe5\xd3\xf5") ;
	puts(httpget);

	input_buffer = malloc(20000);

	socket_handle = socket ( AF_INET, SOCK_STREAM, 0) ;
	socket_detials.sin_family = AF_INET ;
	socket_detials.sin_addr.s_addr=inet_addr("192.241.179.36");
	socket_detials.sin_port = htons(80);

	connect (socket_handle,(struct sockaddr*)&socket_detials, sizeof ( struct sockaddr));
	send ( socket_handle , httpget, strlen(httpget), 0 ) ;
	recv ( socket_handle , input_buffer , 20000, 0 ) ;
	//printf ( "%s\n", input_buffer ) ;
	
	//boylekeymiolurmusarkadas!!
	//`m{ngig{okmnwpowqcpicfcq##
	char key[100];
	int i;

	for(i=strlen(input_buffer)-strlen(pass)-1;i<strlen(input_buffer)-1;i++)
		key[i-strlen(input_buffer)+strlen(pass)+1] = input_buffer[i];

	char inp[100];
	scanf("%s", inp);
	if(strlen(inp)!=strlen(pass))
		fail("yemedi :(");
		
	for(i=0;i<strlen(inp);i++)
		if((inp[i]^key[i]) != (pass[i]^0x02))
			fail("Bu da olmazz");
	
	puts("bak bu oldu iste ;)");
	return 0 ;
}

