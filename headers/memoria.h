#ifndef MEMORY_H
#define MEMORY_H
#include "mips_instance.h"
void ler_mem(mips_instance* state);
int binario_para_decimal(char binario[], int inicio, int fim, int complemento2);
void decod(data* a);
int gen_asm(mips_instance* state, const char* name);
#endif
