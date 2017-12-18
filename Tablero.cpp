#include "Tablero.h"
#include <iostream>

using namespace std;

Tablero::Tablero(){
	Tamano = 0;
}
Tablero::Tablero(int pTamano){
	Tamano = pTamano;
}
int Tablero::getTamano(){
	return Tamano;
}
void Tablero::setTamano(int pTamano){
	Tamano = pTamano;
}
Tablero::~Tablero(){}
int** Tablero::CrearTablero(){
	int** matriz = new int*[Tamano];
	for(int i = 0; i < Tamano; i++){
		matriz[i] = new int[Tamano];
	}
	for (int i = 0; i < Tamano; i++) {
		for (int j = 0; j < Tamano; j++) {
			matriz[i][j] = -1;
		}
	}
	return matriz;
}
void Tablero::EliminarTablero(int** tablero){
	for(int i=0;i<Tamano;i++){
		delete[]tablero[i];
		tablero[i] = NULL;
	}
	delete[]tablero;
}
