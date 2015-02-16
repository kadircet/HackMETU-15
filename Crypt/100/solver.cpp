/*
	Decrypt this: gbscsvovlrkcwrobsdlr
*/
#include <iostream>
#include <string>
using namespace std;
string crypt(string INP,int seed)
{
	string RES;
	RES.push_back(((INP[0]-'a')+seed)%26+'a');
	for(int i=1;i<INP.size();i++)
	{
		RES.push_back(((INP[i-1]-'a')+(INP[i]-'a'))%26+'a');
	}
	return RES;
}
string decrypt(string INP,int seed)
{
	string RES;
	RES.push_back(((INP[0]-'a')-seed+26)%26+'a');
	for(int i=1;i<INP.size();i++)
	{
		RES.push_back(((INP[i]-'a')-(RES[i-1]-'a')+26)%26+'a');
	}
	return RES;
}
void DEC(string INP)
{
	for(int i=1;i<26;i++)
	{
		cout << decrypt(INP,i) << endl;	
	}
}
int main()
{
	string INP;
	cin >> INP;
	DEC(INP);
	//cout << crypt(INP,18)<<endl;	
	return 0;
}
