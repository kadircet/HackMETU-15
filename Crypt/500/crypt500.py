def isPrime(n):
	i=0
	if n<2:
		return False
	if n==2:
		return True
	i=3
	while i*i<=n:
		if n%i==0:
			return False
		i+=2
	return True
	
def gcd(a,b):
	if b==0:
		return a
	return gcd(b,a%b)

p=5003
q=5009
n=p*q
tn=(p-1)*(q-1)
d=21686587
e=499

def decrypt(C):
	res=[]
	for i in C:
		c = pow(i,d,n)
		res=[c]+res
	msg=""
	for c in res:
		while c>0:
			msg = chr(c%128)+msg
			c/=128
	return msg

#n=25060027
#e=499
def encrypt(M):
	res=[]
	for i in range(0,len(M),3):
		msg = M[i:i+3]
		c=0
		for m in msg:
			c*=128
			c+=ord(m)
		c = pow(c,e,n)
		res.append(c)
	return res
		
M = "bupass"
r=encrypt(M)
print r
