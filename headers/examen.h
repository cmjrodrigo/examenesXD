#pragma once
#include <string>
#include "linked_list.h"


constexpr int RespuestasPorPregunta {4};

struct Ejercicio{
	std::string Pregunta{};
	std::string Respuesta[RespuestasPorPregunta]{"NA"};
};

constexpr int DefaultPuntosTotales {10};
struct Examen{
	int Puntos{DefaultPuntosTotales};
	int Aciertos{0};
	int Calificacion{0};
	std::string Titulo{};
	std::string Alumno{};
	std::string Archivo{};
	Node<Ejercicio> Reactivos;
};

void generarExamen();
void modificarExamen();
void aplicarExamen();
