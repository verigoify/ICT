from cosineTransform import discreteCosineTransform
import sys

f = open(sys.argv[1])
file = f.read()
f.close()
file = [ord(i) for i in file]
print(file)
dct = discreteCosineTransform(file)
print(dct)
file2 = ' '.join([str(i) for i in dct])
print(file2)
f = open(sys.argv[1] + 'com.txt', 'w')
f.write(file2)
f.close()

