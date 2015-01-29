#include "Hll.h"
#include "MurmurHash3.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Hll::Hll(int p) : b(p){
	m = pow(2,p);
	
	buckets = new int[m];
	for(int i = 0; i < m; i++){
		buckets[i] = 0;
	}
}

double Hll::alpha(int m){
	if (m == 16){
		return 0.673;
	}
	else if (m == 32){
		return 0.697;
	}
	else if (m == 64){
		return 0.709;
	}
	return 0.7213/(1+ 1.079/m);
	
}

void Hll::AddItem(unsigned int n) {
	unsigned int j = n >> (32 - b);
	int r = 0;
	unsigned int w = 0;
	w = n & ((1<<(32-b))-1);
	r = __builtin_clz(w) - b + 1;
	//	cout << "j=" << j << ", w = " << w << " and r =" << r << endl;
	buckets[j] = max(buckets[j], r);
}


double Hll::Count(){
	double sum = 0.0;
	double e = 0.0;
	for( int i = 0; i < m; i++){
		sum += 1/pow(2,buckets[i]);
	}
	sum = 1.0/sum;
	e = alpha(m)*(m*m)*sum;
	if(e < 5.0/2*m){
		int v = 0;
		for(int i =0; i < m; i++){
			if(buckets[i] == 0)
				v++;
		}
		if(v >0){
			//cout << "V=" << v << endl;
			e = m*log((float)m/v);
		}
	}
	else if(e > 1.0/(30*pow(2,32))){
		e = -1*pow(2,32)*log(m/(pow(2,32)));
	}
	
	return e;
}


int main(int argc, char* argv[])
{
	//int size = atoi(argv[1]);
	
	string line;
	
	Hll hll(14);
	
	
	unsigned int hash;
	
	
	while ( getline (cin,line) )
	{
		MurmurHash3_x86_32(line.c_str(), line.length(), 0, &hash);
		hll.AddItem(hash);
		
	}
	
	
	printf("%f \n",hll.Count());
	
}
