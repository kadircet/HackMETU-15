texts= [
"I think hackmetu is the best ctf contest ever.",
"One time padding is overpowered, no one can beat it.",
"But if you can manage to convert it into a many time padding.",
"It is the time to rule the world! Hack the planet!",
"Age of the geek bitch, age of the geek!",
"NSA is trying to listen to hackmetu traffic??",
"What if I told you we are in the matrix?",
"Do you think you are the one ??",
"Follow the white hobbit, or the rabbit ?",
"It is too damn secure to be broken ^^"
]

def strxor(a, b):
	if len(a) > len(b):
		return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a[:len(b)], b)])
	else:
		return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b[:len(a)])])

target = "bupass"
key = open("/dev/urandom").read(1024)

res=""
for t in texts:
	res+= strxor(t, key).encode('hex')+"\\n"
res+= "And your target is:\\n"
res+= strxor(target, key).encode('hex')+"\\n"

print res
