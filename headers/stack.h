#ifndef STACK_H
#define STACK_H
#include <stdint.h>
#include "mips_instance.h"

typedef struct a state;
struct a{
	mips_instance content;
	struct a* next;
};

void pushState(mips_instance* mips, state** stack);
int popState(mips_instance* mips, state** stack); //return is error signal
void clearState(state* stack);
#endif
