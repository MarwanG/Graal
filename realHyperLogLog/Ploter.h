//
//  Ploter.h
//  realHyperLogLog
//
//  Created by Steven on 07/02/2015.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#ifndef __realHyperLogLog__Ploter__
#define __realHyperLogLog__Ploter__

#include <stdio.h>
#include <vector>


using namespace std;

class Ploter {
	
public:
	double percentile(vector <double> v , double x);
	void plotRawHll(string filename);
	void plotCorrectedHll(string filename);
	void plotCorrectedHllBias(string filename);
	void plotLinear(string filename);
	void plotLinearBias(string filename);
	void plotRawBias(string filename);
	
private:
	vector<double> makeVector();
	double interpolation(double x, double x1, double y1, double x2, double y2);
};

#endif /* defined(__realHyperLogLog__Ploter__) */
