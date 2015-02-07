#ifndef DeltaVarIntDecoder_H
#define DeltaVarIntDecoder_H


#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

class DeltaVarIntDecoder {
 public:
  DeltaVarIntDecoder(const string& data);  // Constructor.
  int GetNext();  // Returns -1 if we have read everything.
  int GetNextBis();  // Returns -1 if we have read everything.
  uint8_t * getChar();
  int getValue();
  int size;
  char *cstr ;
 private:
 	uint64_t decodeVarint(uint8_t* input, uint8_t inputSize);
 	uint64_t decodeVarint16(uint16_t* input, uint8_t inputSize);
 	uint32_t decode2(uint8_t* encoded);

 	int pos;
 	int prev;
 	string t;
};

#endif