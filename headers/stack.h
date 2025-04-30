#ifndef STACK_H
#define STACK_H
#include <stdint.h>
typedef struct a state;
struct a{
	uint8_t pc;
	int8_t mem[256], registers[8];
	struct a* next;
};
void addState(uint8_t pc, int8_t* reg, int8_t* data_mem, state** stack);
void loadState(uint8_t *pc, int8_t* reg, int8_t* data_mem, state** stack);
void clearState(state* stack);
#endif
