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

  void AddItem(unsigned int n);

  double Count();

private : 
  int* buckets;

  int b;

  int m; 

};
 
#endif
