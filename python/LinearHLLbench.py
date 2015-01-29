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
            print pos
            return v[pos];
        return (pos - math.floor(pos)) * v[pos] + ( math.ceil(pos) - pos) * v[pos+1]; 


f = open('linearRes.txt', 'w')
f.write("# x \t avg \t error \n  ")

valuesLinear = []


CARD = 100000
NB = 10
STEP = 100

# Un tableau de CARD/STEP cardinalites
for i in range(CARD/STEP):
    valuesLinear.append([])

x = 0

# On fait NB tests
for x in range(NB):
    print x
    hll = Hll(14)
    for j in range(CARD):
        hll.AddItem64(mmh3.hash64(str(random.randrange(0,CARD*10)))[0])
        # Tous les STEP
        if j%STEP == 0:
            countLinear = hll.CountLinear()
            valuesLinear[j/STEP].append(countLinear)

for i in range(len(valuesLinear)):
    sumLinear = 0
    for j in range(len(valuesLinear[i])):
        sumLinear = sumLinear + valuesLinear[i][j]
    avgLinear = sumLinear / len(valuesLinear[i])
    error = 0
    if i!=0 :
        error = math.fabs(i*STEP-avgLinear)/(i*STEP)
    f.write(str(i*STEP) + "\t" + str(avgLinear) + "\t" + str(error) + "\n");
   
f.close()    
