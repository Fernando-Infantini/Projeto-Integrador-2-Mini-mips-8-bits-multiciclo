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
void print_mem_hex(mips_instance* mips);
char to_hex(unsigned int x);

int main(int argc, char** argv){

	char fileN[64]; //nome do arquivo
	char tmp;
	int break_point=0;

	mips_instance mips={0};
	state* state_stack = NULL;

	if(argc>1){
		strcpy(fileN, argv[1]);
		if(ler_mem(&mips,fileN)==2) printf("unable to open file");
	}

	char opt='1';

    while (opt != '0'){

	printf("\n1)step\n2)show data memory\n3)show registers\n4)show all instructions\n5)make .asm\n6)store data\n7)run\n8)load instruction memory\n9)show multicycle only units\nx)print memory in hex\nb)back\ne)edit a register\nE)edit a memory address\n0)quit\n:");

	do scanf("%c",&opt); while (opt == '\n');

    switch(opt){

	case '0':
	exit(0);
	break;

	case '1':
		pushState(&mips, &state_stack);
		exec(&mips);
		print_state(&mips);
		printf("%hu ", mips.pc);
		print_instruction(mips.RI);
		printf("\nstate: %u\n", mips.microinstruction);
	break;

	case '2':
		print_memory(&mips);
	break;

	case '3':
		print_registers(&mips);
	break;

	case '5':
		{
			char tmpp[64];
			printf("File name: ");
			do fgets(tmpp,64,stdin); while(strcmp(tmpp,"\n\0")==0);
			fileN[strcspn(tmpp,"\n\0")]='\0';
			if(gen_asm(&mips,tmpp)==2) printf("Unable to create file");
		}
	break;

	case '6':
	save_mem(mips);
	break;

	case '7':
		printf("Break point: ");
		scanf("%i",&break_point);

		do exec(&mips); while(mips.pc!=break_point);
		print_state(&mips);
		printf("%hu ", mips.pc);
		print_instruction(mips.RI);
		printf("\nstate: %u\n", mips.microinstruction);

	break;

	case '8':
		{
			printf("File name: ");
			do fgets(fileN,64,stdin); while(strcmp(fileN,"\n\0")==0);
			fileN[strcspn(fileN,"\n\0")]='\0';
			if(ler_mem(&mips,fileN)==2) printf("Unable to open file");
			else{
				mips.pc=0;
				mips.RI=0;
				mips.RDM=0;
				mips.A=0;
				mips.B=0;
				mips.aluOut=0;
				mips.microinstruction=0;
				for(int i=0;i<8;i++){
					mips.reg[i]=0;
				}
			}
		}
	break;

	case '9':
		print_multi(&mips);
	break;

	case 'b':
		if(popState(&mips,&state_stack)) printf("no state to return to\n");
		else{
			print_state(&mips);
			printf("%hu ", mips.pc);
			print_instruction(mips.RI);
			printf("\nstate: %u\n", mips.microinstruction);
		}
	break;
	case 'x':
		print_mem_hex(&mips);
	break;
	case '4':
		print_instructions(&mips);
	break;
	case 'e':{
			int value;
			char tmpp[10];
			printf("Register: ");
			do fgets(tmpp,10,stdin); while(strcmp(tmpp,"\n\0")==0);
			tmpp[strcspn(tmpp,"\n\0")]='\0';

			printf("Value: ");
			scanf("%i", &value);

			switch(write_a_register(&mips,tmpp,value)){
				case 1:
					printf("invalid value\n");
				break;
				case 2:
					printf("no register %s\n", tmpp);
				break;
			}
	}break;
	case 'E':{
			int value;
			unsigned int address;
			printf("Address: ");
			scanf("%i", &address);

			printf("Value: ");
			scanf("%i", &value);

			switch(write_a_ddress(&mips,address,value,0)){
				case 1:
					printf("invalid value\n");
				break;
				case 2:
					printf("inexistent address\n");
				break;
			}
	}break;
	return 0;
}
}
}

void print_memory(mips_instance* mips){
	printf("\n================instruction/data===============\n    ");
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
	printf("\n============Registers============\n");
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
void print_mem_hex(mips_instance* mips){
	printf("\n================instruction/data===============\n    ");
	for(int j=0;j<8;j++){
		printf("   %i ", j);
	}
	printf("\n");
	for(int i=0;i<32;i++){
		char tmpb[5];
		const_size(tmpb,8*i);
		printf("%s", tmpb);
		for(int j=0;j<8;j++){
			char tmp[5] = {0};
			tmp[0] = to_hex((mips->mem[8*i+j].inst>>12)&15);
			tmp[1] = to_hex((mips->mem[8*i+j].inst>>8)&15);
			tmp[2] = to_hex((mips->mem[8*i+j].inst>>4)&15);
			tmp[3] = to_hex(mips->mem[8*i+j].inst&15);
			printf("|%s", tmp);
		}
		printf("|\n");
	}
	printf("\n");
	return;
}

char to_hex(unsigned int x){
	if( (0<=x) && (x<10) ) return '0'+x;
	else if( (9<x) && (x<16) ) return 'a'+x-10;
	else return '?';
}
