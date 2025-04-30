#include <stdlib.h>
#include "stack.h"

void addState(uint8_t pc, int8_t* reg, int8_t* mem, state** stack){
	state* temp = malloc(sizeof(state));
	temp->pc = pc;
	for(int i=0;i<8;i++){
		temp->registers[i] = reg[i];
		temp->mem[i] = mem[i];
	}
	for(int i=8;i<256;i++){
		temp->mem[i] = mem[i];
	}
	temp->next = *stack;
	*stack = temp;
	return;
}
void loadState(uint8_t *pc, int8_t* reg, int8_t* mem, state** stack){
	state* temp = *stack;
	*pc = temp->pc;
	for(int i=0;i<8;i++){
		reg[i] = temp->registers[i];
		mem[i] = temp->mem[i];
	}
	for(int i=8;i<256;i++){
		mem[i] = temp->mem[i];
	}
	*stack = temp->next;
	free(temp);
	return;
}
void clearState(state* stack){
	do{
		state* tmp = stack->next;
		free(stack);
		stack = tmp;
	}while(stack);
	return;
}
