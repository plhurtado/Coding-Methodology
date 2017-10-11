/**
  * @file
  * @brief Fichero con las definiciones para codificar y revelar mensajes
  *
  */

#include <iostream>
#include <cstring>
#include "codificar.h"
#include "byte.h"
#include "imagen.h"
#include "pgm.h"

using namespace std;


bool ocultar(Imagen &img, char mensaje[]){

    //Comprobacion de errores
    if ( (((strlen(mensaje)+1)*8) <= img.columnas()*img.filas()) && mensaje[0]!='\0' ){
        int posicion = 0;
        bool bit;
        byte valor;

        for (int i=0; i<=strlen(mensaje); i++){
            for (int j=7; j>=0; j--){
                bit = get (mensaje[i], j);
                valor = img.getPos(posicion);

                if (bit)
                    on(valor, 0);
                else
                    off(valor,0);

                img.setPos (posicion, valor);
                posicion++;
            }
        }
        return true;
    }

    else
        return false;
}

bool revelar(Imagen &img, char mensaje[], const int max){
    unsigned char letra;
    int indice = 0;
    int posicion = 0;

    do{
        for (int i=7; i>=0; i--){

            if (get (img.getPos(posicion), 0))
                on (letra, i);
            else
                off (letra, i);

            posicion++;
        }

        mensaje[indice] = letra;
        indice++;

    }while (posicion < (img.filas() * img.columnas()) && letra != '\0');

    if (posicion >= (img.filas() * img.columnas()) || strlen(mensaje) > max)
        return false;
    else
        return true;


}

