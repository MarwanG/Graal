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
	
	void AddItem(uint64_t n);
	
	void AddItem32(unsigned int n);
	
	double Count();
	
	double Linear();
	
	double Count32();
	
	private :
	int* buckets;
	
	int b;
	
	int m;
	
};

#endif
