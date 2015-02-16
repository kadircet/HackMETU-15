#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#define MAXCHUNK 0x40

int DEBUG = 0;

void do_crazy_things()
{
	if(!DEBUG)
		return;
		
	FILE *f = fopen("flag.txt", "r");
	char flag[128];
	fscanf(f, "%s", flag);
	
	puts(flag);
}

struct chunk
{
	int size;
	struct chunk *fwd;
	struct chunk *bck;
};

struct chunk* chead;

void init()
{
	int i;
	chead = (struct chunk*)malloc(MAXCHUNK*0x400+MAXCHUNK*sizeof(struct chunk));
	chead->size = 0x400+sizeof(struct chunk);
	
	struct chunk* cur = chead;
	for(i=0;i<MAXCHUNK;i++)
	{
		cur->fwd = (struct chunk*)(((void*)cur)+chead->size-(i==(MAXCHUNK-1)?MAXCHUNK*chead->size:0));
		cur->bck = (struct chunk*)(((void*)cur)+(MAXCHUNK-1)*chead->size-(i>0?MAXCHUNK*chead->size:0));
		cur->size = chead->size;
		cur = cur->fwd;
	}
	
	cur=chead;
	do
	{
		cur->size |= 0x01;
		cur = cur->fwd;
	}while(cur!=chead);
}

void* cmalloc(int size)
{
	size = (size+1+sizeof(struct chunk))&0xFFFFFFFE;
	
	struct chunk* cur = chead, *new = NULL;
	do
	{
		if(cur->size&0x01 && size<cur->size)
		{
			new = cur;
			break;
		}
		cur = cur->fwd;
	}while(cur!=chead);
	
	if(new==NULL)
	{
		return (void*)-1;
		new = (struct chunk*)malloc(size);
		new->size = size;
		new->fwd = chead;
		new->bck = chead->bck;
		chead->bck->fwd = new;
		chead->bck = new;
	}
	else
	{
		cur = (struct chunk*)(((void*)new)+size);
		cur->size = (new->size - size -1) | 0x01;
		cur->fwd = new;
		cur->bck = new->bck;
		if(chead==new)
			chead = cur;
		new->bck->fwd = cur;
		new->bck = cur;
		new->size = size & ~0x01;
	}
	
	return ((void*)new)+sizeof(struct chunk);
}

void cfree(void *p)
{
	struct chunk* node = (struct chunk*)(p-sizeof(struct chunk));
	
	node->bck->fwd = node->fwd;
	node->fwd->bck = node->bck;
	node->bck->size += node->size;
	
	if(DEBUG)
		do_crazy_things();
	
	//free(node);
}

int do1()
{
	int i=0;
	init();
	char *a = (char*)cmalloc(sizeof(char)*256);
	char *b = (char*)cmalloc(sizeof(char)*256);
	
	scanf("%s", a);
	
	/*struct chunk *cur = chead;
	do
	{
		printf("%d: addr:%p size:%x fwd:%p bck:%p\n", i++, (void*)cur+sizeof(struct chunk), cur->size, cur->fwd, cur->bck);
		cur = cur->fwd;
	}while(cur!=chead);*/
	
	cfree(b);
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

//(perl -e 'print "A"x256';echo -ne "AAAA\x30\xa0\x04\x08") | ./p
//nm ./p | grep DEBUG
