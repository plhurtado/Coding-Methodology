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
    datos = new byte * [filas];

    datos[0] = new byte [filas*columnas];
    for (int i=1; i<filas; i++)
        datos[i] = datos[i-1]+columnas;

    nfilas = filas;
    ncolumnas = columnas;
}

Imagen::Imagen(const Imagen & copia){
    nfilas = copia.nfilas;
    ncolumnas = copia.ncolumnas;
    //Reservamos memoria para la imagen
    datos = new byte * [nfilas];

    datos[0] = new byte [nfilas*ncolumnas];
    for (int i=1; i<nfilas; i++)
        datos[i] = datos[i-1]+ncolumnas;

    //Copiamos los datos
    for (int i=0; i<nfilas; i++)
        for (int j=0; j<ncolumnas; j++)
            datos[i][j] = copia.datos[i][j];
}

Imagen::~Imagen(){
    destruir();
}

Imagen & Imagen::operator = (const Imagen & copia){
    if (this == &copia)
        return *this;
    else{
        nfilas = copia.nfilas;
        ncolumnas = copia.ncolumnas;
        //Reservamos memoria para la imagen
        datos = new byte * [nfilas];

        datos[0] = new byte [nfilas*ncolumnas];
        for (int i=1; i<nfilas; i++)
            datos[i] = datos[i-1]+ncolumnas;

        for (int i=0; i<nfilas; i++)
            for (int j=0; j<ncolumnas; j++)
                datos[i][j] = copia.datos[i][j];

        return *this;
    }
}

Imagen Imagen::operator + (const Imagen & copia) const{
    Imagen resultado;
    int fil, col;
    int poscol=0;

    //Nos quedamos con el numero de filas de la imagen que mas tenga
    if (nfilas > copia.nfilas)
        fil = nfilas;
    else
        fil = copia.nfilas;

    //El numero de columnas es la suma de las dos imagenes
    col = ncolumnas + copia.ncolumnas;

    //Creo la imagen rellena de negro
    resultado.crear(fil,col);

    //Inserto la primera imagen
    for (int i=0; i<nfilas; i++)
        for (poscol=0; poscol<ncolumnas; poscol++)
            resultado.set(i,poscol,datos[i][poscol]);

    //Inserto la segunda imagen
    for (int i=0; i<copia.nfilas; i++)
        for (int j=0; j<copia.ncolumnas; j++)
            resultado.set(i,j+poscol,copia.datos[i][j]);

    return resultado;
}

void Imagen::crear(int filas, int columnas){
    if (datos != 0)
        destruir();

    nfilas = filas;
    ncolumnas = columnas;

    //Reservamos memoria para la imagen
    datos = new byte * [nfilas];

    datos[0] = new byte [nfilas*ncolumnas];
    for (int i=1; i<nfilas; i++)
        datos[i] = datos[i-1]+ncolumnas;

    for (int i=0; i<nfilas; i++)
            for (int j=0; j<ncolumnas; j++)
                datos[i][j] = 0;
}

void Imagen::destruir(){
    if (datos){
        delete [] datos[0];
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
     datos[y][x] = v;
}

byte Imagen::get(int y, int x){
    return datos[y][x];
}

void Imagen::setPos(int i, byte v){
    datos[i/ncolumnas][i%ncolumnas] = v;
}

byte Imagen::getPos(int i){
    return datos[i/ncolumnas][i%ncolumnas];
}


bool Imagen::leerImagen(const char nombreFichero[]){
    int filas, columnas;
    TipoImagen tipo = infoPGM(nombreFichero, filas, columnas);

    crear(filas, columnas);

    if (tipo == IMG_PGM_BINARIO){
        if (filas * columnas <= MAXPIXELS){
            return leerPGMBinario(nombreFichero, datos, nfilas, ncolumnas);
        }
        else
            return false;
    }
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
    int aux;
    int posicion=0;

    Imagen modificada(ncolumnas, nfilas);

    for (int i = 0; i < ncolumnas; i++){
        for (int j = nfilas-1; j>=0 ; j--){
            modificada.setPos(posicion, getPos(j*ncolumnas + i));
            posicion++;
        }
    }

    aux = nfilas;
    nfilas = ncolumnas;
    ncolumnas = aux;

    (*this) = modificada;

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















