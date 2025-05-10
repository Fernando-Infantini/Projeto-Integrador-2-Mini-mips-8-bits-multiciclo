#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H
#include <stdbool.h>
typedef struct{
	bool pcWrite;
	bool IorD;
	bool MemWrite;
	bool irWrite;
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
control_signal* uc(unsigned int microinstruction, unsigned int function);
void update_microinstruction(unsigned int inst, unsigned int* microinstruction);
#endif
