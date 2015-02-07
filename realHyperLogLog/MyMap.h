//
//  MyMap.h
//  realHyperLogLog
//
//  Created by Steven Varoumas on 06/02/15.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#ifndef __realHyperLogLog__MyMap__
#define __realHyperLogLog__MyMap__

#include <stdio.h>
#include <vector>
#include "bitmap.h"

using namespace std;

class MyMap {
    Bitmap bigList;
    vector < uint32_t > smallList;
public:
    MyMap();
    // "key" prend 14 bits; "value" au plus 6 bits.
    void UpdateMax(int key, int value);
    
    // Crée une copie "dense"; de taille 2^14; où l'élément #i est la
    // "value" max ayant été donnée avec la "key" i à UpdateMax(..).
    vector<char> GetDense();
    
    int BytesUsed() const;  // Renvoie la taille mémoire, en octets.
    void add(uint64_t v);
private:
    Bitmap merge();

    int getKey(int i);
    void displaySmall();
    int getValue(int i);
};

#endif /* defined(__realHyperLogLog__MyMap__) */
