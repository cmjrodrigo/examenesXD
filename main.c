#include "examen.h"
#include <stdio.h>

int main()
{
	bool shouldExit = false;
	while(!shouldExit){
		printf( "-----------------------------------------------\n"
			"               MENÚ PRINCIPAL\n"
			"-----------------------------------------------\n"
			"Escoja por favor la función que desee realizar:\n"
			"	1) Generar examen\n"
			"	2) Modificar examen\n"
			"	3) Aplicar examen\n"
			"	4) Revisar examen\n"
			"	...) Salir\n\n");

		int opcion = 0;
		scanf("%d", &opcion);

		if(opcion == 1){
			generarExamen();
		} else if(opcion == 2){
			modificarExamen();
		} else if(opcion == 3){
			aplicarExamen();
		} else if(opcion == 4){
			revisarExamen();
		} else{
			shouldExit = true;
		}
	}

	return 0;
}
