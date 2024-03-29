#include "Hll.h"
#include "MurmurHash3.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
#include <algorithm>

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

void Hll::AddItem32(unsigned int n) {
	unsigned int j = n >> (32 - b);
	int r = 0;
	unsigned int w = 0;
	w = n & ((1<<(32-b))-1);
	r = __builtin_clz(w) - b + 1;
	buckets[j] = max(buckets[j], r);
}


void Hll::AddItem64(uint64_t n) {
	uint64_t j = n >> (64 - b);
	int r = 0;
	uint64_t w = 0;
	w = n & ((1<<(64-b))-1);
	r = __builtin_clzll(w) - b + 1;
	buckets[j] = max(buckets[j], r);
}

double Hll::Linear32() {
	double e = 0;
	int v = 0;
	for(int i =0; i < m; i++){
		if(buckets[i] == 0){
			v++;
		}
	}
	if(v >0){
		e = m*log((float)m/v);
	}
	
	return e;
}

double Hll::Linear64() {
	double e = 0;
	uint64_t v = 0;
	for(int i =0; i < m; i++){
		if(buckets[i] == 0){
			v++;
		}
	}
	if(v >0){
		e = m*log((float)m/v);
	}
	
	return e;
}

double Hll::Count32(){
	double sum = 0.0;
	double e = 0.0;
	for( int i = 0; i < m; i++){
		sum += 1.0/(1<<buckets[i]);
		
	}
	sum = 1.0/sum;
	e = alpha(m)*(m*m)*sum;
	if(e < 5.0/2*m){
		e = Linear32();
	}
	else if(e > 1.0/(30*pow(2,32))){
		e = -1*pow(2,32)*log(m/(pow(2,32)));
	}
	
	return e;
}

double Hll::Count64(){
	double sum = 0.0;
	double e = 0.0;
	for( int i = 0; i < m; i++){
		sum += 1.0/(1<<buckets[i]);
	}
	sum = 1.0/sum;
	e = alpha(m)*(m*m)*sum;
	if(e < 5.0/2*m){
		e = Linear64();
	 }

	return e;
}

double Hll::CountRaw64(){
	double sum = 0.0;
	double e = 0.0;
	for( int i = 0; i < m; i++){
		sum += 1.0/(1<<buckets[i]);
	}
	sum = 1.0/sum;
	e = alpha(m)*(m*m)*sum;

	return e;
}

double Hll::CountLinear64(){
	return Linear64();
}

double percentile(vector <double> v , double x){
	//	sort(v.begin(), v.end());
	double pos = ((v.size()-1)*x);
	if(floor(pos) == pos){
		return v[pos];
	}
	return (pos - floor(pos)) * v[pos] + ( ceil(pos) - pos) * v[pos+1];
}

void uui(int argc, char* argv[])
{
	//int size = atoi(argv[1]);
	ofstream file ("test.txt");
	
	
	
	string line;
	
	Hll hll(14);
	
	
	uint64_t hash;
	uint64_t hash128[2];

	int i;
	int card = 100000;
	int tests = 1000;
	int step = 100;
	vector< vector<double> > tab(card/step, vector<double>(tests));
	
	int ca = 0;
	for(i = 0; i < tests; i ++){
		cout << i << endl;
		Hll hll(14);
		for(int j = 0; j < card; j++){
			MurmurHash3_x86_128(&ca, 4, 0, &hash128);
			ca++;
			hash = hash128[0];
			hll.AddItem64(hash);
			if(j%step == 0){
				double count = hll.Count64();
				count = (double)abs(count-j)/j;
				tab[j/step][i]=count;
			}
		}
	}
	
	for(int j = 0; j < card/step; j++){
		double sum = 0;
		for (int k = 0; k < tests; k++){
			sum= sum + tab[j][k];
		}
		//cout << sum << endl;
		double median = percentile(tab[j],0.5);
		double pct01 = percentile(tab[j],0.01);
		double pct99 = percentile(tab[j],0.99);
		file << (j*step) << "\t" << (double)sum/tests << "\t" << (double)median << "\t" << pct01 << "\t" << pct99 << endl;
	}
	
	
	
	printf("%f \n",hll.Count64());
	
}
