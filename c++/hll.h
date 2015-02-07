#ifndef HLL_H
#define HLL_H

#include <iostream>
using namespace std;

class Hll
{
public:
	// Constructeurs
	Hll(int p);
	
	double alpha(int m);
	
	void AddItem64(uint64_t n);
	
	void AddItem32(unsigned int n);
	
	double Count64();
	
	double Linear32();
	
	double Linear64();
	
	double Count32();
	
	double CountRaw64();
	
	double CountLinear64();
	
	double CountCorrected64();
	
	private :
	int* buckets;
	
	int b;
	
	int m;
	
};

#endif
