/*
Sadece ingilizce karakterler kullanılarak yazılan bir mesaj aşağıdaki gibi şifrelenmiştir:
NSCZSRQBOKUBOCSGOK

Şifreleme algoritmasını yazan kişi monoalfabetik şifreleme teknikleri kullanıldığını bir konferansta açıkladığına göre orjinal mesajı elde ediniz.*/
#include <iostream>
#include <string>
using namespace std;
string crypt(string inp,int a,int b,int m)
{
	string res;
	for(int i=0;i<inp.size();i++)
	{
		if(inp[i]>='a' && inp[i]<='z')
			res.push_back((a*(inp[i]-'a')+b)%m+'a');
		else
			res.push_back((a*(inp[i]-'A')+b)%m+'A');
	}
	return res;
}
string decrypt(string inp,int a,int b,int m)
{
	string res;
	int inverse;
	for(inverse=0;inverse<m;inverse++)
	{
		if((inverse*a)%m==1)break;
	}
	if(inverse==m) return res;
	for(int i=0;i<inp.size();i++)
	{
		if(inp[i]>='a' && inp[i]<='z')
			res.push_back(((inp[i]-'a'-b+m)*inverse)%m+'a');
		else
			res.push_back(((inp[i]-'A'-b+m)*inverse)%m+'A');
	}
	return res;
}
int main()
{
	string I;
	cin >> I;
	//cout << crypt(I,17,14,26) << endl;
	for(int i=1;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			cout << decrypt(I,i,j,26) << endl;
		}
	}
}
