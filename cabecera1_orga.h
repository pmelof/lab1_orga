/*
Laboratorio 1 de Organizacipon de Computadores.
Patricia Melo Fuenzalida.
*/


/*Librerías a ocupar*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*DEFINICIONES*/
#define TAM_PALABRA 32
#define TAM_LINEA 1000
#define TAM_REGISTRO 32
#define TOTAL_REGISTRO 32
#define NO_HAY_ERROR -1
#define MAX_LABEL 100
#define TAM_MEMORIA 100


/*ESTRUCTURAS*/

typedef struct Registro
{
	char nombre[TAM_REGISTRO];
	int valor;
}Registro;

typedef struct Jugada
{
	Registro jugador;
	int posicion;
	int instruccion;	// 0 agrega jugada (addi), 1 quita jugada (subi).
	struct Jugada* sgte; 
}Jugada;


/*DEFINICIÓN DE FUNCIONES*/

void iniciarRegistros(Registro* registros);
int buscarRegistro(char* reg, Registro* registros);
int validarSw(char* rt, Registro* registros);
Jugada* crearJugada(int pos, Registro jugador, char* instruc);
Jugada* insertarJugada(Jugada* lista, int pos, Registro jugador, char* instruc);
void mostrarLista(Jugada* lista);
Jugada* leerEntrada(char* nombre, Registro* registros, Jugada* lista);