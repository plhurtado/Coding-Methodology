#include "byte.h"
#include <iostream>

using namespace std;
void  on(byte &b, int pos){
    byte mask;
    if ((pos>=0) && (pos<8)){
        mask = 0x1 << pos;
        b = b | mask;
    }
}

void  off(byte &b, int pos){
    byte mask;
    if ((pos>=0) && (pos<8)){
        mask = 0x1 << pos;
        mask = ~mask;
        b = b & mask;
    }
}

bool  get(byte b, int pos){
    bool status;
    byte mask = 0x1 << pos;

    status = (b & mask) > 0;
    return status;
}

void  print(byte b){
    byte mask;
    int v[8]={0};

    for (int i = 0; i<8 ; i++){
        mask = 0x1 << i;
        if ((b & mask) > 0)
            v[i]=1;
        else
            v[i]=0;
    }

    for (int j=7; j>=0; j--){
        cout << v[j];
    }

    cout << endl;
}

void  encender(byte &b){
    b=0xFF;
}

void  apagar(byte &b){
    b=0x0;
}

void  asignar(byte &b, const bool v[]){
    int posicion;
    for (int i=0; i<8; i++){
        posicion = 7 - i;
        if (v[i])
            on(b, posicion);
        else
            off(b, posicion);
    }
}

void  volcar(byte b, bool v[]){
    int posicion;
    for (int i = 0; i < 8; i++){
        posicion = 7-i;
        v[i] = get (b, posicion);
    }

}


void  encendidos(byte b, int posic[], int &cuantos){
    int pos = 0;
    cuantos = 0;
    for (int i = 0; i<8; i++){
        if (get(b, i)){
            posic[pos]=i;
            pos++;
            cuantos++;
        }
    }

}
