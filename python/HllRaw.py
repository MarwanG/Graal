#!/usr/bin/env python2.7


import sys
import mmh3
from hll import Hll
import time
import random
import math

def percentile(v,x):
        values[i].sort()
        pos = int((len(v)-1)*x)
        if(math.floor(pos) == pos):
            return v[pos];
        return (pos - math.floor(pos)) * v[pos] + ( math.ceil(pos) - pos) * v[pos+1]; 


f = open('HllRaw.txt', 'w')
f.write("# x \t avg \t 50% \t 1% \t 99% \n")

values = []



CARD = 100000
NB = 1000
STEP = 500

# Un tableau de CARD/STEP cardinalites
for i in range(CARD/STEP):
    values.append([])
x = 0

# On fait NB tests
for x in range(NB):
    print x
    hll = Hll(14)
    for j in range(CARD):
        hll.AddItem64(mmh3.hash64(str(random.randrange(0,CARD*10)))[0])
        # Tous les STEP
        if j%STEP == 0:
            count = hll.Count64()
            values[j/STEP].append(count)


for i in range(len(values)):
    sum = 0
    for j in range(len(values[i])):
        sum = sum + values[i][j]
    avg = sum / len(values[i])
    
    mid = percentile(values[i],0.50)
    one = percentile(values[i],0.01)
    ninetynine = percentile(values[i],0.99)
    
    f.write(str(i*STEP) + "\t" + str(avg) + "\t" + str(mid) + "\t" + str(one) + "\t"+ str(ninetynine)+ "\n")

f.close()    
