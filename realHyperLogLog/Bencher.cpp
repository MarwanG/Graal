//
//  Bencher.cpp
//  realHyperLogLog
//
//  Created by Steven on 07/02/2015.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#include "Bencher.h"
#include "MurmurHash3.h"
#include "hll.h"
#include <vector>
#include <chrono>

void Bencher::go32(int num){
	uint32_t hash;
	vector <int> hashed = vector<int>();
	
	cout << "hashing ..." << endl;
	for(int i = 0; i < num ; i++){
		MurmurHash3_x86_32(&i, 4, 0, &hash);
		hashed.push_back(hash);
	}
	Hll hll(14);
	cout << "go" << endl;
	auto begin = chrono::high_resolution_clock::now();
	for(int i = 0; i < num ; i++){
			hll.AddItem32(hashed[i]);
	}
	double n = hll.Count32();
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto temps = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	
	cout << n <<  endl << "temps : " << temps << "ms" << endl;

}

void Bencher::go64(int num){
	uint64_t hash;
	uint64_t hash128[2];
	vector < uint64_t > hashed = vector<uint64_t>();
	
	cout << "hashing ..." << endl;
	for(uint64_t i = 0; i < num ; i++){
		MurmurHash3_x86_128(&i, 8, 0, &hash128);
		hash = hash128[0];
		hashed.push_back(hash);
	}
	Hll hll(14);
	cout << "go" << endl;
	auto begin = chrono::high_resolution_clock::now();
	for(uint64_t i = 0; i < num ; i++){
		hll.AddItem64(hashed[i]);
	}
	double n = hll.Count64();
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto temps = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	
	cout << n <<  endl << "temps : " << temps << "ms" << endl;
	
}
