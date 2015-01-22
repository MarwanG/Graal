#!/usr/bin/env python2.7


import sys
import mmh3
from hll import Hll
import time

class Benchmark:
	def __init__(self,p,n):
		self.p = p
                self.n = n

        def gogo(self):
                hll = Hll(self.p)
                debut = int(round (time.time() * 1000))
                for x in range (0, int(self.n)):
			hll.AddItem(x)
                print hll.Count()
                fin = int(round (time.time() * 1000))
                print "temps = "+str(fin-debut)+"ms";



	def go(self):
		hll = Hll(self.p)
		hashvalues = []
                for x in range (0,int(self.n)):
			hashvalues.append(mmh3.hash(str(x)))

                debut = int(round (time.time() * 1000))
                for i in range(0, int(self.n)):
		    	hll.AddItem(hashvalues[i])
                fin = int(round (time.time() * 1000))
		print hll.Count()
                print "temps = "+str(fin-debut)+"ms";
        
        def go64(self):
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
   	bencheur.gogo();

if __name__ == '__main__':
  main()  
