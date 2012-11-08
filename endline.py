import sys

print sys.argv[1]
print sys.argv[2]

for i in range(1, len(sys.argv)):
	print sys.argv[i]
	f1 = open(sys.argv[i], 'r')
	str = f1.read()
	f1.close()
	f2 = open(sys.argv[i], 'w')
	f2.write(str + "\n")
	f2.close();


