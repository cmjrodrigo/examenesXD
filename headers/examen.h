#ifndef EXAM_H
#define EXAM_H
#include "linked_list.h"

typedef char * string;

constexpr int RespuestasPorPregunta = 4;

typedef struct Ejercicio{
	string Pregunta;
	string Respuesta;
} Ejercicio;

constexpr int DefaultPuntosTotales =10;

typedef struct Examen{
	int Puntos;
	int Aciertos;
	int Calificacion;
	string Titulo;
	string Alumno;
	string Archivo;
	Node Reactivos;
} Examen;

void generarExamen();
void modificarExamen();
void aplicarExamen();

#endif
