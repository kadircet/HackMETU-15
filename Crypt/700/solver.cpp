#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;
vector<string> results;
string ex(char a,int len)
{
	string s;
	for(int i=0;i<len;i++)
		s.push_back(a);
	return s;
}
void updateResults(char a,int index)
{
	vector<char> possibleChars;
	for(int i=0;i<26;i++)
	{
		string CHECKLAST=ex('a'+i,index+1);
		cout << CHECKLAST<<endl;
		ofstream f;
		f.open("asdqwe123");
		f<<CHECKLAST;
		f.close();
		system("./client noreboot < asdqwe123 > qweasd321");
		ifstream q;
		q.open("qweasd321");
		string RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q>>RES;
		q.close();
		if(RES[RES.size()-1]==a)
		{
			possibleChars.push_back('a'+i);
		}
	}
	if(possibleChars.size()>0)
	{
		vector<string> NEW;
		for(int i=0;i<results.size();i++)
		{
			vector<string> hold=results;
			for(int j=0;j<possibleChars.size();j++)
			{
				hold[i].push_back(possibleChars[j]);
				NEW.push_back(hold[i]);
			}
		}
		results=NEW;
	}
}
int main()
{
	results.push_back(string());
	string INP;
	cin >> INP;
	for(int i=0;i<INP.size();i++)
	{
		updateResults(INP[i],i);
	}
	for(int i=0;i<results.size();i++)
		cout << results[i] << endl;
	system("rm asdqwe123 qweasd321");
	return 0;
}
