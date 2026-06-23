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
} Ejercicio;

Ejercicio *newEjercicio(string p, string r[kDefaultRespuestasPorPregunta]);
void delEjercicio(void *ej);

void printEjercicio(generic ej);

int ejercicioIgual(generic e1, generic e2);



/***********************************
	     Examen
***********************************/
constexpr int kDefaultPuntosTotales = 10;
constexpr int kDefaultMinimoDeReactivos= 1;
typedef struct Examen{
	int Puntos;
	int Aciertos;
	int NumeroReactivos;
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

void printExamen(Examen *ex);

/***********************************
	     General
***********************************/
void generarExamen();
void modificarExamen();
void aplicarExamen();

#endif
