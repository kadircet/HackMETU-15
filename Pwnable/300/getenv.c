#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		printf("Usage: %s <variable_name> <realexec_name>", argv[0]);
		exit(0);
	}
	
	int diff = strlen(argv[2]) - strlen(argv[0]);
	diff <<= 1;
	char *addr = getenv(argv[1]);
	printf("%p %s\n", addr-diff, addr);
	return 0;
}

