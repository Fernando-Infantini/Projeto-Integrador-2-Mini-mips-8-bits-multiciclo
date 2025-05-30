#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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
        }

        if (flag == 0) {
            state->mem[i].inst = binario_para_decimal(temp, 0, 15, 0);  // Lê instrução binária
		continue;
            i++;
        }
    }

    // Leitura de dados a partir do índice 128 até o limite de 255
    i = 128; // Agora começamos a ler dados na posição 128
    while (i < 256 && fgets(temp, 19, arq) != NULL) {  // Enquanto não atingir o fim do arquivo
        temp[strcspn(temp, "\n")] = '\0';  // Remover \n se presente
        // Leitura dos dados após ".data"
        state->mem[i].data[0] = binario_para_decimal(temp, 8, 15, 1); // Leitura de 16 bits
        i++;
    }

    fclose(arq);
	return 0;
}





int binario_para_decimal(char binario[], int inicio, int fim, int complemento2) {
    int decimal = 0;
    int tamanho = strlen(binario);

    if (inicio < 0 || fim >= tamanho || inicio > fim) {
        //printf("Índices inválidos.\n");
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
						fprintf(arq,"%s $%u, $%u, %i\n", tmp, (inst>>6)&7, (inst>>9)&7, inst&63);
					break;
					default:
						fprintf(arq,"%s $%u, %i($%u)\n", tmp, (inst>>6)&7, inst&63, (inst>>9)&7);
					break;
				}
			break;
		}
	}
	fclose(arq);
	return 0;
}

void print_instructions(mips_instance* mips){

	for(int i=0; i<256;i++){
		unsigned int mi = 1;
		unsigned int inst = mips->mem[i].inst;
		update_microinstruction(inst>>12,&mi);
		char tmp[5];
		instruction_name_finder(inst>>12,inst&7,tmp);

		int imm = inst&63;
		if(imm>31) imm -= 64;

		printf("%u:", i);
		switch(mi){
			case 7:
				printf("%s $%u, $%u, $%u\n", tmp, (inst>>3)&7, (inst>>9)&7, (inst>>6)&7);
			break;
			case 9:
				goto immediat;
			break;
			case 10:
				printf("%s %u\n", tmp, inst&255);
			break;
			default:
				update_microinstruction(inst>>12,&mi);
				switch(mi){
					case 6:
					immediat:
						printf("%s $%u, $%u, %i\n", tmp, (inst>>6)&7, (inst>>9)&7, imm);
					break;
					default:
						printf("%s $%u, %i($%u)\n", tmp, (inst>>6)&7, imm, (inst>>9)&7);
					break;
				}
			break;
		}
	}
	return;
}

void decimal_para_binario(char binario[], int num, int bits, int usar_complemento){
    int i = bits - 1;

    for (int j = 0; j < bits; j++) {
        binario[j] = '0';
    }
    binario[bits] = '\0';

    if (usar_complemento && num < 0) {
        num = (1 << bits) + num;
    }

    while (num > 0 && i >= 0) {
        binario[i--] = (num % 2) + '0';
        num /= 2;
    }

}

void save_mem(mips_instance state){
	char temp[256];
	while(getchar() != '\n');
	printf("File name: ");
	setbuf(stdin,NULL);
	fgets(temp,255,stdin);

	FILE *arq = fopen(temp,"w");
	int i=0;


	while(state.mem[i].inst != 0 && i<128){
		decimal_para_binario(temp, state.mem[i].inst, 16, 0);
		fprintf(arq, "%s\n", temp);
		i++;
	}

	fprintf(arq,".data\n");

	i=128;
	while(i<256){
		decimal_para_binario(temp, state.mem[i].data[0], 8, 1);
		fprintf(arq, "00000000%s\n", temp);
		i++;
	}

	fclose(arq);
}

int write_a_register(mips_instance* mips, char* which, int value){
	if(!strcmp(which,"PC\0")){
		if(value<0 || value>255) return 1;
		mips->pc = value;
	}
	else{
		if(value<-128 || value>127) return 1;
		if(!strcmp(which,"A\0")){
			mips->A = value;
		}
		else if(!strcmp(which,"B\0")){
			mips->B = value;
		}
		else if(!strcmp(which,"RDM\0")){
			mips->RDM = value;
		}
		else if(!strcmp(which,"AluOut\0")){
			mips->aluOut = value;
		}
		else if( (0<=which[0]-'0') && (which[0]-'0'<9) ){
			mips->reg[which[0]-'0'] = value;
		}
		else return 2;
	}
	return 0;
}

int write_a_ddress(mips_instance* mips, unsigned int address, int value, _Bool mode){

	if( !((0<=address) && (address<256)) ) return 2;

	if( (mode == 0) ){
			if(value<-128 || value>127) return 1;
			mips->mem[address].data[0]=value;
			mips->mem[address].data[1]=0;
	}
	else{
			mips->mem[address].inst = value;
	}
	return 0;
}

void print_instruction(unsigned int inst){
		unsigned int mi = 1;
		update_microinstruction(inst>>12,&mi);
		char tmp[5];
		instruction_name_finder(inst>>12,inst&7,tmp);

		int imm = inst&63;
		if(imm>31) imm -= 64;

		switch(mi){
			case 7:
				printf("%s $%u, $%u, $%u", tmp, (inst>>3)&7, (inst>>9)&7, (inst>>6)&7);
			break;
			case 9:
				goto immediat;
			break;
			case 10:
				printf("%s %u", tmp, inst&255);
			break;
			default:
				update_microinstruction(inst>>12,&mi);
				switch(mi){
					case 6:
					immediat:
						printf("%s $%u, $%u, %i", tmp, (inst>>6)&7, (inst>>9)&7, imm);
					break;
					default:
						printf("%s $%u, %i($%u)", tmp, (inst>>6)&7, imm, (inst>>9)&7);
					break;
				}
			break;
		}
	return;
}
