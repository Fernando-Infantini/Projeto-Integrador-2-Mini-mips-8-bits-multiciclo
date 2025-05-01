#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "minimipsmulti.h" //isso aqui não pode existir

#include "control_unit.h"
#include "dat_manager.h"
#include "stack.h"
#include "ula.h"

int main(int argc, char** argv){
/*
	char fileN[64];
    int8_t reg[8] = {0};
    data mem[256] = {0};
    int16_t A=0, B=0;
    uint8_t pc=0;
    control_signal* csignal;
    int8_t aluIn, result, aluOut;
	ula_signal* usignal;
	state* state_stack = NULL;
    ciclo* block;

    if(argc>1){
		strcpy(fileN,argv[1]);
		ler_mem(mem,fileN);
	}

	char temp[30];

	char casee=0;
	do{
		switch(casee){
			case '1':

				addState(pc, reg, mem, &state_stack);
                exec(mem[pc], &pc, reg, mem);

                printf("\n");
                for(int i=0;i<16;i++){
                    for(int j=0;j<16;j++){
                        printf("|%i",mem[16*i+j]);
                    }
                    printf("|\n");
                }
                printf("\n");

                for(int i=0;i<8;i++){
                    printf("|%i",reg[i]);
                }
                printf("|\n\n");

                decod(mem+pc);
                csignal = uc(mem[pc].opcode,mem[pc].funct);
                printf("PC:%u | %s ",pc, csignal->name);
                if( !csignal->jump ){
                    if( !csignal->RegDst ) printf("$%u, $%u, %i\n", mem[pc].rt, mem[pc].rs, mem[pc].imm);
                    else printf("$%u, $%u, $%u\n", mem[pc].rd, mem[pc].rs, mem[pc].rt);
                }
                else printf("%u\n",mem[pc].addr);
                free(csignal);

			break;

			case '2':
				for(int i=0;i<16;i++){
					for(int j=0;j<16;j++){
						printf("|%i",mem[16*i+j]);
					}
					printf("|\n");
				}
				printf("\n");
			break;

			case '3':
				for(int i=0;i<8;i++){
					printf("|%i",reg[i]);
				}
				printf("|\n\n");
			break;

            case '4':
                for(int i=0;i<256;i++){
                    decod(mem+i);
                    csignal = uc(mem[i].opcode,mem[i].funct);
                    printf("Num:%u | %s ",i, csignal->name);
                    if( !csignal->jump ){
	                    if( !csignal->RegDst ) printf("$%u, $%u, %i\n", mem[i].rt, mem[i].rs, mem[i].imm);
	                    else printf("$%u, $%u, $%u\n", mem[i].rd, mem[i].rs, mem[i].rt);
                    }
                    else printf("%u\n",mem[i].addr);
                    free(csignal);
                }
            break;

            case '5':
                decod(mem+pc);
                csignal = uc(mem[pc].opcode,mem[pc].funct);
                printf("PC:%u | %s ",pc, csignal->name);
                if( !csignal->jump ){
                    if( !csignal->RegDst ) printf("$%u, $%u, %i\n", mem[pc].rt, mem[pc].rs, mem[pc].imm);
                    else printf("$%u, $%u, $%u\n", mem[pc].rd, mem[pc].rs, mem[pc].rt);
                }
                else printf("%u\n",mem[pc].addr);
                free(csignal);
			break;

			case '6':
				asm_code(mem, fileN);
			break;

			case '7':

				pc=0;
				for(int i=0;i<8;i++){
					reg[i] = 0;
				}
				for(int i=0;i<256;i++){
					mem[i].imm = 0;
				}

				printf("Digite nome do arquivo: ");
				do fgets(temp,29,stdin); while( !((strcmp(temp,"\n"))||(strcmp(temp,"\n\0"))) );
				temp[strcspn(temp,"\n")]='\0';

				read_dat(temp, mem);

			break;

			case '8':
				printf("Digite nome do arquivo: ");
				do fgets(temp,29,stdin); while( !((strcmp(temp,"\n"))||(strcmp(temp,"\n\0"))) );
				temp[strcspn(temp,"\n")]='\0';

				write_dat(temp, mem);

			break;

            case '9':
				{
					uint8_t break_point;
					printf("break point:");
					scanf("%u", (unsigned int*)&break_point);
					do{
						addState(pc, reg, mem, &state_stack);
						exec(mem[pc], &pc, reg, mem);
					}while(pc != break_point);
				}
            break;

			case 'a':
				printf("file name: ");
				do fgets(fileN,sizeof(char[64]),stdin); while(!strcmp(fileN,"\n\0"));
				{
					char* tmpP = strpbrk(fileN,"\n");
					if(tmpP) *tmpP = '\0';
				}
				for(int i=0;i<8;i++){
					reg[i] = 0;
				}
				for(int i=0;i<256;i++){
					mem[i].imm=0;
				}
				ler_mem(mem,fileN);
			break;

            case 'b':

				if(state_stack == NULL){
					printf("no state to return to\n");
					break;
				}

				loadState(&pc, reg, mem, &state_stack);

                printf("\n");
                for(int i=0;i<16;i++){
                    for(int j=0;j<16;j++){
                        printf("|%i",mem[16*i+j]);
                    }
                    printf("|\n");
                }
                printf("\n");

                for(int i=0;i<8;i++){
                    printf("|%i",reg[i]);
                }
                printf("|\n\n");

                decod(mem+pc);
                csignal = uc(mem[pc].opcode,mem[pc].funct);
                printf("PC:%u | %s ",pc, csignal->name);
                if( !csignal->jump ){
                    if( !csignal->RegDst ) printf("$%u, $%u, %i\n", mem[pc].rt, mem[pc].rs, mem[pc].imm);
                    else printf("$%u, $%u, $%u\n", mem[pc].rd, mem[pc].rs, mem[pc].rt);
                }
                else printf("%u\n",mem[pc].addr);
                free(csignal);


            break;
        }

		printf("1)step\n2)show data memory\n3)show registers\n4)show all instructions\n5)show intruction to run\n6)make .asm\n7)load data memory data\n8)store data memory data\n9)run\na)load instruction memory\nb)back\n0)quit\n:");
		do scanf("%c",&casee); while(casee=='\n');
	}while(casee!='0');*/
    return 0;
}
























