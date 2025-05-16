#include <stdlib.h>
#include "stack.h"

void pushState(mips_instance* mips, state** stack){
	state* temp = malloc(sizeof(state));

	for(int i=0;i<8;i++){
		temp->content.reg[i] = mips->reg[i];
		temp->content.mem[i] = mips->mem[i];
	}
	for(int i=8;i<256;i++){
		temp->content.mem[i] = mips->mem[i];
	}

	temp->content.RI = mips->RI;
	temp->content.RDM = mips->RDM;
	temp->content.A = mips->A;
	temp->content.B = mips->B;
	temp->content.aluOut = mips->aluOut;
	temp->content.pc = mips->pc;
	temp->content.microinstruction = mips->microinstruction;

	temp->next = *stack;
	*stack = temp;
	return;
}
int popState(mips_instance* mips, state** stack){

	if((*stack)==NULL) return 1;

	state* temp = *stack;

	for(int i=0;i<8;i++){
		mips->reg[i] = temp->content.reg[i];
		mips->mem[i] = temp->content.mem[i];
	}
	for(int i=8;i<256;i++){
		mips->mem[i] = temp->content.mem[i];
	}

	mips->RI = temp->content.RI;
	mips->RDM = temp->content.RDM;
	mips->A = temp->content.A;
	mips->B = temp->content.B;
	mips->aluOut = temp->content.aluOut;
	mips->pc = temp->content.pc;
	mips->microinstruction = temp->content.microinstruction;

	*stack = temp->next;
	free(temp);
	return 0;
}
void clearState(state* stack){
	do{
		state* tmp = stack->next;
		free(stack);
		stack = tmp;
	}while(stack);
	return;
}
