#include "bufftofile.h"
#include <stdio.h> 
#include <stdlib.h> 

int bufftofile(char *buffer, long size){

	//creamos el archivo
	FILE *f_dst = fopen("OUT", "wb");
	if(f_dst == NULL){
		printf("ERROR - No se pudo crear el archivo\n");
		return 1;
	}

	//escribimos en el archivo
	if(fwrite(buffer, 1, size, f_dst) != size){
		printf("ERROR - No se pudo crear el archivo\n");
		return 2;
	}

	//cerramos el archivo
	fclose(f_dst);
	f_dst = NULL;
	return 0;
}
