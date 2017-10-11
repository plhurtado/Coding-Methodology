
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g -c -I$(INC)


all: $(BIN)/prueba

bin/prueba : obj/prueba.o lib/libimagen.a
	g++ -g obj/prueba.o -l imagen -o bin/prueba -L lib

lib/libimagen.a : obj/imagen.o obj/pgm.o obj/codificar.o obj/byte.o
	ar rvs lib/libimagen.a obj/pgm.o obj/imagen.o obj/codificar.o obj/byte.o

obj/imagen.o : src/imagen.cpp
	g++ -c src/imagen.cpp -o obj/imagen.o -I include/

obj/pgm.o : src/pgm.cpp
	g++ -c src/pgm.cpp -o obj/pgm.o -I include/

obj/codificar.o : src/codificar.cpp
	g++ -c src/codificar.cpp -o obj/codificar.o -I include/

obj/byte.o : src/byte.cpp
	g++ -c src/byte.cpp -o obj/byte.o -I include/

obj/prueba.o : src/prueba.cpp
	g++ -c src/prueba.cpp -o obj/prueba.o -I include/

# ************ documentación *******

documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
clean:
	echo "Limpiando..."
	rm obj/*.o

mrproper: clean
	rm bin/*
