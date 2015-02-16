#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
/*has to be on a vm whose aslr is disabled ssh enabled*/

int i;

int main(int argc, const char *argv[])
{
	char c[50];
	if(argc<2)
	{
		printf("USAGE: %s <SMTHNG>\n", argv[0]);
		exit(1);
	}
	strcpy(c, argv[1]);
	
	while(c[i])
		if(c[i++]==11)
		{
			puts("yok bu olmaz :((");
			exit(0);
		}
	
	setuid(0);	
	puts("bak iste bu olur ;) (tabii becerebildiysen :C)");
	return;
}

