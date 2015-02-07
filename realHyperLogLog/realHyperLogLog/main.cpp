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
#include "MurmurHash3.h"
#include "hll.h"
#include "Bencher.h"
#include "Ploter.h"


void clientForTester(){
	
	string line;
	
	Hll hll(14);
	uint64_t hash;
	uint64_t hash128[2];
	
	while ( getline (cin,line) ){
		MurmurHash3_x86_128(line.c_str(), line.length(), 0, &hash128);
		hash = hash128[0];
		hll.AddItem64(hash);
	}
	
	cout << hll.Count64();
}

void clientForBencher(int n){
	Bencher bench;
	
	bench.go64(n);
	
}

void clientforPloter(string filename){
	Ploter plot;
	
	plot.plotRawHll(filename+"_raw.txt");
	plot.plotLinear(filename+"_linear.txt");
	
	plot.plotRawBias(filename+"_raw_bias.txt");
	plot.plotLinearBias(filename+"_linear_bias.txt");
	
	plot.plotCorrectedHll(filename+"_corrected.txt");
	plot.plotCorrectedHllBias(filename+"_corrected_bias.txt");
}

int main(int argc, const char * argv[]) {
	
	//clientForTester();
	
	//clientForBencher(100000000);
	
	clientforPloter("hll");

//    MyMap map = MyMap();
//    
//    for(int i = 0; i < 5; i++)
//        map.add(99887799998989948);
//	
//	vector < char > tab = map.GetDense();
//	
//	
    return 0;
}
