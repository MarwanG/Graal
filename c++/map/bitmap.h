//
//  bitmap.h
//  hyperLogLog
//
//  Created by Steven Varoumas on 06/02/15.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#ifndef __hyperLogLog__bitmap__
#define __hyperLogLog__bitmap__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

using namespace std;

class Bitmap {
    uint32_t* list;
    int size;
    int realsize;
public:
    Bitmap();
    void write(uint32_t val);
    void display();
    uint32_t read(int i);
    int getKey(int i);
    int getValue(int i);
    int getSize() const;
    int getRealSize() const;
    
private:
    unsigned int get(char b);
    uint32_t val(int a, int b);
};

#endif /* defined(__hyperLogLog__bitmap__) */
