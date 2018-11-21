#include "cabecera1_orga.h"


/*VARIABLES GLOBALES*/
Registro Jugador1;
Registro Jugador2;



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
	printf("%s %d\n", jugador.nombre, jugador.valor );
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
    		//sumar IF ID EXE ...
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
    		//sumar IF ID EXE ...
    	}

    	while (feof(archivo)==0)
    	{
    		strcpy(instruc, "");
			fscanf(archivo, "%s", instruc);//obtengo una instruccion.
    		printf("instruc: %s\n", instruc);

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
			    		lista = insertarJugada(lista, pos, Jugador1, instruc);	
		    		}
		    		else if (strcmp(rd, Jugador2.nombre) == 0)
		    		{
			    		lista = insertarJugada(lista, pos, Jugador2, instruc);	
		    		}
		    	}
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
			    	lista = insertarJugada(lista, atoi(rt), Jugador1, instruc);
	    		}
	    		else if (strcmp(rd, Jugador2.nombre) == 0)
	    		{
			    	lista = insertarJugada(lista, atoi(rt), Jugador2, instruc);
	    		}
	    		else if (strcmp(rd, "$sp") == 0)
	    		{
	    			//genero tablero.
	    		}
    		}
			
	    	else
	    		printf("ERROR\n");

		}
    }
	else
		printf("No se encontro archivo.\n");
	fclose(archivo);
	return lista;
}

int main(int argc, char const *argv[])
{
	Registro registros[TOTAL_REGISTRO];
	iniciarRegistros(registros);
	Jugada* lista = NULL;

	lista = leerEntrada("Jugadas1.txt", registros, lista);
	mostrarLista(lista);

//	printf("Jugador1:%s %d\n", Jugador1.nombre, Jugador1.valor);
//	printf("Jugador2:%s %d\n", Jugador2.nombre, Jugador2.valor);

	printf("Fin programa.\n");
	return 0;
}