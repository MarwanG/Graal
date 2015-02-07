#include "DeltaVarIntDecoder.h"


DeltaVarIntDecoder::DeltaVarIntDecoder(const string& data){
	t = data;
	pos = 0;
	prev = -1;
	size = t.size();
}


uint64_t DeltaVarIntDecoder::decodeVarint(uint8_t* input, uint8_t inputSize) {
uint64_t ret = 0;
   for (uint8_t i = 0; i < inputSize; i++) {
      ret |= (input[i]&127) << (7*i);
      //If the next-byte flag is set
      if(!(input[i] & 128)) {
         break;
   }
}
return ret;
}

uint64_t DeltaVarIntDecoder::decodeVarint16(uint16_t* input, uint8_t inputSize) {
uint64_t ret = 0;
   for (uint16_t i = 0; i < inputSize; i++) {
      ret |= (input[i]&127) << (7*i);
      //If the next-byte flag is set
      if(!(input[i] & 128)) {
         break;
   }
}
return ret;
}


uint8_t * DeltaVarIntDecoder::getChar(){
	pos = pos + 1;
	// cout << bitset<8>((uint8_t *) &t.at(pos-1)) << endl;
	return (uint8_t *) &t.at(pos-1);
}



int DeltaVarIntDecoder::getValue(){
	uint32_t total;
 	int nb = 0;
 	int shift = 0;
	while(1){
		uint8_t* input = getChar();
		
		if (bitset<8>(input[0])[7] ==  1){
			cout << "found 1 " << endl;
			cout << bitset<8>(input[0]) << endl;
			cout << "remove poid fort" << endl;
			*input&=0x7f;
			cout << bitset<8>(input[0]) << endl;
			total |= (*input << shift);
		}else{
			cout << "found 2 " << endl;
			cout << bitset<8>(input[0]) << endl;
			total = total << shift;
			// total |= *input;
			cout << "TOTAL : " << endl;
			cout << bitset<16>(total) << endl;
			return total;
		}
		shift = shift + 7;
		if (shift >= 32){
			return -1;
		}
	}
}
// 	}
// }

int DeltaVarIntDecoder::GetNextBis(){
	if(pos == size){
		return -1;
	}else{
		uint8_t* input = getChar();
		if (bitset<8>(input[0])[7] ==  1){
			*input&= ~(1 << 7);
			uint8_t* input2 = getChar();
			if (bitset<8>(input2[0])[7] ==  1){
				*input2&= ~(1 << 7);
				uint8_t* input3 = getChar();
				uint32_t * total = (uint32_t*) malloc (sizeof(uint32_t) * 24);
				*total = *input;
				*total <<= 8;
				*total |= *input2;
				*total <<= 8;
				*total |= *input3;    
				return 0; 
			}else{
				uint16_t  total;
				// *total = *input;
				// *total <<= 8;
				// *total |= *input2;
				// cout << bitset<16>(total[0]) << endl;
				// uint64_t tmp = decodeVarint16(total, 3);
				cout << "got my shit" << endl;
				cout << bitset<8>(input[0]) << endl;
				cout << bitset<8>(input2[0]) << endl;
				total = *input2;
				total <<= 8;
				total |= *input;
				cout << bitset<16>(total) << endl;
				uint64_t tmp = 1;
				if (prev == -1) {
					prev = (int)tmp;
					return (int)tmp;
				}else{
					int tmp2 = prev;
					prev = (int)tmp;
					return (int) tmp + tmp2;
				}
			}                                     		
		}else{
			uint64_t tmp = decodeVarint(input, 3);
			if (prev == -1) {
				prev = (int)tmp;
				return (int)tmp;
			}else{
				int tmp2 = prev;
				prev = (int)tmp;
				return (int) tmp + tmp2;
			}
		}
	}
}

int DeltaVarIntDecoder::GetNext(){
	if(pos == size){
		return -1;
	}else{
		uint8_t* input = (uint8_t *) &t.at(pos);
		pos = pos +1 ;

		uint64_t tmp = decodeVarint(input, 3);
	
		if (prev == -1) {
			prev = (int)tmp;
			return (int)tmp;
		}else{
			int tmp2 = prev;
			prev = (int)tmp;

			return (int) tmp + tmp2;
		}
	}
}

/*int umain(){
	DeltaVarIntEncoder dd;
	dd.AppendInt32(5);
	dd.AppendInt32(40);
	dd.AppendInt32(50);
	dd.AppendInt32(60);
	dd.AppendInt32(80);
	// dd.AppendInt32(140);
	// dd.AppendInt32(150);
	dd.AppendInt32(600);
	dd.AppendInt32(840);
	// dd.AppendInt32(1000);

	DeltaVarIntDecoder dd1 (dd.data());
	cout << "size : " << dd1.size << endl;
	int tmp = 0;
	while( tmp != -1 ){
		tmp = dd1.getValue();
		// cout << tmp << endl;
	}
	return 0;
}*/