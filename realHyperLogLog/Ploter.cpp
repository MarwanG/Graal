//
//  Ploter.cpp
//  realHyperLogLog
//
//  Created by Steven on 07/02/2015.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#include "Ploter.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include "hll.h"
#include <stdio.h>
#include "MurmurHash3.h"

#define TESTS	1000
#define CARDMAX	100000
#define STEP	100

vector<double> Ploter::makeVector(){
	vector<double> tab = vector<double>(CARDMAX/STEP);
	string line;
	ifstream myfile ("hll_raw.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			int i;
			double card;
			sscanf(line.c_str(), "%d %lf %*s", &i, &card);
			
			tab[i/STEP] = card;
			cout << card;
		}
		myfile.close();
	}
	return tab;
}
double Ploter::interpolation(double x, double x1, double y1, double x2, double y2){
	//cout << x << " - > " << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
	double v = (((x-x1)*(y2-y1))/(x2-x1))+y1;
	//cout << "v=" << v << endl;
	return v;
}

double Ploter::percentile(vector <double> v , double x){
	//	sort(v.begin(), v.end());
	double pos = ((v.size()-1)*x);
	if(floor(pos) == pos){
		return v[pos];
	}
	return (pos - floor(pos)) * v[pos] + ( ceil(pos) - pos) * v[pos+1];
}

void Ploter::plotRawHll(string filename){
	ofstream file(filename);
	string line;
	
	uint64_t hash;
	uint64_t hash128[2];
	
	int i;

	vector< vector<double> > tab(CARDMAX/STEP, vector<double>(TESTS));
	
	int ca = 0;
	for(i = 0; i < TESTS; i ++){
		cout << i << endl;
		Hll hll(14);
		for(int j = 0; j < CARDMAX; j++){
			MurmurHash3_x86_128(&ca, 4, 0, &hash128);
			ca++;
			hash = hash128[0];
			hll.AddItem64(hash);
			if(j%STEP == 0){
				double count = hll.CountRaw64();
				//count = (double)abs(count-j)/j;
				tab[j/STEP][i]=count;
			}
		}
	}
	
	for(int j = 0; j < CARDMAX/STEP; j++){
		double sum = 0;
		for (int k = 0; k < TESTS; k++){
			sum= sum + tab[j][k];
		}
		//cout << sum << endl;
		double median = percentile(tab[j],0.5);
		double pct01 = percentile(tab[j],0.01);
		double pct99 = percentile(tab[j],0.99);
		file << (j*STEP) << "\t" << (double)sum/TESTS << "\t" << (double)median << "\t" << pct01 << "\t" << pct99 << endl;
	}

}

void Ploter::plotCorrectedHll(string filename){
	ofstream file(filename);
	string line;
	int x1, x2;
	double y1, y2;
	x1 = 0;
	y1 = 0;
	x2 = CARDMAX/STEP-1;
	y2 = 0;
	uint64_t hash;
	uint64_t hash128[2];
	
	vector<double> estimates = makeVector();
	
	int i;
	vector< vector<double> > tab(CARDMAX/STEP, vector<double>(TESTS));
	
	int ca = 0;
	for(i = 0; i < TESTS; i ++){
		cout << i << endl;
		Hll hll(14);
		
		for(int j = 0; j < CARDMAX; j++){
			MurmurHash3_x86_128(&ca, 4, 0, &hash128);
			ca++;
			hash = hash128[0];
			hll.AddItem64(hash);
			if(j%STEP == 0){
				double count = hll.CountRaw64();
				for(int i = 0; i < CARDMAX/STEP-1; i++){
					if(estimates[i] <= count && count < estimates[i+1]){
						x1 = estimates[i];
						y1 = i*STEP;
						x2 = estimates[i+1];
						y2 = (i+1)*STEP;
						count = interpolation(count, x1, y1, x2, y2);
					}
				}
				//count = interpolation(count, x1, y1, x2, y2);
				//count = (double)abs(count-j)/j;
				tab[j/STEP][i]=count;
			}
		}
	}
	
	for(int j = 0; j < CARDMAX/STEP; j++){
		double sum = 0;
		for (int k = 0; k < TESTS; k++){
			sum= sum + tab[j][k];
		}
		//cout << sum << endl;
		double median = percentile(tab[j],0.5);
		double pct01 = percentile(tab[j],0.01);
		double pct99 = percentile(tab[j],0.99);
		file << (j*STEP) << "\t" << (double)sum/TESTS << "\t" << (double)median << "\t" << pct01 << "\t" << pct99 << endl;
	}
	
}

