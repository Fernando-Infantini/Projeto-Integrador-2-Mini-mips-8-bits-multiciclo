#include <stdio.h>
#include <stdlib.h>
#include "headersmips_instance.h"
#include "memoria.h"
#include "nameing.h"
#include "stack.h"

int main(int argc, char** argv){

	char fileN[64]; //nome do arquivo
	char tmp, opt;

	mips_instance mips={0};
	state* state_stack = NULL;

	mips.mem[0].inst = (4<<12)+(0<<9)+(1<<6)+1;
	mips.mem[1].inst = (4<<12)+(4<<9)+(4<<6)+1;
	mips.mem[2].inst = (4<<12)+(1<<9)+(1<<6)+2;
	mips.mem[3].inst = (15<<12)+(0<<9)+(1<<6)+1;
	mips.mem[4].inst = (2<<12)+1;

	printf("1)step\n2)show data memory\n3)show registers\n4)show all instructions\n5)make .asm\n6)load data memory data\n7)store data memory data\n8)run\n9)load instruction memory\nb)back\n0)quit\n:");
	setbuf(stdin,NULL);
	scanf("%c",opt);

	while (opt != '0'){ 

	case '0':
	exit(0);
	break;

	case '1':
		for(int i=0;i<8;i++){
			printf("|%i",mips.reg[i]);
		}
		printf("|\n");

		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				printf("|%i %i",mips.mem[16*i+j].data[1], mips.mem[16*i+j].data[0]);
			}
			printf("|\n");
		}
		printf("\n");

		char I[5], M[7];
		instruction_name_finder((mips.RI>>12),(mips.RI&7),I);
		microinstruction_name_finder(mips.microinstruction,M);
		printf("pc:%i|%s %s\n",mips.pc,I,M);
	break;

	case '2':
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			printf("|%i %i",mips.mem[16*i+j].data[1], mips.mem[16*i+j].data[0]);
		}
		printf("|\n");
	}
	printf("\n");
	break;

	case '3':
	for(int i=0;i<8;i++){
		printf("|%i",mips.reg[i]);
	}
	printf("|\n");
	break;

	case '4':
	printf("Work in progress...\n");
	break;
	}

	case '5':
	printf("Work in progress...\n");
	break;

	case '6':
	printf("Work in progress...\n");
	break;

	case '7':
	printf("Work in progress...\n");
	break;

	case '8':
	printf("Work in progress...\n");
	break;

	case '9':
	printf("Work in progress...\n");
	break; 

	case 'b':
	printf("Work in progress...\n");
	break; 
	return 0;
}
