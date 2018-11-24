#include "cabecera1_orga.h"


/*VARIABLES GLOBALES*/
Registro Jugador1;
Registro Jugador2;
Registro Tablero[9];
int IF;
int ID;
int EXE;
int MEM;
int WB;


void inciarEtapas()
{
	IF = 0;
	ID = 0;
	EXE = 0;
	MEM = 0;
	WB = 0;
}


void quitarSaltoLinea(char *frase)
{
  char *ptr;
  ptr = strchr (frase, '\n');
  if (ptr)
    *ptr = '\0';
}


void iniciarRegistros(Registro* registros)
{
	int i=0;

	for (i = 0; i < TOTAL_REGISTRO; ++i)
	{
		registros[i].valor= 0;
	}

	strcpy(registros[0].nombre, "$zero");
	strcpy(registros[1].nombre, "$at");
	strcpy(registros[2].nombre, "$v0");
	strcpy(registros[3].nombre, "$v1");
	strcpy(registros[4].nombre, "$a0");
	strcpy(registros[5].nombre, "$a1");
	strcpy(registros[6].nombre, "$a2");
	strcpy(registros[7].nombre, "$a3");
	strcpy(registros[8].nombre, "$t0");
	strcpy(registros[9].nombre, "$t1");
	strcpy(registros[10].nombre, "$t2");
	strcpy(registros[11].nombre, "$t3");
	strcpy(registros[12].nombre, "$t4");
	strcpy(registros[13].nombre, "$t5");
	strcpy(registros[14].nombre, "$t6");
	strcpy(registros[15].nombre, "$t7");
	strcpy(registros[16].nombre, "$s0");
	strcpy(registros[17].nombre, "$s1");
	strcpy(registros[18].nombre, "$s2");
	strcpy(registros[19].nombre, "$s3");
	strcpy(registros[20].nombre, "$s4");
	strcpy(registros[21].nombre, "$s5");
	strcpy(registros[22].nombre, "$s6");
	strcpy(registros[23].nombre, "$s7");
	strcpy(registros[24].nombre, "$t8");
	strcpy(registros[25].nombre, "$t9");
	strcpy(registros[26].nombre, "$k0");
	strcpy(registros[27].nombre, "$k1");
	strcpy(registros[28].nombre, "$gp");
	strcpy(registros[29].nombre, "$sp");
	strcpy(registros[30].nombre, "$fp");
	strcpy(registros[31].nombre, "$ra");
}


int buscarRegistro(char* reg, Registro* registros)
{
	int i=0;

	if (reg != NULL){
		for (i = 0; i < TOTAL_REGISTRO; ++i)
		{
			if(strcmp(reg, registros[i].nombre) == 0){
				return i;
			}
		}
		printf("Registro no encontrado.\n");
		return -1;
	}
	else{
		printf("Registro NULL.\n");
		return -1;
	}
}


int validarSw(char* rt, Registro* registros)
{
	int caracteres=0, i=0;
	char num[TAM_PALABRA];
	char regReal[TAM_PALABRA];
	char letra[TAM_PALABRA];
	strcpy(num, "");
	strcpy(regReal, "");
	strcpy(letra, "");

	while (rt[i] != '(')
	{
		sprintf(letra,  "%c", rt[i]);
		strcat(num, letra);
		caracteres++;
		i++;
	}

	caracteres++;
	while (rt[caracteres] != ')')
	{
		sprintf(letra,  "%c", rt[caracteres]);
		strcat(regReal, letra);
		caracteres++;
	}

	if (strcmp(regReal, "$sp") == 0)
	{
		return atoi(num);
	}
	else
	{
		return -1;
	}	
}


 /*TDA lista jugadas*/
Jugada* crearJugada(int pos, Registro jugador, char* instruc)
{
	Jugada* nodito = (Jugada*)malloc(sizeof(Jugada));
	if (nodito != NULL)
	{
		nodito->jugador = jugador;
		nodito->posicion = pos;
		if (strcmp(instruc, "addi") == 0 || strcmp(instruc, "sw") == 0)		
			nodito->instruccion = 0;	//agrego jugada
		else if (strcmp(instruc, "subi") == 0)
			nodito->instruccion = 1;	//quito jugada
		else
			nodito->instruccion = -1;	//error.
		nodito->sgte = NULL;
	}
	return nodito;
}


Jugada* insertarJugada(Jugada* lista, int pos, Registro jugador, char* instruc)
{
	Jugada* aux;
	aux = lista;
	Jugada* nueva = crearJugada(pos, jugador, instruc);

	if (lista != NULL)
	{
		while (aux->sgte != NULL)
		{
			aux = aux->sgte;
		}
		aux->sgte = nueva;
	}
	else
	{
		return nueva;
	}
	return lista;
}


