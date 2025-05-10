#include <string.h>
#include "nameing.h"

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
			strcpy(name,"???\0");
		break;
	}
	return;
}
void microinstruction_name_finder(unsigned int microinstruction, char* name){
	switch(microinstruction){
		case 0:
			strcpy(name,"fetch\0");
		break;
		case 1:
			strcpy(name,"decode\0");
		break;
		case 2:
			strcpy(name,"fadd\0");
		break;
		case 3:
			strcpy(name,"readM\0");
		break;
		case 4:
			strcpy(name,"strfM\0");
		break;
		case 5:
			strcpy(name,"writeM\0");
		break;
		case 6:
			strcpy(name,"addiR\0");
		break;
		case 7:
			strcpy(name,"Rexec\0");
		break;
		case 8:
			strcpy(name,"Rstr\0");
		break;
		case 9:
			strcpy(name,"branch\0");
		break;
		case 10:
			strcpy(name,"jmp\0");
		break;
	}
	return;
}
