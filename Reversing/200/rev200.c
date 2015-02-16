#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//buflagbaskaflag
//char str[] = {0x20, 0x10, 0x08, 0x0b, 0x04, 0x0b, 0x0b, 0x13, 0x1e, 0x04, 0x06, 0x0f, 0x08, 0x04, 0x15};
char str[] = "\x20\x10\x08\x0b\x04\x0b\x0b\x13\x1e\x04\x06\x0f\x08\x04\x15";
char *key = "BENGELIRMOGIDRARKAMDANTIKTIKEDER";


void fail(char *s)
{
	puts(s);
	exit(1);
}

int main()
{
	char a[20];
	int i;
	
	scanf("%s", a);
	if(strlen(a) != strlen(key))
		fail("Your password is your password, i want mine :)");
	for(i=0;i<strlen(key);i++)
		if(str[i]^key[i] != a[i])
			fail("Nah, it wont work :(");
			
	puts("Helal kenkz, flag bu :)");
	
	return 0;
}
