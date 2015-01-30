#!/usr/bin/env python2.7



#might need to change it when using something different than int :)
#the objects are likely to be a couple of key and value therefore need to change as well :(
def qsort1(list):
    if list == []: 
        return []
    else:
        pivot = list[0][0]
        lesser = qsort1([x for x in list[1:] if x[0] < pivot[0]])
        greater = qsort1([x for x in list[1:] if x[0] >= pivot[0]])
        return lesser + [pivot] + greater

class mem:
    

    def __init__(self):
        self.tab = []
        self.tmp = []
        self.size = 32 #a definir


    #v is key,value object
    def addvalue(self,v):
        self.tmp.append(v)
        if self.tmp.size() == self.size:
            self.tmp = qsort1(self.tmp)
            z=0
            list = []
            for i in range(len(self.tmp)):
                x =  self.tmp[i]
                y =  self.tab[z]
                if x[0] < y[0]:
                    list.append(x)
                    i+=1
                else if x[0] == y[0]:
                    if x[1] < y[1]:
                        list.append(x)
                        i+=1
                    else:
                        list.append(y)
                        z+=1
                else
                    list.append(y)
                    z+=1



      
