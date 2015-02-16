#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int key;
char pass[] = "bupass";
//"flag_olsaydim_aynen_boyle_olurdum";

void dec()
{
	unsigned int i,j;
	for(j=0;j<0xffffffff;j++)
	{
		key = 0;
		for(i=0;i<0xdeffbeef;i++)
			key++;
	}
}

void fail(char *s)
{
	puts(s);
	exit(1);
}

int main()
{
	char *keyc = (char*)&key;
	char inp[40];
	int i;
	
	scanf("%s", inp);
	dec();
	
	if(strlen(pass)!=strlen(inp))
		fail("asdf qomik olma yhaa .s.s");
		
	for(i=0;i<strlen(inp);i++)
		if((inp[i]^keyc[i%4]^0x05) != (pass[i]^0x05))
			fail("Qomik olmaya calisiyosun ama olmuyor :(");
	
	puts("HEH SImDI OLDUN ISTE :))");
	return 0;
}
