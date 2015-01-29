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

#Y = ( ( X - X1 )( Y2 - Y1) / ( X2 - X1) ) + Y1
def interpolation (x,x1,y1,x2,y2):
    return (((x-x1)*(y2-y1))/(x2-x1))+y1


data={}
valuesdata = []

f =  open(sys.argv[1],'r')
f.readline()

for line in f:
    split = line.split()
    data[float(split[1])] = float(split[0])
    valuesdata.append(float(split[1]))

f.close()


f = open('resHLLBRUT.txt', 'w')
f.write("# x \t avg \t 50% \t 1% \t 99% \n")

CARD = 100000
NB = 10
STEP = 500

values = []

# Un tableau de CARD/STEP cardinalites
for i in range(CARD/STEP):
    values.append([])
x = 0


for x in range(NB):
    hll = Hll(14)
    for j in range(CARD):
        hll.AddItem64(mmh3.hash64(str(random.randrange(0,CARD*10)))[0])
        # Tous les STEP
        if j%STEP == 0:
            count = hll.Count64()
            x1 =  min(valuesdata, key=lambda x:abs(x-count))
            y1 = data[x1]
            if valuesdata.index(x1)+1 != len(valuesdata):
               x2 = valuesdata[valuesdata.index(x1)+1]
               y2 = data[x2]
               inter = interpolation(count,x1,y1,x2,y2)
               values[j/STEP].append(inter)
            else:
               values[j/STEP].append(x2)
         


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
