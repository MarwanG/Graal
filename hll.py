#!/usr/bin/env python2.7


import sys
import mmh3
import math

class Hll:
    
    def __init__(self, p):
       self.b = p;
       self.buckets = [];
       self.alpha = 0.7;
       self.m = 2**self.b;
       for i in range (self.m):
           self.buckets.append(0);

    def AddItem(self,h):
  #      print 32;
        j = h >> (32 -self.b);
        w = h & (32 -self.b);
        self.buckets[j] = max(  self.buckets[j], self.rho(w)  );

    def count(self):
        sum = 0;
        for i in range(len(self.buckets)):
            sum += 1/(2**(self.buckets[i]));
            # print self.buckets[i]; JSS NOOB MAIS J'AIME PAS
        sum = 1.0/sum;
        e = self.alpha*(len(self.buckets)**2)*sum;

        if(e < (5/2)*self.m):
           v = 0;
           for i in range(self.m):
               if (self.buckets[i] == 0):
                   v+=1;
           if(v != 0):
               e = self.m * math.log(self.m/float(v))

        if (e > 1/30 * 2**32):
            e = -2**32 * math.log(1- e/2**32);
        return e;

    def rho(self,val):
        return 32 - val.bit_length() + 1;



#print v.bit_length()

#def main():
#    test = Hll(16);
#    v = mmh3.hash("coucou")
##    test.AddItem(mmh3.hash("abc"));
#   test.AddItem(mmh3.hash("ab"));
#    test.AddItem(mmh3.hash("abc"));
#    print test.count();

#if __name__ == '__main__':
#  main()
