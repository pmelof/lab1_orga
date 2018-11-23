/*
Laboratorio 2 de Organizacipon de Computadores.
Patricia Melo Fuenzalida.
*/


/*Librerías a ocupar*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*DEFINICIONES*/
#define INCOMPLETO -1
#define COMPLETO 1
#define TAM_PALABRA 32
#define TAM_REGISTRO 32
#define TOTAL_REGISTRO 32


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
	int instruccion;	// 0 agrega jugada (addi o sw), 1 quita jugada (subi).
	struct Jugada* sgte; 
}Jugada;


/*DEFINICIÓN DE FUNCIONES*/

/*
Inicio todas las etapas con valor 0.
Entrada: Nada. 
Salida: Void.
*/
void inciarEtapas():


/*
Quita el salto de línea al final de la frase.
Entrada: Una frase.
Salida: Void.
*/
void quitarSaltoLinea(char *frase);


/*
Inicio los registros todos con valor 0 y con su respectivo nombre.
Entrada: Arreglo de registros. 
Salida: Void.
*/
void iniciarRegistros(Registro* registros);


/*
Busca un registro a partir de su nombre.
Entrada: Nombre de un registro y arreglo de registros.
Salida: Posición del registro en el arreglo.
*/
int buscarRegistro(char* reg, Registro* registros);


/*
Separa num($reg) en num y $reg, ve si $reg es $sp, si lo es puede acceder a la memoria del tablero.
Entrada: Registro rt, arreglo de registros.
Salida: Num de rt.
*/
int validarSw(char* rt, Registro* registros);


/*
Crea un nodo jugada con los datos que recibe de entrada.
Entrada: Posición del tablero donde se juega, jugador que juega, instrucción con la que juega.
Salida: Nodo jugada.
*/
Jugada* crearJugada(int pos, Registro jugador, char* instruc);


/*
Inserta una jugada al final de la lista enlazada de jugadas.
Entrada: Lista enlazada, datos de la nueva jugada a insertar (posición, jugador e instrucción con que juega).
Salida: Lista enlazada con la jugada insertada.
*/
Jugada* insertarJugada(Jugada* lista, int pos, Registro jugador, char* instruc);


/*
Muestra por pantalla el total de la lista enlazada.
Entrada: Lista enlazada.
Salida: Void.
*/
void mostrarLista(Jugada* lista);


/*
Lee la entrada, obtiene a los jugadores, y guarda las jugadas validas en una lista enlazada, 
además va contando cuantas veces se ocupan las etapas de pipeline.
Entrada: Nombre archivo, arreglo de registros, lista enlazada.
Salida: Lista enlazada con las jugadas validas encontradas.
*/
Jugada* leerEntrada(char* nombre, Registro* registros, Jugada* lista);


/*
Inicia el tablero con 0 en todas las posiciones, y con nombre "".
Entrada: Nada.
Salida: Void.
*/
void iniciarTablero();


/*
Ve si el tablero se encuentra completo o incompleto.
Entrada: Nada.
Salida: 1 (completo) o -1 (incompleto).
*/
int comprobarTablero();


/*
Verifica si algún jugador ganó.
Entrada: Nada.
Salida: Jugador ganador.
*/
Registro obtenerResultado();


/*
Guarda en el archivo de salida 1 el tablero, con las jugadas hechas.
Entrada: Archivo salida.
Salida: Void.
*/
void mostrarTablero(FILE* archivo);


/*
Recorre la lista enlazada con jugadas, una por una, modificando el tablero y buscando a algún ganador 
en cada turno.
Entrada: Lista enlazada con jugadas, archivo de salida 1.
Salida: Void.
*/
void realizarJugadas(Jugada* lista, char* salida1);


/*
Imprime en el archivo de salida 2 cuántas veces se ocupo cada etapa del pipeline.
Entrada: Archivo de salida 2.
Salida: Void.
*/
void mostrarEtapas(FILE* archivo);

