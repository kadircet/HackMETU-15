#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
bool check(string msg)
{
	for(int i=0;i<msg.size();i++)
	{
		if(msg[i]<'a' || msg[i]>'z')
		{
			cout << "\033[31monly lowercase chars!\033[0m" << endl;		 
			return false;
		}
	}
	return true;
}
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
int main(int argc,char* argv[])
{
	if(argc<2 || strcmp(argv[1],"noreboot")!=0)
	{
		system("sudo reboot");
	}
	else
	{
		char* port=(char*)"12345";		
		char* server=(char*)"192.168.2.5";

		int status;
		struct addrinfo host_info;
		struct addrinfo *host_info_list;   
		memset(&host_info, 0, sizeof(host_info));
		host_info.ai_family=AF_INET;
		host_info.ai_socktype=SOCK_STREAM;

		cout << "\033[32mGetting addrinfo...\033[0m" << endl;
		status=getaddrinfo(server,port,&host_info,&host_info_list);
		if(status!=0){cout << "\033[31merror: " << gai_strerror(status) <<"\033[0m"<< endl;exit(0);}
	
		cout << "\033[32mCreating socket...\033[0m" << endl;	
		int id=socket(host_info_list->ai_family,host_info_list->ai_socktype,host_info_list->ai_protocol);
		if(id==-1){cout << "\033[31msocket creation error\033[0m" << endl;exit(0);}

		cout << "\033[32mConnecting to server...\033[0m" << endl;	
		status=connect(id,host_info_list->ai_addr,host_info_list->ai_addrlen);
		if(status==-1){cout << "\033[31mconnect error\033[0m" << endl;exit(0);}
	
		string MSG;
		cin >> MSG;
		if(check(MSG))
		{
			ssize_t sent;
			cout << "\033[32mSending data...\033[0m"<<endl;	
			sent=send(id,lock(MSG,17).c_str(),MSG.size(),0);
	
			char* rec;
			rec=(char*)malloc(sizeof(char)*1500);
			memset(rec,0,1500);		
			ssize_t rect;
			cout << "\033[32mReceiving data...\033[0m"<<endl;
			rect=recv(id,rec,1500,0);
			if(rect==-1){cout << "\033[31mreceive error\033[0m" << endl;exit(0);}
			if(rect==0){cout << "\033[31mhost is down\033[0m" << endl;exit(0);}
			cout <<rec << endl;
			free(rec);
		}

		freeaddrinfo(host_info_list);
		close(id);
	}
	return 0;
}
