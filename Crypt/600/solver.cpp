/*
Bir mesaj aşağıdaki gibi şifrelenmiştir:
KT$DONAORUAKMINMEOYA#^MI!


Blok şifreleme yöntemi kullanıldığı bilindiğine göre orjinal mesajı elde ediniz.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
unsigned long long int FAC[30];
unsigned long long int fac(int n)
{
	if(FAC[n]!=0)return FAC[n];
	FAC[n]=n*fac(n-1);
	return FAC[n];
}
vector<int> next_permutation(vector<int> inp)
{
	int p=inp.size();
	for(int i=inp.size()-1;i>0;i--)
	{
		if(inp[i-1]<inp[i])
			{
				p=i-1;
				break;
			}
	}
	if(p==inp.size())
		return inp;
	int newplace=p+1;
	for(int i=p+2;i<inp.size();i++)
	{
		if(inp[i]>inp[p] && inp[i]<inp[newplace])
			newplace=i;
	}
	int h=inp[p];
	inp[p]=inp[newplace];
	inp[newplace]=h;
	sort(inp.begin()+p+1,inp.end());
	return inp;
}
string crypt_decrypt(string inp,vector<int> permutation)
{
	vector<int> A;
	string res;
	while(inp.size()%permutation.size()!=0)
		inp.push_back('X');
	for(int i=0;i<inp.size();i++)
	{
		res.push_back(inp[((i/permutation.size())*permutation.size()+permutation[i%permutation.size()])]);
	}
	return res;
}
void DEC(string inp,int UpperLimit)
{
	for(int i=1;i<=UpperLimit;i++)
	{
		vector<int> KEY;
		for(int j=0;j<i;j++)
		{
			KEY.push_back(j);
		}
		for(int j=0;j<fac(KEY.size());j++)
		{
			cout << crypt_decrypt(inp,KEY) << endl;
			KEY=next_permutation(KEY);
		}
	}
}
int main()
{
	FAC[0]=1;
	string INP;
	cin >> INP;
	vector<int> a;
/*	a.push_back(3);
	a.push_back(4);
	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	cout << crypt_decrypt(INP,a)<<endl;	
*/	
	DEC(INP,6);
	return 0;
}