void mostrarLista(Jugada* lista)
{
	Jugada* indice = lista;
	printf("LISTA ENLAZADA:\n");
	while (indice != NULL){
		printf("Jugador:%s %d, pos:%d, ins:%d\n", indice->jugador.nombre, indice->jugador.valor, indice->posicion, indice->instruccion);
		indice = indice->sgte;
	}
	printf("\nFIN LISTA ENLAZADA.\n\n");
}

/*FIN TDA*/


Jugada* leerEntrada(char* nombre, Registro* registros, Jugada* lista)
{
	FILE* archivo = NULL;
	archivo = fopen(nombre, "rb");

	//asumiendo instruc rd rs rt
	char instruc[TAM_PALABRA];
	char rd[TAM_REGISTRO];
	char rs[TAM_REGISTRO];
    char rt[TAM_REGISTRO];

    if (NULL!= archivo)
    {
    	//Jugador 1
    	fscanf(archivo, "%s", instruc);//obtengo una instruccion.
    	fscanf(archivo, "%s", rd);
    	rd[strlen(rd)-1]= '\0';	//quitar coma.
    	fscanf(archivo, "%s", rs);
    	rs[strlen(rs)-1]= '\0';	//quitar coma.
    	fscanf(archivo, "%s", rt);
    	if (strcmp("addi", instruc) == 0)
    	{
    		int i;
    		i = buscarRegistro(rs, registros);
    		if (i != -1)
    		{
    			strcpy(Jugador1.nombre, rd);
    			Jugador1.valor = registros[i].valor + atoi(rt);
    		}
    		IF++;
    		ID++;
    		EXE++;
    		WB++;
    	}

    	//Jugador 2
    	fscanf(archivo, "%s", instruc);//obtengo una instruccion.
    	fscanf(archivo, "%s", rd);
    	rd[strlen(rd)-1]= '\0';	//quitar coma.
    	fscanf(archivo, "%s", rs);
    	rs[strlen(rs)-1]= '\0';	//quitar coma.
    	fscanf(archivo, "%s", rt);
    	if (strcmp("addi", instruc) == 0)
    	{
    		int i;
    		i = buscarRegistro(rs, registros);
    		if (i != -1)
    		{
    			strcpy(Jugador2.nombre, rd);
    			Jugador2.valor = registros[i].valor + atoi(rt);
    		}
    		IF++;
    		ID++;
    		EXE++;
    		WB++;
    	}

    	while (feof(archivo)==0)
    	{
    		strcpy(instruc, "");
			fscanf(archivo, "%s", instruc);//obtengo una instruccion.

    		if (strcmp(instruc, "sw") == 0)
    		{
    			int pos;
    			fscanf(archivo, "%s", rd);	//Jugador.
		    	rd[strlen(rd)-1]= '\0';	//quitar coma.
		    	fscanf(archivo, "%s", rt);	//pos y $sp.
		    	pos = validarSw(rt, registros);
		    	if (pos != -1)
		    	{	
		    		if (strcmp(rd, Jugador1.nombre) == 0)
		    		{
			    		lista = insertarJugada(lista, pos/4, Jugador1, instruc);	
		    		}
		    		else if (strcmp(rd, Jugador2.nombre) == 0)
		    		{
			    		lista = insertarJugada(lista, pos/4, Jugador2, instruc);	
		    		}
		    	}
		    	IF++;
		    	ID++;
		    	EXE++;
		    	MEM++;
    		}
    		else if (strcmp(instruc, "addi") == 0 || strcmp(instruc, "subi") == 0)
    		{
		    	fscanf(archivo, "%s", rd);	//Jugador.
		    	rd[strlen(rd)-1]= '\0';	//quitar coma.
		    	fscanf(archivo, "%s", rs);
		    	rs[strlen(rs)-1]= '\0';	//quitar coma.
		    	fscanf(archivo, "%s", rt);
		    	if (strcmp(rd, Jugador1.nombre) == 0)
	    		{
			    	lista = insertarJugada(lista, atoi(rt)-1, Jugador1, instruc);
	    		}
	    		else if (strcmp(rd, Jugador2.nombre) == 0)
	    		{
			    	lista = insertarJugada(lista, atoi(rt)-1, Jugador2, instruc);
	    		}
	    		IF++;
	    		ID++;
	    		EXE++;
	    		WB++;
    		}
			else if (strcmp(instruc, "add") == 0 || strcmp(instruc, "sub") == 0 
				|| strcmp(instruc, "mul") == 0 || strcmp(instruc, "div") == 0)
			{
				fscanf(archivo, "%s", rd);
				fscanf(archivo, "%s", rs);
				fscanf(archivo, "%s", rt);
				IF++;
	    		ID++;
	    		EXE++;
	    		WB++;
			}
			else if (strcmp(instruc, "lw") == 0)
			{
				fscanf(archivo, "%s", rd);
				fscanf(archivo, "%s", rt);
				IF++;
	    		ID++;
	    		EXE++;
	    		MEM++;
	    		WB++;
			}
		}
    }
	else
		printf("No se encontro archivo.\n");
	fclose(archivo);
	return lista;
}


