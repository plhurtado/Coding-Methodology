/**
@file
@author Pedro Luis Hurtado González y Juan Antonio Perez Maldonado
@date 1 de marzo de 2015, 19:33
@brief Funciones de manejo de bytes

*/

#ifndef _CODIFICAR_H_
#define	_CODIFICAR_H_

#include "imagen.h"

    /**
    @brief oculta el @p mensaje en la @p imagen
    @param img 	@p imagen donde se va a ocultar el mensaje
    @param mensaje 	@p mensaje que queremos esconder en la imagen
    */
    bool ocultar(Imagen &img, char mensaje[]);

     /**
    @brief revela el @p mensaje oculto en la @p imagen con tamaño maximo @c max
    @param img  @p imagen de donde se va a extraer el mensaje
    @param mensaje 	array donde se va a almacenar el mensaje desencriptado
    @param c    tamaño maximo que podra tener el mensaje oculto
    */
    bool revelar(Imagen &img, char mensaje[], const int max);

#endif
