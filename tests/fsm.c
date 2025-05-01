#include <stdio.h>
#include "control_unit.h"
int main(void){
	unsigned int state=0, instruction=0;
	while(instruction<16){
		printf("%u %u\n", instruction, state);
		update_microinstruction(instruction, &state);
		if(!state) instruction++;
	}
	return 0;
}
