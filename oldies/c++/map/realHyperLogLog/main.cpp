//
//  main.cpp
//  realHyperLogLog
//
//  Created by Steven Varoumas on 06/02/15.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#include <iostream>
#include "bitmap.h"
#include "MyMap.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    // Bitmap bit = Bitmap();
    
  //  bit.display();
    
  //  bit.write(10284398);
    
   // bit.display();
    
    MyMap map = MyMap();
    
    for(int i = 0; i < 5; i++)
        map.add(9988779999992948);
    
    return 0;
}