void iniciarTablero()
{
	int i;
	for (i = 0; i < 9; ++i)
	{
		strcpy(Tablero[i].nombre, "");
		Tablero->valor = 0;
	}
}


int comprobarTablero()
{
	int i;
	for (i = 0; i < 9; ++i)
	{
		if (strcmp(Tablero[i].nombre, "") == 0 && Tablero[i].valor == 0)
			return INCOMPLETO; 
	}
	return COMPLETO;
}

Registro obtenerResultado()
{
	if (Tablero[0].valor == Jugador1.valor && Tablero[1].valor == Jugador1.valor && Tablero[2].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[0].valor == Jugador2.valor && Tablero[1].valor == Jugador2.valor && Tablero[2].valor == Jugador2.valor)
		return Jugador2;
	else if (Tablero[0].valor == Jugador1.valor && Tablero[3].valor == Jugador1.valor && Tablero[6].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[0].valor == Jugador2.valor && Tablero[3].valor == Jugador2.valor && Tablero[6].valor == Jugador2.valor)
		return Jugador2;
	else if (Tablero[1].valor == Jugador1.valor && Tablero[4].valor == Jugador1.valor && Tablero[7].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[1].valor == Jugador2.valor && Tablero[4].valor == Jugador2.valor && Tablero[7].valor == Jugador2.valor)
		return Jugador2;
	else if (Tablero[2].valor == Jugador1.valor && Tablero[5].valor == Jugador1.valor && Tablero[8].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[2].valor == Jugador2.valor && Tablero[5].valor == Jugador2.valor && Tablero[8].valor == Jugador2.valor)
		return Jugador2;
	else if (Tablero[3].valor == Jugador1.valor && Tablero[4].valor == Jugador1.valor && Tablero[5].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[3].valor == Jugador2.valor && Tablero[4].valor == Jugador2.valor && Tablero[5].valor == Jugador2.valor)
		return Jugador2;
	else if (Tablero[6].valor == Jugador1.valor && Tablero[7].valor == Jugador1.valor && Tablero[8].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[6].valor == Jugador2.valor && Tablero[7].valor == Jugador2.valor && Tablero[8].valor == Jugador2.valor)
		return Jugador2;
	else if (Tablero[0].valor == Jugador1.valor && Tablero[4].valor == Jugador1.valor && Tablero[8].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[0].valor == Jugador2.valor && Tablero[4].valor == Jugador2.valor && Tablero[8].valor == Jugador2.valor)
		return Jugador2;
	else if (Tablero[2].valor == Jugador1.valor && Tablero[4].valor == Jugador1.valor && Tablero[6].valor == Jugador1.valor)
		return Jugador1;
	else if (Tablero[2].valor == Jugador2.valor && Tablero[4].valor == Jugador2.valor && Tablero[6].valor == Jugador2.valor)
		return Jugador2;
	else
	{
		Registro empate;
		strcpy(empate.nombre, "empate");
		empate.valor = 0;
		return empate;
	}
}


void mostrarTablero(FILE* archivo)
{
	int i;
	for (i = 0; i < 9; ++i)
	{
		if (Tablero[i].valor == Jugador1.valor)
			fprintf(archivo, "%c ", 'X');
		else if (Tablero[i].valor == Jugador2.valor)
			fprintf(archivo, "%c ", 'O');
		else
			fprintf(archivo, "- ");
		if((i+1)%3 == 0)	
			fprintf(archivo, "\n");
		
	}
}

