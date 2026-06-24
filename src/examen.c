#include "examen.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/***********************************
	     Ejercicios
***********************************/
Ejercicio *newEjercicio(string p, string r[kDefaultRespuestasPorPregunta], int c)
{
	Ejercicio *ej = (Ejercicio *) calloc(1, sizeof(Ejercicio));
	ej->Pregunta = strdup(p);
	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
		ej->Respuesta[i] = strdup(r[i]);
	ej->Correcta = c;
	ej->Ingresada = 0;
	return ej;
}

void delEjercicio(generic ej)
{
	Ejercicio *curr = (Ejercicio *)ej;
	free(curr->Pregunta);
	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
		free(curr->Respuesta[i]);
	free(curr);
}

void printEjercicio(generic ej, int opt)
{
	Ejercicio *curr = (Ejercicio *)ej;
	printf(". %s\n", curr->Pregunta);

	if(opt == OPT_PROFESOR){
		printf("(Respuesta correcta: %s)\n", curr->Respuesta[curr->Correcta - 1]);
		printf("(Respuesta ingresada: %s)\n", ((curr->Ingresada - 1) < 0) ? 
				"Sin responder" : curr->Respuesta[curr->Ingresada - 1]);
	}

	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++)
		printf("\t%c:\t%s\n", 'A' + i, curr->Respuesta[i]);
	printf("\n");
}

int ejercicioIgual(generic e1, generic e2)
{
	Ejercicio *curr1 = (Ejercicio *)e1;
	Ejercicio *curr2 = (Ejercicio *)e2;
	bool c1 = !strcmp(curr1->Pregunta, curr2->Pregunta);
	bool c2 = true;
	for(int i = 0; i < kDefaultRespuestasPorPregunta; i++){
		if(strcmp(curr1->Respuesta[i], curr2->Respuesta[i])){
			c2 = false;
		}
	}
	return c1 && c2 && (curr1->Respuesta == curr2->Respuesta);
}

/***********************************
	     Examen
***********************************/

Examen *newExamen(string arch)
{
	Examen *ex = (Examen *) calloc(1, sizeof(Examen));

	ex->Puntos = 0;
	ex->Aciertos = 0;
	ex->Calificacion = 0.0f;
	ex->Titulo = nullptr;
	ex->Alumno = nullptr;
	ex->Archivo = strdup(arch);
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

	int res = 0;
	int ing = 0;
	while(fscanf(f, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n",
			buff[0], buff[1], buff[2], buff[3], buff[4], &res, &ing) != EOF)
	{
		if(ex->Reactivos == nullptr){
		//Crea nuevo nodo raíz a base de un nuevo ejercicio 
		//que se inicializa con los buffers del texto del documento
			ex->Reactivos = newNode(
					(generic)newEjercicio(buff[0], (string[]){
						buff[1], buff[2],
						buff[3], buff[4]}, res),
					nullptr, nullptr);
		} else{
		//Empuja un nuevo nodo en la lista de reactivos basado
		//en un ejercicio inicializado de acuerdo a los buffers
		//de texto del documento
			push_front(ex->Reactivos, newNode(
				(generic)newEjercicio(buff[0], (string[]){
					buff[1], buff[2],
					buff[3], buff[4]}, res),
				nullptr, nullptr));
		}
		((Ejercicio *)front(ex->Reactivos)->data)->Ingresada = ing;
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
		fprintf(f, "%d\n%d\n", ((Ejercicio *)curr->data)->Correcta,
				((Ejercicio *)curr->data)->Ingresada);
		curr = curr->head;
	}
	fclose(f);
	return 1;
}

void printExamen(Examen *ex, int opt)
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
		printLinkedList(ex->Reactivos, printEjercicio, opt);
}



void examenCalificar(Examen *ex)
{
	Node *curr = back(ex->Reactivos);
	for(int i = 0; i < ex->Puntos; i++)
	{
		if(((Ejercicio *)curr->data)->Correcta == ((Ejercicio *)curr->data)->Ingresada)
			ex->Aciertos++;
		curr = curr->head;
	}
	ex->Calificacion = (ex->Aciertos == 0) ? (0.0f) : (((float)ex->Aciertos / (float)ex->Puntos) * 10.0f);
}
/***********************************
	     General
***********************************/
void generarExamen()
{
	printf( "-----------------------------------------------\n"
		"                GENERAR EXAMEN\n"
		"-----------------------------------------------\n"
		"Sea usted bienvenido a la sección para generar\n"
		"nuevos examenes :)\n\n"
		"Para poder empezar a generar su examen, por favor\n"
		"ingrese la dirección del archivo en el cual desea\n"
		"que se guarde su examen.\n");

	char buff[5][512] = {0};
	scanf(" %[^\n]", buff[0]);

	Examen *ex = newExamen(buff[0]);
	memset(buff, 0, sizeof(buff));

	printf("!Perfecto! su examen se guardará en:\n\t%s\n", ex->Archivo);

	printf("Ahora por favor ingrese el nombre de su examen:\n");
	scanf(" %[^\n]", buff[0]);
	ex->Titulo = strdup(buff[0]);
	memset(buff, 0, sizeof(buff));

	printf("Ingrese ahora el número de reactivos totales en el\n"
		"examen: ");
	int puntos = 0;
	while(puntos <= 0){
		scanf("%d", &puntos);
		if(puntos < 0)
			printf("Por favor ingrese un valor válido de puntos (mayor a 0): ");
	}
	ex->Puntos = puntos;

	for(int i = 0; i < ex->Puntos; i++){
		printf("Ingrese la pregunta %d:\n", i + 1);
		scanf(" %[^\n]", buff[0]);

		for(int j = 0; j < kDefaultRespuestasPorPregunta; j++){
			printf("\tIngrese posible respuesta %c:\n\t", 'A' + j);
			scanf(" %[^\n]", buff[j + 1]);
		}

		printf("\tDe las respuestas ingresadas, ingrese NUMÉRICAMENTE\n"
			"\tcuál fue la correcta: ");
		int corr = 0;
		scanf("%d", &corr);

		if(ex->Reactivos == nullptr){
			ex->Reactivos = newNode((generic) newEjercicio(
						buff[0], (string []){
							buff[1], buff[2],
							buff[3], buff[4]
						}, corr),
					nullptr, nullptr);
		} else{
			push_front(ex->Reactivos, newNode((generic) newEjercicio(
						buff[0], (string []){
							buff[1], buff[2],
							buff[3], buff[4]
						}, corr),
					nullptr, nullptr));
		}

		memset(buff, 0, sizeof(buff));
	}

	examenGuardar(ex);
	printf("¡El proceso de crear su examen ha acabado!\n"
		"Su examen se guardó en %s\n\n"
		"(Presione cualquier tecla para continuar)\n", ex->Archivo);

	char ch = ' ';
	scanf(" %c", &ch);

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
