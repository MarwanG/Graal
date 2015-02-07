//
//  MyMap.cpp
//  realHyperLogLog
//
//  Created by Steven Varoumas on 06/02/15.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#include "MyMap.h"

#define MAXSIZE 100

MyMap::MyMap(){
    bigList = Bitmap();
    smallList = vector<uint32_t>();
}

void MyMap::add(uint64_t v){
    int key = v >> (64-14);
    uint64_t w = v & (((uint64_t)1<<(64-14))-1);
    int r = __builtin_clzll(w) - 14 + 1;
    int value = r;
    /*cout << bitset<64>(v) << endl;
    cout << "key =" << bitset<14>(key) << endl;
    cout << "value = " << bitset<6>(value) << endl;
    */
    int val = key << 6 | value;
    //cout << bitset<20>(val) << endl;
    if (smallList.size() >= MAXSIZE){
        //cout << "on merge !" << endl;
        bigList = merge();
        smallList.clear();
        smallList.push_back(val);
    }else{
        smallList.push_back(val);
    }
    displaySmall();
}

int MyMap::getKey(int i){
    return smallList[i] >> (32-14);
}

int MyMap::getValue(int i){
    return smallList[i] & (((uint32_t)1 << 18) -1);
}

Bitmap MyMap::merge(){
    Bitmap newList = Bitmap();
    
    //trie la liste smallList
    sort(smallList.begin(), smallList.end());
    
    int iSmall =0;
    int iBig =0;
    
    
    
    while(iBig < bigList.getRealSize() && iSmall < smallList.size()){
        //cout << "merging ..." << endl;
        int keyBig = bigList.getKey(iBig);
        int valueBig = bigList.getValue(iBig);
        int big = bigList.read(iBig);
        int keySmall = getKey(iSmall);
        int valueSmall = getValue(iSmall);
        
        if(keySmall < keyBig){
            newList.write(smallList[iSmall]);
            iSmall++;
        }
        else if(keySmall > keyBig){
            newList.write(big);
            iBig++;
        }
        else{
            if(valueSmall > valueBig)
                newList.write(smallList[iSmall]);
            else
                newList.write(big);
            //UpdateMax(key,value);
            iSmall++;
            iBig++;
        }
    }
    
    
    // On stocke ce qui reste
    if(iSmall < smallList.size()){
       // cout << "adding from the small list" << endl;
        for(int i = iSmall; i < smallList.size(); i ++){
            newList.write(smallList[i]);
        }
    }
    
    if(iBig < bigList.getRealSize()){
        
      //  cout << "adding from the big list (of size " << bigList.getRealSize() << ")" << endl;
        for(int i = iBig; i < bigList.getRealSize(); i ++){
            newList.write(bigList.read(i));
        }
    }
    
    
    
    return newList;
}

void MyMap::UpdateMax(int key, int value){
	int val = key << 6 | value;
	if (smallList.size() >= MAXSIZE){
		bigList = merge();
		smallList.clear();
		smallList.push_back(val);
	}else{
		smallList.push_back(val);
	}
	//displaySmall();
}

vector<char> MyMap::GetDense(){
    vector<char> tab(1<<14);
	bigList = merge();
	smallList.clear();
	cout << bigList.getSize() << endl;
	for(int i = 0; i < bigList.getSize(); i++){
		int index = bigList.getKey(i);
		cout << index << endl;
		char value = (char)bigList.getValue(i);
		//cout << "devient : " << bitset<8>(value) << ")" <<  endl;
		tab[index] = value;
		cout << bitset<8>(tab[index]) << endl;
	}
    return tab;
}

void MyMap::displaySmall(){
   // cout << "content of the small list " << endl;
    for(int i = 0; i < smallList.size(); i ++){
        cout << bitset<32>(smallList[i]) << endl;
    }
}

int MyMap::BytesUsed() const{
    return bigList.getSize();
}
