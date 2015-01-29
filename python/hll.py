#!/usr/bin/env python2.7


import sys
import mmh3
import math

class Hll:
    
    def __init__(self, p):
       self.b = p;
       self.buckets = [];
       self.m = 2**self.b;
       for i in range (self.m):
           self.buckets.append(0);


    def alpha(self, m):
        if m == 16:
            return 0.673;
        elif m == 32 :
            return 0.697
        elif m == 64:
            return 0.709
        return 0.7213/(1+ 1.079/m)

    def AddItem(self, n):
        # on met un 1 au 32eme bit pour que les entiers soient tous de la meme longueur
        #numero du bucket
        j = n >> (32 - self.b)
	# reste
        w = n & 2**(32 - self.b) -1
        w = w + 2**(32 - self.b)
        r = self.rho(w)
        self.buckets[j] = max(  self.buckets[j], r );

    def AddItem64(self,n):
        # on met un 1 au 32eme bit pour que les entiers soient tous de la meme longueur
        #numero du bucket 
	j = n >> (64 - self.b)
        # reste
        w = n & 2**(64 - self.b) -1
        w = w + 2**(64 - self.b)
        r = self.rho(w)
        self.buckets[j] = max(  self.buckets[j], r );


    def Count(self):
        sum = 0;
        #calcul de la moyenne harmonique
        for i in range(len(self.buckets)):
		sum += math.pow(2.0, -self.buckets[i])
        sum = 1.0/sum;
        e =  self.alpha(self.m)*float(self.m**2)*sum;

        if(e < 5.0/2*self.m): # linear counting
		v = 0; 
            	for i in range(self.m):
                	if (self.buckets[i] == 0):
                    		v+=1;
            	if(v != 0):
                	e = self.m * math.log(self.m/float(v))
        
        if(e > 1.0/30*2**32): # correction
            	e = -2**32*math.log(self.m/2**32)
        
        return e;

    def Count64(self):
        sum = 0;
        #calcul de la moyenne harmonique
        for i in range(len(self.buckets)):
            	sum += math.pow(2.0, -self.buckets[i])
        sum = 1.0/sum;
        e =  self.alpha(self.m)*float(self.m**2)*sum;

     #   if(e < 5.0/2*self.m): # linear counting
      #      	v = 0;
       #     	for i in range(self.m):
        #        	if (self.buckets[i] == 0):
         #           		v+=1;
          #  	if(v != 0):
           #     	e = self.m * math.log(self.m/float(v))
			
        if(e > 1.0/30*2**64): # correction
            	e = -2**64*math.log(self.m/2**64)
        return e;


    def rho(self,val): # calcul de la position du premier bit a 0 de val
        val = val & 2**(32 - self.b)-1
        rho = (33 - self.b) - val.bit_length()
        return rho 

    def rho64(self,val): # calcul de la position du premier bit a 0 de val
        val = val & 2**(64 - self.b)-1
        rho = (65 - self.b) - val.bit_length()
        return rho 





def main():
    test = Hll(14);

if __name__ == '__main__':
  main()  
