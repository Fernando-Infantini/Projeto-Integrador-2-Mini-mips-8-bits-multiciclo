#include <stdio.h>
#include <stdlib.h>
#include "mips_instance.h"
#include "memoria.h"
#include "nameing.h"
#include "stack.h"

void print_state(mips_instance* mips);

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

	printf("\n1)step\n2)show data memory\n3)show registers\n4)show all instructions\n5)make .asm\n6)store data\n7)run\n8)load instruction memory\nb)back\n0)quit\n:");
	setbuf(stdin,NULL);

	do scanf("%c",&opt); while (opt == '\n');

    switch(opt){

	case '0':
	exit(0);
	break;

	case '1':
		exec(&mips);
		print_state(&mips);
		char I[5], M[7];
		instruction_name_finder((mips.RI>>12),(mips.RI&7),I);
		microinstruction_name_finder(mips.microinstruction,M);
		printf("pc:%i|%s %s\n",mips.pc,I,M);
	break;

	case '2':
		break_point=0;
		printf("\n==========Memória de instrucoes/dados==========\n");
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			printf("|pos %i: %i %i",break_point,mips.mem[16*i+j].data[1], mips.mem[16*i+j].data[0]);
			break_point++;
		}
		printf("|\n");
	}
	printf("\n");
	break_point=0;
	break;

	case '3':
		printf("\n==========Registradores==========\n");
	for(int i=0;i<8;i++){
		printf("|$%i: %i",i,mips.reg[i]);
	}
	printf("|\n");
	printf("|PC: %i|RI: %i |A: %i|B: %i|RDM: %i|AluOut: %i|\n",mips.pc, mips.RI, mips.A, mips.B, mips.RDM, mips.aluOut);
	break;

	case '4':
	printf("Work in progress...\n");
	break;

	case '5':
	printf("Work in progress...\n");
	break;

	case '6':
	printf("Work in progress...\n");
	break;

	case '7':
		printf("Informe Break point: ");
		setbuf(stdin,NULL);
		scanf("%i",&break_point);

		do exec(&mips); while(mips.pc!=break_point);
		print_state(&mips);
	break;

	case '9':
		ler_mem(&mips);

	break; 

	case 'b':
	printf("Work in progress...\n");
	break; 
	return 0;
}
}
}

void print_state(mips_instance* mips){

	for(int i=0;i<8;i++){
		printf("|%i",mips->reg[i]);
	}
	printf("|\n");

	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			printf("|%i %i",mips->mem[16*i+j].data[1], mips->mem[16*i+j].data[0]);
		}
		printf("|\n");
	}
	printf("\n");

	return;
}
