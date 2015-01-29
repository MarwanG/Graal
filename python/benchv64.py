#!/usr/bin/env python2.7


import sys
import mmh3
from hll import Hll
import time
import random
import math

def percentile(v,x):
        pos = int((len(v)-1)*x)
        if(math.floor(pos) == pos):
            return v[pos];
        return (pos - math.floor(pos)) * v[pos] + ( math.ceil(pos) - pos) * v[pos+1]; 


hll = Hll(14)


f = open('res.txt', 'w')
f.write("# x avg 50% 5% 55%% \n")



values = []
for i in range(1000):
    values.append([])


x = 0
    

for j in range(1000):
    print j
    for i in range(int(sys.argv[1])):
        hll.AddItem64(mmh3.hash64(str(random.randrange(0,1000000)))[0])
        if i%100 == 0:
            count = hll.Count64()
            values[x].append(count)
            x = x + 1
    x = 0

for i in range(1000):
    values[i].sort()
    sum = 0
    for j in range(100):
        sum = sum + values[i][j]
    avg = sum / 100
    mid = percentile(values[i],0.50)
    five = percentile(values[i],0.02)
    nightfive = percentile(values[i],0.98)
    f.write(str(i*100) + "\t" + str(avg) + "\t" + str(mid) + "\t" + str(five) + "\t"+ str(nightfive)+ "\n")

f.close()    
