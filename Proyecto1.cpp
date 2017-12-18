#include "Tablero.h"
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <utility>
#include <memory>

using namespace std;
//Para el tablero
int** crearTablero(int);
void imprimirTablero(int**, int);
void eliminarTablero(int**, int);
//Para verificar la victoria
bool RevisarFilas(int**,int,int);
bool RevisarColumnas(int**,int,int);
bool RevisarDiagonalesIaD(int**,int);
bool RevisarDiagonalesDaI(int**,int);
//Es primo?
bool EsPrimo(int);
//Jugada del AI
bool JugadaAI(int**,int);//Ai de prueba (Nivel Facil)
bool JugadaAIM(int**,int);//Ai (Nivel medio)[En proceso]
//main del juego
int main(){
	cout<<endl;
	int opcion = 0;
	Tablero Matriz2;
	while(opcion != 2){
		cout<<"Proyecto de progra 3"<<endl;
		cout<<"X y O primo (usando numeros)"<<endl;
		cout<<"----Menu-----"<<endl
		<<"1)Jugar"<<endl
		<<"2)Salir"<<endl;
		cin>>opcion;
		switch(opcion){
			case 1:{
				int opcion2 = 2;
				cout<<"Menu de juego"<<endl
				<<"1)2x2"<<endl
				<<"2)3x3"<<endl
				<<"3)4x4"<<endl;
				cin>>opcion2;
				int** Tablero1;
				int size = 2;
				int NumMaxJ = 4;
				switch(opcion2){
					case 1:{
						size = 2;
						NumMaxJ = 4;
						Tablero1 = crearTablero(size);
					}
					break;
					case 2:{
						size = 3;
						NumMaxJ = 9;
						Tablero1 = crearTablero(size);
					}
					break;
					case 3:{
						size = 4;
						NumMaxJ = 16;
						Tablero1 = crearTablero(size);
					}
					break;
					default:{}
					break;
				}
				imprimirTablero(Tablero1,size);
				int ContadorTurno = 0;
				string Jugador;
				cout<<"Ingrese el nombre del jugador: "<<endl;
				cin>>Jugador;
				if(Jugador == ""){
					Jugador = "Juagdor1";
				}
				string Ganador;
				bool Continua = true;
				bool RF = false;//revision de filas
				bool RC = false;//revision de columnas
				bool RDID = false;//revision de diagonal de izquierda a derecha
				bool RDDI = false;//revision de diagonal de derecha a izquierda
				while(Continua){
					if(ContadorTurno%2== 0){
						cout<<"Es el turno de: "<<Jugador<<endl;
						cout<<"Ingrese el numero a ingresar: "<<endl;
						int numI = 0;
						char NumI;
						cin>>NumI;
						if(isdigit(NumI)){
							numI = NumI-48;
							while(numI < 0 || numI > 9){
								cout<<"Numero Invalido ingrese uno otra vez:"<<endl;
								cin>>numI;
							}
						}else{
							cout<<"No es posible ingresar algo diferente a un numero"<<endl;
							cin.fail();
							cin.clear();
							cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
							numI=0;
						}
						cout<<"Ingrese la columna donde ingresara el numero"<<endl;
						int columna;
						cin>>columna;
						while(columna < 0 || columna >= size){
							cout<<"Numero de columna inexistente porfavor ingrese otra:"<<endl;
							cin>>columna;
						}
						cout<<"Ingrese la fila donde ingresara el numero"<<endl;
						int fila;
						cin>>fila;
						while(fila < 0 || fila >= size){
							cout<<"Numero de fila invalida, ingrese otra:"<<endl;
							cin>>fila;
						}
						if(Tablero1[fila][columna] == -1){
							Tablero1[fila][columna] = numI;
						}
						//Aqui se hacen las revisiones
						RF = RevisarFilas(Tablero1,size,fila);
						RC = RevisarColumnas(Tablero1,size,columna);
						RDID = RevisarDiagonalesIaD(Tablero1,size);
						RDDI = RevisarDiagonalesDaI(Tablero1,size);

						if(ContadorTurno == NumMaxJ-1){
							Continua = false;
							cout<<"Ya no hay mas turnos"<<endl;
						}
						if(RF || RC || RDID || RDDI){
							Continua = false;
							cout<<"El Ganador es: "<<Jugador<<endl;
						}
					}else{
						cout<<"Es el turno del ai."<<endl;
						bool CON = JugadaAI(Tablero1,size);
						//Revisar si gano el AI


						if(ContadorTurno == NumMaxJ-1){
							Continua = false;
							cout<<"Ya no hay mas turnos"<<endl;
						}
						if(CON){
							Continua = false;
							cout<<"El ganador es el AI"<<endl;
						}
					}
					imprimirTablero(Tablero1,size);
					unique_ptr<Tablero> Matriz2(new Tablero(size));
					cout<<endl;
					ContadorTurno++;
				}
				eliminarTablero(Tablero1,size);

			}
			break;
			default:{}
			break;
		}
	}
	return 0;
}
//Para el tablero
int** crearTablero(int size){
	int** matriz = new int*[size];
	for(int i = 0; i < size; i++){
		matriz[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matriz[i][j] = -1;
		}
	}
	return matriz;
}
void imprimirTablero(int** tablero, int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<"["<<tablero[i][j]<<"]";
		}
		cout<<endl;
	}
}
void eliminarTablero(int** tablero, int size){
	for(int i=0;i<size;i++){
		delete[]tablero[i];
		tablero[i] = NULL;
	}
	delete[]tablero;
}
//Para tomar los numeros
bool RevisarFilas(int** matriz,int size, int fila){
	bool Es = false;
	int num = 0;
	for (size_t i = 0; i < size; i++) {
		if(matriz[fila][i] != -1){
			num = num + ((matriz[fila][i])*pow(10,size - (i + 1)));
		}else{
			num = -9999;
		}
	}
	if(num < 0){
		return false;
	}else{
		return EsPrimo(num);
	}
}
bool RevisarColumnas(int** matriz,int size,int columna){
	bool Es = false;
	int num = 0;
	for (size_t i = 0; i < size; i++) {
		if(matriz[i][columna] != -1){
			num = num + ((matriz[i][columna])*pow(10,size - (i + 1)));

		}else{
			num = -9999;
		}
	}
	if(num < 0){
		return false;
	}else{
		return EsPrimo(num);
	}
}
bool RevisarDiagonalesIaD(int** matriz,int size){
	bool Es = false;
	int num = 0;
	for(size_t i = 0; i < size; i++){
		for(size_t j = 0; j < size;j++){
			if(i == j){
				if(matriz[i][j] != -1){
					num = num + ((matriz[i][j])*pow(10,size - (i + 1)));
				}else{
					num = -9999;
				}
			}
		}
	}
	if(num < 0){
		return false;
	}else{
		return EsPrimo(num);
	}
}
bool RevisarDiagonalesDaI(int** matriz, int size){
	bool Es = false;
	int num = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size;j++){
			if((i + j + 1) == size){
				if(matriz[i][j] != -1){
					num = num + ((matriz[i][j])*pow(10,size - (i + 1)));
				}else{
					num = -9999;
				}
			}
		}
	}
	if(num < 0){
		return false;
	}else{
		return EsPrimo(num);
	}
}
//Revisar si el numero es primo
bool EsPrimo(int num){
	int a = 0;
	bool Primo = false;
	for(int i=1;i<(num+1);i++){
		if(num%i==0){
			a++;
		}
	}
	if(a!=2){
		return false;
	}else{
		cout<<num<<endl;
		cout<<"Es primo"<<endl;
		return true;
	}
}
//Jugadas del AI (solo de prueba)(nivel facil)
bool JugadaAI(int** Tablero, int size){
	bool RF = false;
	bool RC = false;
	bool RDID = false;
	bool RDDI = false;
	bool seguir = true;
	int numI = 0;
	int columna = 0;
	int fila = 0;
	while(seguir){
		srand(time(0));
		numI = rand()%10;
		columna = rand()%size;
		fila = rand()%size;
		//verificar que el espacio este vacio (contiene -1)
		if(Tablero[fila][columna] == -1){
			Tablero[fila][columna] = numI;
			seguir = false;
		}else{
			seguir = true;
		}
	}
	RF = RevisarFilas(Tablero,size,fila);
	RC = RevisarColumnas(Tablero,size,columna);
	RDID = RevisarDiagonalesIaD(Tablero,size);
	RDDI = RevisarDiagonalesDaI(Tablero,size);
	if(RC || RF || RDID || RDDI){
		cout<<"El ganador es el AI"<<endl;
		return true;
	}else{
		return false;
	}
}
//Juagdas del ai (En proceso)(Nivel medio)
bool JugadaAIM(int**Tablero,int size){
	bool RF = false;
	bool RC = false;
	bool RDID = false;
	bool RDDI = false;
	bool seguir = true;
	int numI = 0;
	int columna = 0;
	int fila = 0;
	srand(time(0));
	//Nueva manera de pensar para el ai
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if(Tablero[i][j] == -1){
				if(i != 0 && i <= size - 1){
					if(j != 0 && j <= size - 1){
						if(Tablero[i-1][j-1] != -1){
							numI = rand()%10;
							Tablero[i][j] == numI;
						}else if(Tablero[i][j-1] != -1){
							numI = rand()%10;
							Tablero[i][j] == numI;
						}else if(Tablero[i-1][j] != -1){
							numI = rand()%10;
							Tablero[i][j] == numI;
						}
					}else if(i == 0){

					}else{

					}
				}else{

				}
			}else{

			}
		}
	}
	//
	RF = RevisarFilas(Tablero,size,fila);
	RC = RevisarColumnas(Tablero,size,columna);
	RDID = RevisarDiagonalesIaD(Tablero,size);
	RDDI = RevisarDiagonalesDaI(Tablero,size);
	if(RC || RF || RDID || RDDI){
		cout<<"El ganador es el AI"<<endl;
		return true;
	}else{
		return false;
	}
	return false;
}
