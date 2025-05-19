#ifndef MEMORY_H
#define MEMORY_H
#include "mips_instance.h"
int ler_mem(mips_instance* state, const char* name);
int binario_para_decimal(char binario[], int inicio, int fim, int complemento2);
void decod(data* a);
int gen_asm(mips_instance* state, const char* name);
#endif
