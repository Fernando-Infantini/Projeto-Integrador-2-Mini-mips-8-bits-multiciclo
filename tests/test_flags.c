#include <stdio.h>
#include <stdlib.h>
#include "control_unit.h"

int main(void){
	for(int i=0;i<11;i++){
		control_signal* a = uc(i,3);
		printf("%i %i\n", i, a->RegDst);
		free(a);
	}
	return 0;
}
