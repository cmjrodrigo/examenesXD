#include "examen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
	printf(
		". %s\n", ((Ejercicio *)ej)->Pregunta);

	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
		printf("\t%c:"
			"\t%s\n", 'A' + i, ((Ejercicio *)ej)->Respuesta[i]);
	printf("\n");
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

Examen *newExamen(string arch)
{
	Examen *ex = (Examen *) calloc(1, sizeof(Examen));

	ex->Puntos = kDefaultPuntosTotales;
	ex->Aciertos = 0;
	ex->NumeroReactivos = kDefaultMinimoDeReactivos;
	ex->Calificacion = 0.0f;
	ex->Titulo = nullptr;
	ex->Alumno = nullptr;
	ex->Archivo = arch;
	ex->Reactivos = nullptr;
	return ex;
}

void delExamen(Examen *ex)
{
	free(ex->Titulo);
	free(ex->Alumno);
	dNodeList(ex->Reactivos, delEjercicio);
}

Examen *examenCargar(string arch)
{
	Examen *ex = newExamen(arch);
	FILE *f = fopen(arch, "r");

	char buff[5][512] = {0};
	
	//Metadatos
	fscanf(f,
		"%d\n%d\n%f\n%[^\n]\n%[^\n]\n",
		&ex->Puntos, &ex->Aciertos, &ex->Calificacion,
		buff[0], buff[1]);
	ex->Titulo = strdup(buff[0]);
	ex->Alumno = strdup(buff[1]);
	memset(buff, 0, sizeof(buff));

	while(fscanf(f, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
			buff[0], buff[1], buff[2], buff[3], buff[4]) != EOF)
	{
		if(ex->Reactivos == nullptr){
		//Crea nuevo nodo raíz a base de un nuevo ejercicio 
		//que se inicializa con los buffers del texto del documento
			ex->Reactivos = newNode(
					(generic)newEjercicio(buff[0], (string[]){
						buff[1], buff[2],
						buff[3], buff[4]}),
					nullptr, nullptr);
		} else{
		//Empuja un nuevo nodo en la lista de reactivos basado
		//en un ejercicio inicializado de acuerdo a los buffers
		//de texto del documento
			push_front(ex->Reactivos, newNode(
				(generic)newEjercicio(buff[0], (string[]){
					buff[1], buff[2],
					buff[3], buff[4]}),
				nullptr, nullptr));
		}
		memset(buff, 0, sizeof(buff));
	}

	//Reactivos
	fclose(f);
	return ex;
}

int examenGuardar(Examen *ex)
{
	FILE *f = fopen(ex->Archivo, "w+");

	//Metadatos
	fprintf(f,
		"%d\n%d\n%f\n%s\n%s\n",
		ex->Puntos, ex->Aciertos, ex->Calificacion,
		ex->Titulo, ex->Alumno);

	//Reactivos
	Node *curr = back(ex->Reactivos);
	while(curr != nullptr){
		fprintf(f, "%s\n", ((Ejercicio *)curr->data)->Pregunta);
		for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
			fprintf(f, "%s\n", ((Ejercicio *)curr->data)->Respuesta[i]);
		curr = curr->head;
	}
	fclose(f);
	return 1;
}

void printExamen(Examen *ex)
{
	printf(
		"-------------------------------------------------\n"
		"%s\n"
		"-------------------------------------------------\n"
		"Alumno: %s\n"
		"Puntos: %d/%d         Calificacion: %.1f\n"
		"-------------------------------------------------\n"
		"PREGUNTAS:                                     \n\n",
		ex->Titulo,
		ex->Alumno,
		ex->Aciertos, ex->Puntos,    ex->Calificacion);

	if(ex->Reactivos != nullptr)
		printLinkedList(ex->Reactivos, printEjercicio);
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
