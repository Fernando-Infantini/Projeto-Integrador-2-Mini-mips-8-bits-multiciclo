#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "minimipsmulti.h" //isso aqui não pode existir

#include "control_unit.h"
#include "dat_manager.h"
#include "stack.h"
#include "ula.h"
#include "tipo_r.h"

void exec(mips_instance* mips);

int main(int argc, char** argv){

	char fileN[64]; //nome do arquivo

	mips_instance mips;
	state* state_stack = NULL;

	exec(&mips);

	return 0;
}

void exec(mips_instance* mips){
	int8_t aIn, bIn, signExt, pcSrc, rt;

	control_signal* csignal = uc(mips->microinstruction,mips->RI);

	if(csignal->irWrite == 1) mips->RI = mips->mem->inst;

	if(RegDst==0){
		rt = (mips->RI>>6)&7;
	}else{
		rt = (mips->RI>>3)&7;
	}

	switch(csignal->AluSrcA){
		case 0:
			aIn = mips->pc;
		break;
		case 1:
			aIn = mips->A;
		break;
	}

	switch(csignal->AluSrcB){
		case 0:
			bIn = mips->B;
		break;
		case 1:
			bIn = 1;
		break;
		case 2:
			bIn = signExt;
		break;
	}

	ula_signal* usignal = ula(aIn, bIn, csignal->AluFunct);

	switch(csignal->pcSrc){
		case 0:
			pcSrc = usignal->result;
		break;
		case 1:
			pcSrc = mips->aluOut;
		break;
		case 2:
			pcSrc = signExt;
		break;
	}

	if(csignal->pcWrite == 1 || (csignal->branch && usignal-> zero_flag)) mips->pc = pcSrc;

	mips->A = mips->mem->data[2*((mips->RI>>9) & 7)+1];
	mips->B = mips->mem->data[2*((mips->RI>>6) & 7)+1];
	if(csignal->RegWrite) mips->reg[((mips->RI)>>3)&7+1] = ;

	mips->aluOut = usignal->result;

	return;
}





















/*
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
*/
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

/*void decod(data* a){

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
}*/
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









/*
void busca_inst(int pc, mips_instance* block){
	block->RI = block->mem[pc];
	ula_signal *temp = ula(pc, 1, 0);
	pc = temp->result;
}

void decode(mips_instance* block, int pc){
	block->A = block->reg[((block->RI>>9)&7)];
	block->B = block->reg[((block->RI>>6)&7)];

	union{
        uint8_t u;
        int8_t s;
    }conv;

	conv.u = (block->RI)&63;
	if( (conv.u&32) == 32) conv.u = conv.u | 192;

	block->aluOut = ula(pc, conv.s, 0);
}

void execucaoR(mips_instance* block, control_signal* csignal){
    block->aluOut = ula(block->A,block->B,csignal->AluFunct);
}*/
/*
void terminoR( int rd, mips_instance* block, data *mem){
	block->reg[mem->rd] = block->aluOut;
}
*/
