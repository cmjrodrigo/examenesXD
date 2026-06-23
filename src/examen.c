#include "examen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************
	     Ejercicios
***********************************/
Ejercicio *newEjercicio(string p, string r[kDefaultRespuestasPorPregunta])
{
	Ejercicio *ej = (Ejercicio *) calloc(1, sizeof(Ejercicio));
	ej->Pregunta = strdup(p);
	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
		ej->Respuesta[i] = strdup(r[i]);
	return ej;
}

void delEjercicio(generic ej)
{
	free(((Ejercicio *)ej)->Pregunta);
	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
		free(((Ejercicio *) ej)->Respuesta[i]);
	free(ej);
}

void printEjercicio(generic ej)
{
	printf("PREGUNTA:\n"
		"\t%s\n", ((Ejercicio *)ej)->Pregunta);

	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
		printf("\t%c:"
			"\t%s\n", 'A' + i, ((Ejercicio *)ej)->Respuesta[i]);
}

int ejercicioIgual(generic e1, generic e2)
{
	bool c1 = !strcmp(((Ejercicio *)e1)->Pregunta, ((Ejercicio *) e2)->Pregunta);
	bool c2 = true;
	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++){
		if(strcmp(((Ejercicio *)e1)->Respuesta[i], ((Ejercicio *)e2)->Respuesta[i])){
			c2 = false;
		}
	}
	return c1 && c2;
}

/***********************************
	     Examen
***********************************/

Examen *newExamen(string tit, string arch)
{
	Examen *ex = (Examen *) calloc(1, sizeof(Examen));

	ex->Puntos = kDefaultPuntosTotales;
	ex->Aciertos = kDefaultMinimoDeAciertos;
	ex->Calificacion = 0.0f;
	ex->Titulo = strdup(tit);
	ex->Alumno = nullptr;
	ex->Archivo = arch;
	ex->Reactivos = nullptr;
	return ex;
}

void delExamen(Examen *ex)
{
	free(ex->Titulo);
	free(ex->Alumno);
	free(ex->Archivo);
	dNodeList(ex->Reactivos, delEjercicio);
}

Examen *exCargar(string arch)
{
}


/***********************************
	     General
***********************************/
void generarExamen()
{
	printf( "-----------------------------------------------\n"
		"                GENERAR EXAMEN\n"
		"-----------------------------------------------\n"
		"Parece que de momento no hay nada aqui :O\n\n\n"
		"(ingrese cualquier caracter para regresar)...\n");

	char ch = ' ';
	scanf("%c", &ch);
	return;
}

void modificarExamen()
{
	printf( "-----------------------------------------------\n"
		"               MODIFICAR EXAMEN\n"
		"-----------------------------------------------\n"
		"Parece que de momento no hay nada aqui :O\n\n\n"
		"(ingrese cualquier caracter para regresar)...\n");

	char ch = ' ';
	scanf("%c", &ch);
	return;
}

void aplicarExamen()
{
	printf( "-----------------------------------------------\n"
		"               APLICAR EXAMEN\n"
		"-----------------------------------------------\n"
		"Parece que de momento no hay nada aqui :O\n\n\n"
		"(ingrese cualquier caracter para regresar)...\n");

	char ch = ' ';
	scanf("%c", &ch);
	return;
}
