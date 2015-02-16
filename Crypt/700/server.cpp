#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <arpa/inet.h>
using namespace std;
string lock(string inp,int exp)
{
	vector<int> exps;
	for(int i=0;i<inp.size();i++)
	{
		exps.push_back(inp[i]-'a');
		int hold=exps[i];
		for(int j=0;j<(exp-1);j++)
			exps[i]=(exps[i]*hold)%26;
	}
	for(int i=0;i<inp.size();i++)
		inp[i]=(exps[i]+i)%26+'a';
	return inp;
}
bool check(string msg)
{
	for(int i=0;i<msg.size();i++)
	{
		if(msg[i]<'a' || msg[i]>'z')
		{
			return false;
		}
	}
	return true;
}
int main()
{
	char* port=(char*)"12345";

	int status;
	struct addrinfo host_info;
	struct addrinfo *host_info_list;   
	memset(&host_info, 0, sizeof(host_info));
	host_info.ai_family=AF_INET;
	host_info.ai_socktype=SOCK_STREAM;
	host_info.ai_flags=AI_PASSIVE;

	cout << "\033[32mGetting addrinfo...\033[0m" << endl;
	status=getaddrinfo(NULL,port,&host_info,&host_info_list);
	if(status!=0){cout << "\033[31merror: " << gai_strerror(status) <<"\033[0m"<< endl;exit(0);}
	
	cout << "\033[32mCreating socket...\033[0m" << endl;	
	int id=socket(host_info_list->ai_family,host_info_list->ai_socktype,host_info_list->ai_protocol);
	if(id==-1){cout << "\033[31msocket creation error\033[0m" << endl;exit(0);}

	cout << "\033[32mBinding socket...\033[0m" << endl;
	int a=1;
	status=setsockopt(id,SOL_SOCKET, SO_REUSEADDR,&a, sizeof(int));	
	status=bind(id,host_info_list->ai_addr,host_info_list->ai_addrlen);
	if(status==-1){cout << "\033[31mbind error\033[0m" << endl;exit(0);}

	cout << "\033[32mListening connections...\033[0m" << endl;
	status=listen(id,10);	
	if(status==-1){cout << "\033[31mlisten error\033[0m" << endl;exit(0);}

	freeaddrinfo(host_info_list);
	
	while(1)
	{
		struct sockaddr_in client;
		socklen_t S=sizeof(client);
		int remote=accept(id,(sockaddr*)&client,&S);
		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(client.sin_addr), ip, INET_ADDRSTRLEN);
		cout << "Connection from: "<< ip << endl;
		char *REC=(char*)malloc(sizeof(char)*1500);
		memset(REC,0,1500);
		ssize_t rect;
		rect=recv(remote,REC,1500,0);
		if(rect!=-1 && check(string(REC)))
		{		
			cout << REC << endl;
			string MSG=lock(string(REC),23);
			free(REC);			
			ssize_t sent;	
			sent=send(remote,MSG.c_str(),MSG.size(),0);
		}
		close(remote);
	}
	return 0;
}
