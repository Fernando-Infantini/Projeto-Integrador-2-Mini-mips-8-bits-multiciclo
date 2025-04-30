#include <stdio.h>
#include <stdlib.h>
#include "dat_manager.h"

void read_dat(const char* name, int8_t* a){
	FILE* buffer = fopen(name,"r");
	if(!buffer) exit(2);
	for(int i=0;i<512;i++){
			fscanf(buffer,"%i",(int*)&a[i]);
	}
	fclose(buffer);
	return;
}

void write_dat(const char* name, int8_t* a){
	FILE *buffer = fopen(name,"w");
	if(!buffer) exit(2);
	for(int i=0;i<512;i++){
			fprintf(buffer,"%i",a[i]);
	}
	fprintf(buffer,"\n");
	fclose(buffer);
	return;
}
