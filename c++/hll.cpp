#include "Hll.h"
#include "MurmurHash3.h"
#include <cmath>
#include <iostream>
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
	int j = n >> (32 - b);
	int r = 0;
	int w = 0;
	w = (int) n & (int)(pow(2,(32-b))-1);
	r = __builtin_clz(w)+1;
//	cout << "j=" << j << ", w = " << w << " and r =" << r << endl;
	buckets[j] = max (buckets[j], r);
}


double Hll::Count(){
	double sum = 0.0; 
	double e = 0.0;
	for( int i = 0; i < m; i++){
		sum += pow(2,-1*buckets[i]);
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
			cout << "V=" << v << endl;
			e = m*log((float)m/v);
		}
	}
	/*else if(e > 1.0/(30*pow(2,32))){
		e = -1*pow(2,32)*log(m/(pow(2,32)));
	}
	*/
	return e;
}


int main(int argc, char* argv[])
{
	int size = atoi(argv[1]);
	int* hash = new int[size];
	int i;
	Hll hll(14);
	for(i = 0; i < size; i++){
		MurmurHash3_x86_32(&i, 32, 0, &hash[i]);
	}
	for(i = 0; i < size; i++){
		hll.AddItem(hash[i]);
	}
	cout << "y en a " << hll.Count() << endl;
}
