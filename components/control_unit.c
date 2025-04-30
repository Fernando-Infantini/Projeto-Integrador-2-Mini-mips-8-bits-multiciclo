#include <stdlib.h>
#include <string.h>
#include "control_unit.h"

void* memCheck(void* a);

control_signal* uc(unsigned int microinstruction, unsigned int function){
    control_signal* result=(control_signal*)memCheck(malloc(sizeof(control_signal)));

	unsigned int tmp=0;

	result->pcWrite = (microinstruction==0)||(microinstruction==10);
	result->louD = ((microinstruction&14)==4)||(microinstruction==3);
	result->MemWrite = (microinstruction==4);
	result->irWrite = (microinstruction==0);
	result->Mem2Reg = (microinstruction==4);
	result->RegWrite = ((microinstruction&13)==4)||(microinstruction==8);
	result->AluSrcA = ((microinstruction&10)==2)||((microinstruction&10)==8)||((microinstruction&4)==4);
	tmp = ((microinstruction&6)==4)||((microinstruction&13)==1)||((microinstruction&11)==2);
	result->AluSrcB = (int)(tmp<<1 | (unsigned int)(microinstruction==0));

	if(microinstruction<7){
		result->AluFunct = 0;
	}else if( (6<microinstruction && microinstruction<9) || (microinstruction==10)){
		result->AluFunct = function;
	}else{
		result->AluFunct = 1;
	}

	tmp = (microinstruction==10);
	result->pcSrc = (int)(tmp<<1 | (unsigned int)(microinstruction==9));
	result->RegDst = ((microinstruction&14)==0) || (microinstruction==7) || (microinstruction==8);
	result->branch = microinstruction==9;

    return result;
}

void update_microinstruction(unsigned int inst, unsigned int function, unsigned int* microinstruction){
/*	const unsigned int lkt[10][]={{1},{},{},{},{}};
	microinstruction = lkt[microinstruction][inst];*/ //unfinished
	return;
}

void instruction_name_finder(unsigned int inst, unsigned int function, char* name){

    switch(inst){
        case 0:
            switch(function){
                case 0:
				case 2:
				case 4:
				case 6:
                    strcpy(name,"add\0");
                    break;
                case 1:
                    strcpy(name,"sub\0");
                    break;
                case 3:
                    strcpy(name,"and\0");
                    break;
                case 5:
                    strcpy(name,"or\0");
                    break;
                case 7:
                    strcpy(name,"zero\0");
                    break;
            }
            break;
        case 2:
            strcpy(name,"j\0");
            break;
        case 4:
            strcpy(name,"addi\0");
            break;
        case 8:
            strcpy(name,"beq\0");
            break;
        case 11:
            strcpy(name,"lw\0");
            break;
        case 15:
            strcpy(name,"sw\0");
            break;
        default:
            exit(1);
            break;
    }
    return;
}

void* memCheck(void* a){
    if(!a){
        exit(2);
    }
    return a;
}
