#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mips_instance.h"
#include "memoria.h"
#include "nameing.h"
#include "stack.h"

#define print_state(mips) print_memory((mips)); print_registers((mips))
void print_memory(mips_instance* mips);
void print_registers(mips_instance* mips);
void const_size(char* out, int in);
void print_multi(mips_instance* mips);

int main(int argc, char** argv){

	char fileN[64]; //nome do arquivo
	char tmp;
	int break_point=0;

	mips_instance mips={0};
	state* state_stack = NULL;

	mips.mem[0].inst = (4<<12)+(0<<9)+(1<<6)+1;
	mips.mem[1].inst = (4<<12)+(4<<9)+(4<<6)+1;
	mips.mem[2].inst = (4<<12)+(1<<9)+(1<<6)+2;
	mips.mem[3].inst = (15<<12)+(0<<9)+(1<<6)+1;
	mips.mem[4].inst = (2<<12)+1;

	char opt='1';

    while (opt != '0'){

	printf("\n1)step\n2)show data memory\n3)show registers\n4)show all instructions\n5)make .asm\n6)store data\n7)run\n8)load instruction memory\n9)show multicycle only units\nb)back\n0)quit\n:");

	do scanf("%c",&opt); while (opt == '\n');

    switch(opt){

	case '0':
	exit(0);
	break;

	case '1':
		pushState(&mips, &state_stack);
		exec(&mips);
		print_state(&mips);
		char I[5], M[7];
		instruction_name_finder((mips.RI>>12),(mips.RI&7),I);
		microinstruction_name_finder(mips.microinstruction,M);
		printf("pc:%i|%s %s\n",mips.pc,I,M);
	break;

	case '2':
		print_memory(&mips);
	break;

	case '3':
		print_registers(&mips);
	break;

	case '4':
	printf("Work in progress...\n");
	break;

	case '5':
		{
			printf("File name: ");
			do fgets(fileN,64,stdin); while(strcmp(fileN,"\n\0")==0);
			char* match = strpbrk(fileN,"\n\0");
			if(match!=NULL) (*match) = '\0';
			if(gen_asm(&mips,fileN)==2) printf("Unable to create file");
		}
	break;

	case '6':
	save_mem(mips);
	break;

	case '7':
		printf("Informe Break point: ");
		scanf("%i",&break_point);

		do exec(&mips); while(mips.pc!=break_point);
		print_state(&mips);
	break;

	case '8':
		{
			printf("File name: ");
			do fgets(fileN,64,stdin); while(strcmp(fileN,"\n\0")==0);
			char* match = strpbrk(fileN,"\n\0");
			if(match!=NULL) (*match) = '\0';
			if(ler_mem(&mips,fileN)==2) printf("Unable to open file");
		}
	break;

	case '9':
		print_multi(&mips);
	break;

	case 'b':
		if(popState(&mips,&state_stack)) printf("no state to return to\n");
		else print_state(&mips);
	break;
	return 0;
}
}
}

void print_memory(mips_instance* mips){
	printf("\n==========Memória de instrucoes/dados==========\n    ");
	for(int j=0;j<8;j++){
		printf("      %i   ", j);
	}
	printf("\n");
	for(int i=0;i<32;i++){
		char tmpb[5];
		const_size(tmpb,8*i);
		printf("%s", tmpb);
		for(int j=0;j<8;j++){
			char tmp[2][5] = {0};
			const_size(tmp[1],mips->mem[8*i+j].data[1]);
			const_size(tmp[0],mips->mem[8*i+j].data[0]);
			printf("|%s %s", tmp[1], tmp[0]);
		}
		printf("|\n");
	}
	printf("\n");
	return;
}
void print_registers(mips_instance* mips){
	printf("\n==========Registradores==========\n");
	for(int i=0;i<8;i++){
		printf("|$%i: %i",i,mips->reg[i]);
	}
	printf("|\n");
	printf("\n");
	printf("|PC: %i|\n",mips->pc);
	return;
}

void print_multi(mips_instance* mips){
	printf("\n|PC: %i|RI: %i|RDM: %i|A: %i|B: %i|AluOut: %i|\n", mips->pc, mips->RI, mips->RDM,mips->A, mips->B,  mips->aluOut);
	return;
}

void const_size(char* out, int in){
	char tmp[5];
	sprintf(tmp,"%i",in);
	int size = 4-strlen(tmp);
	out[size]='\0';
	if(out!=NULL) strcpy(out+size,tmp);
	for(int i=0; i<size; i++) out[i]=' ';
	return;
}
