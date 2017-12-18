#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
using namespace std;

class Tablero{
	private:
		int Tamano;
	public:
		Tablero();
		Tablero(int);
		int getTamano();
		void setTamano(int);
		~Tablero();
		//importantes
		int** CrearTablero();
		void EliminarTablero(int**);
};
#endif