void Ploter::plotCorrectedHllBias(string filename){
	ofstream file(filename);
	string line;
	int x1, x2;
	double y1, y2;
	x1 = 0;
	y1 = 0;
	x2 = CARDMAX/STEP-1;
	y2 = 0;
	uint64_t hash;
	uint64_t hash128[2];
	
	vector<double> estimates = makeVector();
	
	int i;
	vector< vector<double> > tab(CARDMAX/STEP, vector<double>(TESTS));
	
	int ca = 0;
	for(i = 0; i < TESTS; i ++){
		cout << i << endl;
		Hll hll(14);
		
		for(int j = 0; j < CARDMAX; j++){
			MurmurHash3_x86_128(&ca, 4, 0, &hash128);
			ca++;
			hash = hash128[0];
			hll.AddItem64(hash);
			if(j%STEP == 0){
				double count = hll.CountRaw64();
				for(int i = 0; i < CARDMAX/STEP-1; i++){
					if(estimates[i] <= count && count < estimates[i+1]){
						x1 = estimates[i];
						y1 = i*STEP;
						x2 = estimates[i+1];
						y2 = (i+1)*STEP;
						count = interpolation(count, x1, y1, x2, y2);
					}
				}
				//count = interpolation(count, x1, y1, x2, y2);
				count = (double)abs(count-j)/j;
				tab[j/STEP][i]=count;
			}
		}
	}
	
	for(int j = 0; j < CARDMAX/STEP; j++){
		double sum = 0;
		for (int k = 0; k < TESTS; k++){
			sum= sum + tab[j][k];
		}
		//cout << sum << endl;
		double median = percentile(tab[j],0.5);
		double pct01 = percentile(tab[j],0.01);
		double pct99 = percentile(tab[j],0.99);
		file << (j*STEP) << "\t" << (double)sum/TESTS << "\t" << (double)median << "\t" << pct01 << "\t" << pct99 << endl;
	}
	
}



void Ploter::plotLinear(string filename){
	ofstream file(filename);
	string line;
	
	uint64_t hash;
	uint64_t hash128[2];
	
	int i;
	vector< vector<double> > tab(CARDMAX/STEP, vector<double>(TESTS));
	
	int ca = 0;
	for(i = 0; i < TESTS; i ++){
		cout << i << endl;
		Hll hll(14);
		for(int j = 0; j < CARDMAX; j++){
			MurmurHash3_x86_128(&ca, 4, 0, &hash128);
			ca++;
			hash = hash128[0];
			hll.AddItem64(hash);
			if(j%STEP == 0){
				double count = hll.CountLinear64();
				tab[j/STEP][i]=count;
			}
		}
	}
	
	for(int j = 0; j < CARDMAX/STEP; j++){
		double sum = 0;
		for (int k = 0; k < TESTS; k++){
			sum= sum + tab[j][k];
		}
		//cout << sum << endl;
		double median = percentile(tab[j],0.5);
		double pct01 = percentile(tab[j],0.01);
		double pct99 = percentile(tab[j],0.99);
		file << (j*STEP) << "\t" << (double)sum/TESTS << "\t" << (double)median << "\t" << pct01 << "\t" << pct99 << endl;
	}
	
}

void Ploter::plotRawBias(string filename){
	ofstream file(filename);
	string line;
	
	uint64_t hash;
	uint64_t hash128[2];
	
	int i;
	vector< vector<double> > tab(CARDMAX/STEP, vector<double>(TESTS));
	
	int ca = 0;
	for(i = 0; i < TESTS; i ++){
		cout << i << endl;
		Hll hll(14);
		for(int j = 0; j < CARDMAX; j++){
			MurmurHash3_x86_128(&ca, 4, 0, &hash128);
			ca++;
			hash = hash128[0];
			hll.AddItem64(hash);
			if(j%STEP == 0){
				double count = hll.CountRaw64();
				count = (double)abs(count-j)/j;
				tab[j/STEP][i]=count;
			}
		}
	}
	
	for(int j = 0; j < CARDMAX/STEP; j++){
		double sum = 0;
		for (int k = 0; k < TESTS; k++){
			sum= sum + tab[j][k];
		}
		//cout << sum << endl;
		double median = percentile(tab[j],0.5);
		double pct01 = percentile(tab[j],0.01);
		double pct99 = percentile(tab[j],0.99);
		file << (j*STEP) << "\t" << (double)sum/TESTS << "\t" << (double)median << "\t" << pct01 << "\t" << pct99 << endl;
	}
	
}



void Ploter::plotLinearBias(string filename){
	ofstream file(filename);
	string line;
	
	uint64_t hash;
	uint64_t hash128[2];
	
	int i;
	vector< vector<double> > tab(CARDMAX/STEP, vector<double>(TESTS));
	
	int ca = 0;
	for(i = 0; i < TESTS; i ++){
		cout << i << endl;
		Hll hll(14);
		for(int j = 0; j < CARDMAX; j++){
			MurmurHash3_x86_128(&ca, 4, 0, &hash128);
			ca++;
			hash = hash128[0];
			hll.AddItem64(hash);
			if(j%STEP == 0){
				double count = hll.CountLinear64();
				count = (double)abs(count-j)/j;
				tab[j/STEP][i]=count;
			}
		}
	}
	
	for(int j = 0; j < CARDMAX/STEP; j++){
		double sum = 0;
		for (int k = 0; k < TESTS; k++){
			sum= sum + tab[j][k];
		}
		//cout << sum << endl;
		double median = percentile(tab[j],0.5);
		double pct01 = percentile(tab[j],0.01);
		double pct99 = percentile(tab[j],0.99);
		file << (j*STEP) << "\t" << (double)sum/TESTS << "\t" << (double)median << "\t" << pct01 << "\t" << pct99 << endl;
	}
	
}