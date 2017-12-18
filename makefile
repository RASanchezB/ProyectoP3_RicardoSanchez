Proyecto2:	Proyecto1.o Tablero.o
	g++ -std=c++11  Proyecto1.o Tablero.o -o Proyecto2

Proyecto1.o:	Tablero.h Proyecto1.cpp
	g++ -std=c++11 -c Proyecto1.cpp

Tablero.o:	Tablero.h Tablero.cpp
	g++ -c Tablero.cpp

clear:
	rm *.o run
