/**
  * @file
  * @brief Fichero con las definiciones para las funciones sobre las imagenes
  *
  */

#include <iostream>
#include "imagen.h"
#include "byte.h"
#include "pgm.h"

using namespace std;

Imagen::Imagen(){
    nfilas = 0;
    ncolumnas = 0;
    datos = 0;
}

Imagen::Imagen(int filas, int columnas){
    datos = new byte [filas*columnas];
    nfilas = filas;
    ncolumnas = columnas;

    /*for (int i=0; i<filas*columnas; i++)
        datos[i]=0;*/
}

void Imagen::crear(int filas, int columnas){
    if (datos != 0)
        destruir();

    nfilas = filas;
    ncolumnas = columnas;

    datos = new byte [filas*columnas];

    for (int i = 0; i < filas*columnas; i++){
        datos[i]=0;
    }
}

void Imagen::destruir(){
    if (datos != NULL){
        delete [] datos;
        nfilas = 0;
        ncolumnas = 0;
        datos = 0;
    }
}

int Imagen::filas(){
    return nfilas;
}

int Imagen::columnas(){
    return ncolumnas;
}

void Imagen::set(int y, int x, byte v){
     datos[y * ncolumnas + x] = v;
}

byte Imagen::get(int y, int x){
    return datos[y * ncolumnas + x];
}

void Imagen::setPos(int i, byte v){
    datos[i] = v;
}

byte Imagen::getPos(int i){
    return datos[i];
}


bool Imagen::leerImagen(const char nombreFichero[]){
    int filas, columnas;
    TipoImagen tipo = infoPGM(nombreFichero, filas, columnas);

    crear(filas, columnas);

    if (tipo == IMG_PGM_BINARIO)
        if (filas * columnas <= MAXPIXELS)
            return leerPGMBinario(nombreFichero, datos, nfilas, ncolumnas);
        else
            return false;
    else{
        if (tipo == IMG_PGM_TEXTO)
            if (filas * columnas <= MAXPIXELS){
                return leerPGMTexto(nombreFichero, datos, nfilas, ncolumnas);
            }
            else
                return false;
        else
            return false;
    }
}

bool Imagen::escribirImagen(const char nombreFichero[]){
	return escribirPGMTexto(nombreFichero, datos, nfilas, ncolumnas);
}

void Imagen::rotar(){
    int filas = ncolumnas;
    int columnas = nfilas;
    int aux;
    int posicion=0;

    Imagen modificada(filas, columnas);

    for (int i = 0; i < ncolumnas; i++){
        for (int j = nfilas-1; j>=0 ; j--){
            modificada.setPos(posicion, datos[j*ncolumnas + i]);
            posicion++;
        }
    }

    aux = nfilas;
    nfilas = ncolumnas;
    ncolumnas = aux;

    for (int i=0; i < filas; i++)
        for (int j=0; j < columnas; j++)
            datos[i*ncolumnas + j] = modificada.get(i, j);

    modificada.destruir();
}

void Imagen::rotacion(int grados, bool shorario){
    if (shorario){
        switch (grados){
            case 90:
                rotar();
                break;

            case 180:
                for (int i=0; i<2; i++)
                    rotar();
                break;

            case 260:
                for (int i=0; i<3; i++)
                    rotar();
                break;
        }
    }
    else{
        switch (grados){
            case 90:
                for (int i=0; i<3; i++)
                    rotar();
                break;

            case 180:
                for (int i=0; i<2; i++)
                    rotar();
                break;

            case 260:
                rotar();
                break;
        }
    }
}















