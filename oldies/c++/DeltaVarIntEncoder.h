#ifndef DeltaVarIntEncoder_H
#define DeltaVarIntEncoder_H

#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

class DeltaVarIntEncoder 
{
 public:
  DeltaVarIntEncoder();
  void AppendInt32(int value);  // value must be >= 0.
  const string& data() const { return data_; }
 private:
  string data_;
  int prev;
  char converter(int value);
  void encodeVarint(uint64_t value, uint8_t* output, uint8_t* outputSizePtr);
};


#endif