#!/usr/bin/env python2.7


import sys
import mmh3
from hll import Hll

class Client:
	def __init__(self,p):
		self.p = p


	def readHash(self):
		hll = Hll(self.p)
		x = sys.stdin.readline().rstrip('\n')
		while x:
			hll.AddItem64(mmh3.hash64(str(x))[0])
			x = sys.stdin.readline().rstrip('\n')
		print hll.Count64()



def main():
   	client = Client(16)
   	client.readHash()

if __name__ == '__main__':
  main()  
