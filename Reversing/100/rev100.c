#include <stdio.h>
#include <string.h>

int main()
{
	char inp[128], *pass = "vallacrackledinprogramibizbusifreyiparaylasatiyozinanirmisin";
	int i=0;
	
	printf("Enter serial: ");
	while(i<128)
	{
		if(scanf("%c", &inp[i])==EOF)
			break;
		if(inp[i]=='\n' || inp[i]=='\r' || inp[i]==0)
			break;
		i++;
	}
	inp[i] = 0;
	
	if(!strcmp(inp, pass))
		printf("Flag is: %s\n", pass);
	else
		puts("Nck... Invalid serial :(");
	return 0;
}