void realizarJugadas(Jugada* lista, char* salida1)
{
	int respuesta = INCOMPLETO;
	int pos;
	int ganador = 0;
	Registro resultado;
	Jugada* aux = lista;
	FILE* archivo = NULL;
	archivo = fopen(salida1, "w");

	if (lista == NULL)
	{
		mostrarTablero(archivo);
		printf("Tablero incompleto.\n");
	}
	while (aux != NULL)
	{
		respuesta = comprobarTablero();
		if (respuesta == INCOMPLETO)
		{
			if (ganador == 0)
			{
				resultado = obtenerResultado();
				if (strcmp(resultado.nombre, "empate") != 0)	//Existe algún ganador.
				{
					mostrarTablero(archivo);
					if (strcmp(resultado.nombre, Jugador1.nombre) == 0)
						fprintf(archivo, "El ganador del juego es el jugador %s (X)\n", Jugador1.nombre);
					else
						fprintf(archivo, "El ganador del juego es el jugador %s (O)\n", Jugador2.nombre);
					ganador = 1;
				}
				
			}
			pos = aux->posicion;
			if (strcmp(Tablero[pos].nombre, "") == 0)
			{
				Tablero[pos] = aux->jugador; 
			}
			else if (Tablero[pos].valor == aux->jugador.valor && aux->instruccion == 1)
			{
				strcpy(Tablero[pos].nombre, "");
				Tablero[pos].valor = 0;
			}
		}
		else	// tablero esta completo.
		{
			if (ganador == 0)
			{
				resultado = obtenerResultado();
				if (strcmp(resultado.nombre, "empate") != 0)	//Existe algún ganador.
				{
					mostrarTablero(archivo);
					if (strcmp(resultado.nombre, Jugador1.nombre) == 0)
						fprintf(archivo, "El ganador del juego es el jugador %s (X)\n", Jugador1.nombre);
					else
						fprintf(archivo, "El ganador del juego es el jugador %s (O)\n", Jugador2.nombre);
				ganador = 1;
				}
				
			}
		}
		aux = aux->sgte;
	}
	fprintf(archivo, "Gato final:\n");
	mostrarTablero(archivo);
	respuesta = comprobarTablero();
	if (respuesta == COMPLETO)
	{
		if (ganador == 0)
		{
			if (strcmp(resultado.nombre, "empate") == 0)
			{
				fprintf(archivo, "El resultado del juego es empate\n");
			}
		}	
	}
	else if (respuesta == INCOMPLETO && ganador == 0)
	{
		resultado = obtenerResultado();
		if (strcmp(resultado.nombre, "empate") == 0)	//No existe algún ganador.
		{
			fprintf(archivo, "Tablero incompleto.\n");
		}
	}
	else if (ganador == 0)
	{
		resultado = obtenerResultado();
		if (strcmp(resultado.nombre, "empate") != 0)	//Existe algún ganador.
		{
			if (strcmp(resultado.nombre, Jugador1.nombre) == 0)
				fprintf(archivo, "El ganador del juego es el jugador %s (X)\n", Jugador1.nombre);
			else
				fprintf(archivo, "El ganador del juego es el jugador %s (O)\n", Jugador2.nombre);
		ganador = 1;
		}
	}	
	
	fclose(archivo);
}


void mostrarEtapas(FILE* archivo)
{
	fprintf(archivo, "IF: %d\nID: %d\nEXE: %d\nMEM: %d\nWB: %d\n", IF, IF, EXE, MEM, WB);
}


int main(int argc, char const *argv[])
{
	printf("\n.......................................\n");
    printf(".                                     .\n");
    printf(".            Laboratorio 2            .\n");
    printf(".              TicTacToe              .\n");
    printf(".......................................\n");
    printf(".     Organización de Computadores    .\n");
    printf(".                                     .\n");
    printf(".       Patricia Melo Fuenzalida      .\n");
    printf(".......................................\n");

	Registro registros[TOTAL_REGISTRO];
	iniciarRegistros(registros);
	iniciarTablero();
	inciarEtapas();
	Jugada* lista = NULL;
	char entrada[TAM_PALABRA];
	char salida[TAM_PALABRA];
	char salida2[TAM_PALABRA];
	FILE* archivo = NULL;

	printf("Ingrese nombre del archivo de entrada (ejemplo: Jugadas1.txt):\n");
	fgets(entrada, TAM_PALABRA, stdin);
	quitarSaltoLinea(entrada);
	printf("Ingrese nombre del archivo de salida para guardar el resultado:\n");
	fgets(salida, TAM_PALABRA, stdin);
	quitarSaltoLinea(salida);
	printf("Ingrese nombre del archivo de salida para guardar las etapas del pipeline:\n");
	fgets(salida2, TAM_PALABRA, stdin);
	quitarSaltoLinea(salida2);

	lista = leerEntrada(entrada, registros, lista);
	realizarJugadas(lista, salida);

	archivo = fopen(salida2, "w");
	mostrarEtapas(archivo);
	fclose(archivo);

	printf("\nFin del programa.\n");
	return 0;
}