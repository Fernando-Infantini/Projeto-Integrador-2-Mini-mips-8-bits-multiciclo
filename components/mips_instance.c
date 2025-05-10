#include <stdlib.h>
#include <stdint.h>

#include "mips_instance.h"
#include "control_unit.h"
#include "ula.h"

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
	mips->RDM = mips->mem[where].data[0];

	if(csignal->pcWrite == 1 || (csignal->branch == 1 && usignal->zero_flag == 1)) mips->pc = pcSrc;

	mips->A = mips->reg[(mips->RI>>9) & 7];
	mips->B = mips->reg[(mips->RI>>6) & 7];
	if(csignal->RegWrite) mips->reg[rt] = regisIn;
	if(csignal->MemWrite) mips->mem[where].data[0] = mips->B;

	mips->aluOut = usignal->result;

	update_microinstruction((mips->RI)>>12,&mips->microinstruction);

	free(csignal);
	free(usignal);

	return;
}
