#!/usr/bin/env python2.7


import sys
import mmh3
from hll import Hll
import time
import random
import math

def percentile(v,x):
        v.sort()
        pos = int((len(v)-1)*x)
        if(math.floor(pos) == pos):
            return v[pos];
        return (pos - math.floor(pos)) * v[pos] + ( math.ceil(pos) - pos) * v[pos+1]; 


f = open('linearError.txt', 'w')
f.write("# x \t avg \t error \n  ")

valuesLinear = []
z = 0

CARD = 100000
NB = 500
STEP = 500

# Un tableau de CARD/STEP cardinalites
for i in range(CARD/STEP):
    valuesLinear.append([])

x = 0

# On fait NB tests
for x in range(NB):
    print x
    hll = Hll(14)
    for j in range(CARD):
        hll.AddItem64(mmh3.hash64(str(z))[0])
	z+=1
        # Tous les STEP
        if j%STEP == 0:
            countLinear = hll.CountLinear()
            if j != 0 : 
                countLinear = math.fabs(countLinear-j)/j
            valuesLinear[j/STEP].append(countLinear)

for i in range(len(valuesLinear)):
    sumLinear = 0
    for j in range(len(valuesLinear[i])):
        sumLinear = sumLinear + valuesLinear[i][j]
    avgLinear = sumLinear / len(valuesLinear[i])
    error = 0
    mid = percentile(valuesLinear[i],0.50)
    one = percentile(valuesLinear[i],0.01)
    ninetynine = percentile(valuesLinear[i],0.99)


    f.write(str(i*STEP) + "\t" + str(avgLinear) + "\t" + str(mid) + "\t" + str(one) + "\t"+ str(ninetynine)+ "\n")
f.close()    
