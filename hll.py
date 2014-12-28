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
        n = (n & (2**(32) -1)) + 2**32
#        print "N="+bin(n)
        j = n >> (32 - self.b)
#        print "J="+bin(j)
        j = j - 2**self.b
        w = n & 2**(32 - self.b) -1
 
        w = w + 2**(32 - self.b)
#        print "W:                "+bin(w) 
        r = self.rho(w)
        self.buckets[j] = max(  self.buckets[j], r );
        
#        print "J= "+bin(j)
#        print "W:                "+bin(w) + "   >> rho =" + str(r) + ")"
#        print ""

    def Count(self):
        sum = 0;
        for i in range(len(self.buckets)):
            sum += math.pow(2.0, -self.buckets[i])
 #           print self.buckets[i]
        sum = 1.0/sum;
        e =  self.alpha(self.m)*float(self.m**2)*sum;
        v = 0;
        for i in range(self.m):
            if (self.buckets[i] == 0):
                v+=1;
            if(v != 0):
                e = self.m * math.log(self.m/float(v))
        return e;

    def rho(self,val):
#        print "VAL="+bin(val)
        val = val & 2**(32 - self.b)-1
#        print "VA2="+bin(val)
        rho = (33 - self.b) - val.bit_length()
#        print rho
        return rho 



#print v.bit_length()

def main():
    test = Hll(16);
    v = mmh3.hash("coucou")
    test.AddItem(mmh3.hash("abc"));
    test.AddItem(mmh3.hash("ab"));
    test.AddItem(mmh3.hash("abc")); 
 #   print test.count();

if __name__ == '__main__':
  main()  
