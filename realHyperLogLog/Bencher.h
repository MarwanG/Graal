//
//  Bencher.h
//  realHyperLogLog
//
//  Created by Steven on 07/02/2015.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#ifndef __realHyperLogLog__Bencher__
#define __realHyperLogLog__Bencher__

#include <stdio.h>


class Bencher
{
public:
	void go32(int num);
	void go64(int num);
};


#endif /* defined(__realHyperLogLog__Bencher__) */
