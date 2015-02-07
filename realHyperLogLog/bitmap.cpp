//
//  bitmap.cpp
//  hyperLogLog
//
//  Created by Steven Varoumas on 06/02/15.
//  Copyright (c) 2015 Steven Varoumas. All rights reserved.
//

#include "bitmap.h"
#include <math.h>


Bitmap::Bitmap(){
    list = (uint32_t*) malloc (1*sizeof(uint32_t));
    size = 0;
    realsize = 0;
}

uint32_t Bitmap::val(int a, int b){
    unsigned int v = 0;
    for(int i = 0; i < b; i++){
        v+=get(a) << i;
        a--;
    }
    return v;
}

unsigned int Bitmap::get(char b){
    return list[b >> 5] >> (31 - (b%32)) & 1;
}

void Bitmap::display(){
    
    for(int i = 0; i < size/32; i++){
        cout << bitset<32>(list[i]);
    }
    cout << endl;
    for(int i = 0; i < size; i++){
        if(i%20==0)
            cout << "[";
        
        else
            cout << "_";
    }
    cout << endl;
    for(int i = 0; i < size; i++){
        if(i%32==0)
            cout << "|";
        
        else
            cout << "_";
    }
    cout << endl;
}

uint32_t Bitmap::read(int i){
    return val(i*20+19,20);
}

int Bitmap::getKey(int i){
    return read(i) >> 6;
}

int Bitmap::getValue(int i){
    return read(i) & ((1<<6)-1);
}


int Bitmap::getSize() const{
    return size/32;
}

int Bitmap::getRealSize() const{
    return realsize/20;
}

void Bitmap::write(uint32_t val){
    // en vrai on ne veut ajouter que 20 bits (les 20 bits de poids faible)!!!
    
    
    //val >>= 12;
    
    val &=(1<<20)-1;
    
    cout << "on ajoute " << bitset<20>(val) << endl;
    
    //cout << "il reste " << (size-realsize) << " places dans la liste" << endl;
    
    // C'est le min entre 20 et la différence
    int sizeRab = min(20,(size-realsize));
    
    if(sizeRab !=0){
        // On remplit jusqu'au bout la case en cours
        uint32_t rab = (val << 12) >> (32-(size-realsize));
        
        cout << "rab=" << (size-realsize) << endl;
        
        
        //cout << "la dernière case de la liste est " << bitset<32>(bigList[size/32-1]) << endl;
        list[size/32-1] >>= sizeRab;
        list[size/32-1] <<= sizeRab;
        if(realsize < size){
            list[size/32-1] |= rab;
            realsize+=sizeRab;
        }
    }
    
    // on fait une nouvelle case au bout pour stocker le reste
    // calcul du reste à placer
    
    uint32_t reste = val & (1 << (20-sizeRab))-1;
    
    
    
    // si le reste est différent de 0 :
    
    if(reste !=0){
        cout << "Le reste à ranger est " << bitset<20>(reste) << endl;
        
        cout << "longueur = " << (20-sizeRab) << endl;
        size+=32;
        list = (uint32_t*) realloc (list, (size/32) * sizeof(uint32_t));
        //cout << "j'ai créé une nouvelle case !! pour l'instant elle contient ";
        //cout << bitset<32>(bigList[size/32-1]) << endl;
        
        // maintenant on met le reste dedans !
        
        list[size/32-1] |= reste;
        
        
        //cout << "et maintenant "<< bitset<32>(bigList[size/32-1]) << " <- il va falloir le décaler !" << endl;
        // et on le met au plus à droite possible
        
        list[size/32-1] <<= (32-(20-sizeRab));
        
        realsize+=(20-sizeRab);
        
        //cout << "et enfin "<< bitset<32>(bigList[size/32-1]) << endl;
        
    }
    
    cout << "realsize = " << realsize << endl;;
    display();
    
    
}