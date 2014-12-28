#!/usr/bin/env python2.7


import sys
import mmh3
import math

class Hll:
    
    def __init__(self, p):
       self.b = 16;
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

    def AddItem(self,h):
#        print bin(h)
        h = h % (2**32)
  #      print bin(h)
        j = h & (self.m - 1)
        w = h >> self.b
#        print bin(h)
#        print bin(j)
 #       print bin(w)
 #      str(self.rho(w))
        self.buckets[j] = max(  self.buckets[j], self.rho(w)  );
 
        #print "=";
       # print str(self.buckets[j]);

    def Count(self):
        sum = 0;
        for i in range(len(self.buckets)):
<<<<<<< HEAD
            sum += math.pow(2.0, -self.buckets[i])
#            print self.buckets[i]; #JSS NOOB MAIS J'AIME PAS
=======
            sum += 1/(2**(self.buckets[i]));
            # print self.buckets[i]; JSS NOOB MAIS J'AIME PAS
>>>>>>> FETCH_HEAD
        sum = 1.0/sum;
 #       print "somme="+str(sum)
        e =  self.alpha(self.m)*float(self.m**2)*sum;
 #       print "e="+str(e)
        
        v = 0;
        for i in range(self.m):
           if (self.buckets[i] == 0):
                   v+=1;
           if(v != 0):
               e = self.m * math.log(self.m/float(v))

 #       print v
        return e;

    def rho(self,val):
<<<<<<< HEAD
       rho = (32 - self.b) - val.bit_length() + 1
       return rho

=======
        return 64 - val.bit_length() + 1;



#print v.bit_length()

def main():
    test = Hll(16);
    v = mmh3.hash("coucou")
    test.AddItem(mmh3.hash("abc"));
    test.AddItem(mmh3.hash("ab"));
    test.AddItem(mmh3.hash("abc")); 
    print test.count();

if __name__ == '__main__':
  main()  
>>>>>>> FETCH_HEAD
