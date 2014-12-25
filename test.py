import sys
import mmh3


def readHash():
	hash = []
	x = sys.stdin.readline().rstrip('\n')
	while x:
		hash.append(mmh3.hash(x))
		x = sys.stdin.readline().rstrip('\n')
	
	for i in range(3):
		print hash[i]

readHash()