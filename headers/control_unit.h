#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H
#include <stdbool.h>
typedef struct{
	bool pcWrite;
	bool louD;
	bool MemWrite;
	bool IREsc;
	bool Mem2Reg;
	bool RegWrite;
	bool AluSrcA;
	int AluSrcB;
	int AluFunct;
	int pcSrc;
	bool RegDst;
	bool branch;
	char name[5];
}control_signal;
void instruction_name_finder(unsigned int a, unsigned int function, char* name);
control_signal* uc(unsigned int microinstruction, unsigned int function);
void update_microinstruction(unsigned int inst, unsigned int function, unsigned int* microinstruction);
#endif
