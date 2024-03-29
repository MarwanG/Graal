#!/usr/bin/env python2.7


import sys
import mmh3
from hll import Hll
import time

class Benchmark:
	def __init__(self,p,n):
		self.p = p
                self.n = n


        def go(self):
            	hll = Hll(self.p)
                hashvalues = []
                for x in range (0,int(self.n)):
			hashvalues.append(mmh3.hash64(str(x))[0])
                debut = int(round (time.time() * 1000))
                for i in range(0, int(self.n)):
			hll.AddItem64(hashvalues[i])
                fin = int(round (time.time() * 1000))
		print hll.Count64()
                print "temps = "+str(fin-debut)+"ms";


def main():
 
   	bencheur = Benchmark(14, sys.argv[1])
	bencheur.go();

if __name__ == '__main__':
  main()  
