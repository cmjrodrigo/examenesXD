#include <iostream>
#include "examen.h"

int main()
{
	bool shouldExit {false};
	while(!shouldExit){
		std::cout
			<< "-----------------------------------------------\n"
			<< "               MENÚ PRINCIPAL\n"
			<< "-----------------------------------------------\n"
			<< "Escoja por favor la función que desee realizar:\n"
			<< "	1) Generar examen\n"
			<< "	2) Modificar examen\n"
			<< "	3) Aplicar examen\n"
			<< "	...) Salir\n\n";

		int opcion {0};
		std::cin >> opcion;
		if(opcion == 1){
			generarExamen();
		} else if(opcion == 2){
			modificarExamen();
		} else if(opcion == 3){
			aplicarExamen();
		} else{
			shouldExit = true;
		}
	}

	return 0;
}
