/**
  * @file
  * @brief Fichero para testear las funciones ocultar y revelar mensaje
  *
  *
  */

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "pgm.h"
#include "imagen.h"
#include "codificar.h"
#include "byte.h"

using namespace std;

int main(){
	const int MAXNOMBRE=100;
	const int MAXMENSAJE=256;
	char mensaje[MAXMENSAJE];
	char entrada[MAXMENSAJE];
	char salida[MAXMENSAJE];
	int opcion;
	int grados;
	string respuesta;
	bool shorario;
	Imagen origen;
	Imagen destino;

	cin.clear();
	cout << "Elija una de las opciones: " << endl;
	cout << "1. Ocultar mensaje" << endl;
	cout << "2. Revelar mensaje" << endl;
	cout << "3. Girar la imagen" << endl;
	cout << "4. Salir" << endl << endl;

	cout <<"Opcion: ";
	cin >> opcion;

	switch(opcion){
        case 1:
            cout << "Se ha escogido la opcion de ocultar mensaje." << endl;
            //Pedimos la ruta de la imagen
            cout << "Introduzca la imagen de entrada: ";
            cin.getline(entrada, MAXNOMBRE);
            cin.getline(entrada, MAXNOMBRE);


            //Abortamos en caso de que haya algun error
            if (!origen.leerImagen(entrada)){
                cout << "Error al leer la imagen" << endl;
                break;
            }

            //Creamos una imagen destino igual de grande que la de origen
            destino.crear(origen.filas(), origen.columnas());

            for (int i=0; i<origen.filas(); i++){
                for (int j=0; j<origen.columnas(); j++){
                    destino.set(i, j, origen.get(i,j));
                }
            }

            //Guardamos el nombre de la imagen salida
            cout << "Introduzca la imagen de salida: ";
            cin.getline(salida, MAXNOMBRE);

            //Guardamos el mensaje a ocultar
            cout << "Introduzca el mensaje: ";
            cin.getline(mensaje, MAXMENSAJE);

            //Ocultamos el mensaje en la imagen destino
            if (!ocultar(destino, mensaje)){
                cout << "Error ocultando el mensaje" << endl;
                break;
            }

            //Creamos la imagen final
            if (destino.escribirImagen(salida))
                cout << "Ocultando... " << endl;
            else
                cout << "Error al crear la nueva imagen" << endl;

            break;

        case 2:
            cout << "Se ha escogido la opcion de revelar mensaje." << endl;

            //Solicitamos la imagen donde esta el mensaje oculto
            cout << "Introduzca la imagen de entrada: ";
            cin.getline(entrada, MAXNOMBRE);
            cin.getline(entrada, MAXNOMBRE);

            //Leemos dicha imagen
            if (!origen.leerImagen(entrada)){
                cout << "Error abriendo la imagen" << endl;
                break;
            }

            //Revelamos el mensaje oculto
            if (revelar(origen, mensaje, MAXMENSAJE)){
                cout << "Revelando..." << endl;
                cout << "El mensaje obtenido es: " << mensaje << endl;
            }
            else
                cout << "Error en el revelado del mensaje" << endl;
            break;

        case 3:
            cout << "Introduzca la imagen a rotar: ";
            cin.getline(entrada, MAXNOMBRE);
            cin.getline(entrada, MAXNOMBRE);

            //Leemos dicha imagen
            if (!origen.leerImagen(entrada)){
                cout << "Error abriendo la imagen" << endl;
                break;
            }

            cout << "¿Cuántos grados desea girar la imagen?(90, 180 o 260): ";
            cin >> grados;

            cout << "¿Girará en sentido horario?: ";
            cin >> respuesta;

            if (respuesta == "si" || respuesta == "Si" || respuesta == "SI")
                shorario = true;
            else
                shorario = false;

            if (grados == 90 || grados == 180 || grados == 260){
                origen.rotacion(grados, shorario);
                if (origen.escribirImagen(entrada))
                    cout << "Ocultando... " << endl;
                else
                    cout << "Error al crear la nueva imagen" << endl;
            }
            else
                cout << "No se ha introducido un angulo de giro correcto." << endl;
            break;

        case 4:

            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opción no valida" << endl;
            break;
	}
	origen.destruir();
	destino.destruir();
}

