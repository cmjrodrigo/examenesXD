#ifndef EXAM_H
#define EXAM_H
#include "linked_list.h"

//Types
typedef char * string;

/***********************************
	     Ejercicios
***********************************/
constexpr int kDefaultRespuestasPorPregunta = 4;
typedef struct Ejercicio{
	string Pregunta;
	string Respuesta[kDefaultRespuestasPorPregunta];
	int Correcta;
	int Ingresada;
} Ejercicio;

Ejercicio *newEjercicio(string p, string r[kDefaultRespuestasPorPregunta], int c);
void delEjercicio(void *ej);

constexpr int OPT_PROFESOR = 0;
constexpr int OPT_ALUMNO = 1;

void printEjercicio(generic ej, int opt);

int ejercicioIgual(generic e1, generic e2);



/***********************************
	     Examen
***********************************/
typedef struct Examen{
	int Puntos;
	int Aciertos;
	float Calificacion;
	string Titulo;
	string Alumno;
	string Archivo;
	Node *Reactivos;
} Examen;

Examen *newExamen(string arch);
void delExamen(Examen *ex);

Examen *examenCargar(string arch);
int examenGuardar(Examen *ex);

void printExamen(Examen *ex, int opt);

void examenCalificar(Examen *ex);

/***********************************
	     General
***********************************/
void generarExamen();
void modificarExamen();
void aplicarExamen();

#endif
