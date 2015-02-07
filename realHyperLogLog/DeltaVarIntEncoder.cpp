#include "DeltaVarIntEncoder.h"



DeltaVarIntEncoder::DeltaVarIntEncoder(){
	prev = 0;
}

void DeltaVarIntEncoder::encodeVarint(uint64_t value, uint8_t* output, uint8_t* outputSizePtr) {
uint8_t outputSize = 0;
   while (value > 127) {
      output[outputSize] = ((uint8_t)(value & 127)) | 128;
      value >>= 7;
      outputSize++;
   }
   output[outputSize++] = ((uint8_t)value) & 127;
   *outputSizePtr = outputSize;
}



void DeltaVarIntEncoder::AppendInt32(int value){
	if (value > 0){
		cout << "value : " << value  << endl;
		char * c;
		int tmp = value - prev;
		prev = tmp;
		uint64_t v = (uint64_t) tmp;
  		uint8_t *output = (uint8_t*) malloc(sizeof(uint8_t)*8);
   		uint8_t *outputSizePtr  = (uint8_t*) malloc(sizeof(uint8_t)*8);
   		encodeVarint(v,output,outputSizePtr);
   		for(int i = 0; i < *outputSizePtr; i ++)
            cout << "output [" << i << "] =" << bitset<8>(output[i]) << endl;
   		c =  (char *)output;
   		data_.append(c);
	}else{
		//rien wht should i do ? ignore or throw.
	}
}

// int main()
// {
// 	DeltaVarIntEncoder dd;
// 	dd.AppendInt32(5);
// 	dd.AppendInt32(40);
// 	dd.AppendInt32(50);
// 	dd.AppendInt32(60);
// 	cout << dd.data().size() << endl;
// 	cout << dd.data() << endl;
// }