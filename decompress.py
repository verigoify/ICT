from cosineTransform import inverseDiscreteCosineTransform
import sys

f = open(sys.argv[1])
file = f.read()
f.close()
file = file.split(' ')
file = [float(i) for i in file]
idct = inverseDiscreteCosineTransform(file)
file2 = ''.join([chr(int(round(i))) for i in idct])
f = open(sys.argv[1] + 'dec.txt', 'w')
f.write(file2)
f.close()