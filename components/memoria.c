#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "memoria.h"


void ler_mem(mips_instance* state, const char* name){
    FILE *arq;
    arq = fopen(name,"r");
    char temp[20];

    if(arq == NULL){
        printf("ERRO NA LEITURA DA MEMORIA DE INSTRUCOES\n");
        exit(2);
    };

    int flag=0;
	int i=0;

    while(flag==0 || i<128){ //leitura instrucoes
		fgets(temp,19,arq);
		if(strcmp(temp,".data")==0) flag=1;

		if(flag==0){
			state->mem[i].inst = binario_para_decimal(temp,0,15,0);
			i++;
		}
	}

	if(flag == 0 || i<256){ // se memoria de instrucoes maior que 128 ignorar proximas intrucoes e ler a partir de .data
		while(strcmp(temp,".data")!=0){
			fgets(temp,19,arq);
		}
	}

	i=128;
	while(i<256 || !feof(arq)){ //leitura dados
		fgets(temp,19,arq);
		state->mem[i].data[0] = binario_para_decimal(temp,0,7,1);
		i++;
	}


    fclose(arq);
};


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

/*
void asm_code(data* mem,const char *memo){
    char temp[30];
    control_signal *csignal;
	int cont=0;

	printf("Digite nome do arquivo .asm: ");
	scanf("%s",temp);

    FILE* arq = fopen(temp,"w");
	FILE* in = fopen(memo,"r");


    if(in == NULL){
        printf("ERRO NA LEITURA DA MEMORIA DE INSTRUCOES\n");
        exit(2);
    };


	while(!feof(in)){
		fgets(temp,20,in);
		cont++;
	}

        for(int i=0;i < cont; i++){
            decod(mem+i);
                    csignal = uc(mem[i].opcode,mem[i].funct);
                    fprintf(arq, "%s ", csignal->name);
                    if( !csignal->jump ){
                        if( !csignal->RegDst ) fprintf(arq, "$%u, $%u, %i\n", mem[i].rt, mem[i].rs, mem[i].imm);
                        else fprintf(arq,"$%u, $%u, $%u\n", mem[i].rd, mem[i].rs, mem[i].rt);
                    }
                    else fprintf(arq, "%u\n",mem[i].addr);
        }

		fclose(arq);
		fclose(in);
		free(csignal);
}
*/
