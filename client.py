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
			hll.AddItem(mmh3.hash(x))
			x = sys.stdin.readline().rstrip('\n')
<<<<<<< HEAD
		print hll.Count()
=======
		print hll.count()
>>>>>>> FETCH_HEAD


def main():
   	client = Client(16)
   	client.readHash()

if __name__ == '__main__':
  main()  