void ler_mem(data *mem_lida, const char* name){
    FILE *arq;
    arq = fopen(name,"r");
    char temp[20];

    if(arq == NULL){
        printf("ERRO NA LEITURA DA MEMORIA DE INSTRUCOES\n");
        exit(2);
    };

    int i;

    for(i=0;!feof(arq);i++){
        fgets(temp,sizeof(char[20]),arq);
        if(!feof(arq)) mem_lida[i].instrucao = (uint16_t)binario_para_decimal(temp,0,15,0);
    }
    mem_lida[i].instrucao = 0;


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

void decod(data* a){

    union{
        uint8_t u;
        int8_t s;
    }conv;

    a->opcode = ((a->instrucao>>12)&15);
    a->rs = ((a->instrucao>>9)&7);
    a->rt = ((a->instrucao>>6)&7);
    a->rd = ((a->instrucao>>3)&7);
	conv.u = (a->instrucao)&63;
	if( (conv.u&32) == 32) conv.u = conv.u | 192;
	a->imm = conv.s;
    a->funct = ((a->instrucao>>0)&7);
	a->addr = ((a->instrucao>>0)&255);
    return;
}

void asm_code(data* mem,const char *memo){
/*    char temp[30];
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
		free(csignal);*/
}

void exec(data instruction, uint8_t* pc, int8_t* reg, int8_t* mem){
/*
	int8_t aluIn, result;

    decod(&instruction);

    control_signal* csignal = uc((unsigned int)instruction.opcode,(unsigned int)instruction.funct);


    if( csignal->RegDst==0 ){
        instruction.rd = instruction.rt;
    }

    if( !csignal->AluSrc ){
        aluIn = reg[instruction.rt];
    } else aluIn = instruction.imm;

    ula_signal* usignal = ula((int16_t)reg[instruction.rs],(int16_t)aluIn,csignal->AluFunc, pc);

    if( csignal->MemWrite == 1 ){
        mem[usignal->result] = reg[instruction.rt];
    }

    if( !csignal->Mem2Reg ){
        result = mem[usignal->result];
    }else result = usignal->result;

    if( csignal->RegWrite == 1 ){
        reg[instruction.rd] = result;
    }

    if( csignal->jump == 1 ){
        (*pc) = instruction.addr;
    }else (*pc)++;

    if( csignal->branch && usignal->zero_flag ){
        (*pc) += instruction.imm;
    }

    free(csignal);
    free(usignal);
*/
	return;
}

