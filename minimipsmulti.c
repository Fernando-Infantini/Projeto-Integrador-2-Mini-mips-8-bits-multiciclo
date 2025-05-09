#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "memoria.h"
#include "mips_instance.h"
#include "control_unit.h"
#include "dat_manager.h"
#include "stack.h"
#include "ula.h"

void exec(mips_instance* mips);

int main(int argc, char** argv){

	char fileN[64]; //nome do arquivo
	char tmp;

	mips_instance mips={0};
	state* state_stack = NULL;

	do{

		for(int i=0;i<8;i++){
			printf("|%i",mips.reg[i]);
		}
		printf("|\n");

		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				printf("|%i %i",mips.mem[i].data[0], mips.mem[i].data[1]);
			}
			printf("|\n");
		}
		printf("\n");

		char I[5], M[7];
		instruction_name_finder((mips.RI>>12),(mips.RI&7),I);
		microinstruction_name_finder(mips.microinstruction,M);
		printf("pc:%i|%s %s\n",mips.pc,I,M);
		printf("continue? ");
		exec(&mips);

		do tmp = getc(stdin); while(tmp=='\n');

	}while(tmp=='y');

	return 0;
}

void exec(mips_instance* mips){
	int8_t aIn, bIn, signExt, pcSrc, rt;
	uint8_t where;

	control_signal* csignal = uc(mips->microinstruction,mips->RI);

	if(csignal->RegDst==0){
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

	{
		union{
			int8_t s;
			uint8_t u;
		}temp;
		temp.u = (mips->RI&63);
		if((temp.u>>6)==1) temp.u = temp.u&(3<<7);
		signExt = temp.s;
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

	int8_t regisIn;
	switch(csignal->Mem2Reg){
		case 0:
			regisIn = mips->aluOut;
		break;
		case 1:
			regisIn = mips->RDM;
		break;
	}

	if(csignal->IorD == 0){
		where = mips->pc;
	}else{
		where = mips->aluOut;
	}

	if(csignal->irWrite == 1) mips->RI = mips->mem[where].inst;
	mips->RDM = mips->mem[where].data[1];

	if(csignal->pcWrite == 1 || (csignal->branch == 1 && usignal->zero_flag == 1)) mips->pc = pcSrc;

	mips->A = mips->reg[(mips->RI>>9) & 7];
	mips->B = mips->reg[(mips->RI>>6) & 7];
	if(csignal->RegWrite) mips->reg[rt] = regisIn;
	if(csignal->MemWrite) mips->mem[where].data[1] = mips->aluOut;

	mips->aluOut = usignal->result;

	update_microinstruction((mips->RI)>>12,&mips->microinstruction);

	return;
}
