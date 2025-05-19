#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "memoria.h"
#include "mips_instance.h"
#include "nameing.h"
#include "control_unit.h"


int ler_mem(mips_instance* state, const char* name){

    FILE *arq = fopen(name, "r");

    if (arq == NULL) return 2;

    int flag = 0; // Para marcar quando encontramos ".data"
    int i = 0;

    // Leitura das instruções até encontrar o .data ou até i alcançar 128
    char temp[20];
    while (flag == 0 && i < 128) {
        if (fgets(temp, 19, arq) == NULL) break;  // Verifica fim do arquivo
        temp[strcspn(temp, "\n")] = '\0';  // Remover \n se presente
        if (strcmp(temp, ".data") == 0) {
            flag = 1;  // Encontramos ".data", agora vamos ler os dados
            continue;  // Ignora a linha ".data"
        }

        if (flag == 0) {
            state->mem[i].inst = binario_para_decimal(temp, 0, 15, 0);  // Lê instrução binária
            i++;
        }
    }

    // Leitura de dados a partir do índice 128 até o limite de 255
    i = 128; // Agora começamos a ler dados na posição 128
    while (i < 256 && fgets(temp, 19, arq) != NULL) {  // Enquanto não atingir o fim do arquivo
        temp[strcspn(temp, "\n")] = '\0';  // Remover \n se presente
        // Leitura dos dados após ".data"
        state->mem[i].data[0] = binario_para_decimal(temp, 0, 7, 1); // Leitura de 16 bits
        i++;
    }

    fclose(arq);
	return 0;
}





int binario_para_decimal(char binario[], int inicio, int fim, int complemento2) {
    int decimal = 0;
    int tamanho = strlen(binario);

    if (inicio < 0 || fim >= tamanho || inicio > fim) {
        printf("Índices inválidos.\n");
        return -1;
    }

    if (complemento2 == 1) {

        if (binario[inicio] == '1') {
            int inversao = 0;
            for (int i = inicio; i <= fim; i++) {
                if (binario[i] == '0') {
                    inversao += 1<<(fim - i);
                }
            }

            decimal = inversao + 1;
            decimal = -decimal;
        } else {
            for (int i = inicio; i <= fim; i++) {
                if (binario[i] == '1') {
                    decimal += 1<<(fim - i);
                }
            }
        }
    } else {
        for (int i = inicio; i <= fim; i++) {
            if (binario[i] == '1') {
                decimal += 1<<(fim - i);
            }
        }
    }

    return decimal;
};

int gen_asm(mips_instance* mips, const char* name){

    FILE *arq = fopen(name,"w");
	if(arq==NULL) return 2;

	for(int i=0; i<128;i++){
		unsigned int mi = 1;
		unsigned int inst = mips->mem[i].inst;
		update_microinstruction(inst>>12,&mi);
		char tmp[5];
		instruction_name_finder(inst>>12,inst&7,tmp);

		if(inst == 0){
			fclose(arq);
			return 0;
		}

		switch(mi){
			case 7:
				fprintf(arq,"%s $%u, $%u, $%u\n", tmp, (inst>>3)&7, (inst>>9)&7, (inst>>6)&7);
			break;
			case 9:
				goto immediat;
			break;
			case 10:
				fprintf(arq,"%s %u\n", tmp, inst&255);
			break;
			default:
				update_microinstruction(inst>>12,&mi);
				switch(mi){
					case 6:
					immediat:
						fprintf(arq,"%s $%u, $%u, %u\n", tmp, (inst>>6)&7, (inst>>9)&7, inst&63);
					break;
					default:
						fprintf(arq,"%s $%u, $%u(%u)\n", tmp, (inst>>6)&7, (inst>>9)&7, inst&63);
					break;
				}
			break;
		}
	}
	fclose(arq);
	return 0;
}

