#include <stdlib.h>
#include "control_unit.h"

void* memCheck(void* a);
unsigned int classify(unsigned int inst);

control_signal* uc(unsigned int microinstruction, unsigned int function){
    control_signal* result=(control_signal*)memCheck(malloc(sizeof(control_signal)));

	unsigned int tmp=0;

	result->pcWrite = (microinstruction==0)||(microinstruction==10);
	result->IorD = ((microinstruction&14)==4)||(microinstruction==3);
	result->MemWrite = (microinstruction==5);
	result->irWrite = (microinstruction==0);
	result->Mem2Reg = (microinstruction==4);
	result->RegWrite = (microinstruction&13)==4||(microinstruction==8);
	result->AluSrcA = ((microinstruction&10)==2)||((microinstruction&10)==8)||((microinstruction&4)==4);
	tmp = ((microinstruction&6)==4)||((microinstruction&13)==1)||((microinstruction&11)==2);
	result->AluSrcB = (int)(tmp<<1 | (unsigned int)(microinstruction==0));

	if(microinstruction<7){
		result->AluFunct = 0;
	}else if( (6<microinstruction && microinstruction<9) || (microinstruction==10)){
		result->AluFunct = function;
	}else{
		result->AluFunct = 2;
	}

	tmp = (microinstruction==10);
	result->pcSrc = (int)(tmp<<1 | (unsigned int)(microinstruction==9));
	result->RegDst = ((microinstruction&14)==0) || (microinstruction==7) || (microinstruction==8);
	result->branch = microinstruction==9;

    return result;
}

void update_microinstruction(unsigned int inst, unsigned int* microinstruction){
	switch(*microinstruction){
		case 0:
			(*microinstruction) = 1;
		break;
		case 1:
			switch(classify(inst)){
				case 0:
					(*microinstruction) = 2;
				break;
				case 1:
					(*microinstruction) = 7;
				break;
				case 2:
					(*microinstruction) = 9;
				break;
				case 3:
					(*microinstruction) = 10;
				break;
				case 4:
					(*microinstruction) = 0;
				break;
			}
		break;
		case 2:
			switch(inst){
				case 4:
					(*microinstruction) = 6;
				break;
				case 11:
					(*microinstruction) = 3;
				break;
				case 15:
					(*microinstruction) = 5;
				break;
				default:
					(*microinstruction) = 0;
				break;
			}
		break;
		case 3:
			(*microinstruction) = 4;
		break;
		case 7:
			(*microinstruction) = 8;
		break;
		default:
			(*microinstruction) = 0;
		break;
	}
	return;
}



unsigned int classify(unsigned int inst){
	if(inst==0){
		return 1;
	}else if(inst==4||(inst&11)==11){
		return 0;
	}else if(inst==8){
		return 2;
	}else if(inst==2){
		return 3;
	}
	return 4;
}
void* memCheck(void* a){
	if(!a){
		exit(2);
	}
	return a;
}
