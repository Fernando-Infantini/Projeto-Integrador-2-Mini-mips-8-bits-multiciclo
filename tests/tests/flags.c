#include <stdio.h>
#include <stdlib.h>
#include "control_unit.h"

int main(void){
	for(int i=0;i<11;i++){
		control_signal* a = uc(i,2);
		printf("%i | %i %i %i %i %i %i %i %i %i %i %i %i\n", i,
			a->pcWrite,
			a->louD,
			a->MemWrite,
			a->irWrite,
			a->Mem2Reg,
			a->RegWrite,
			a->AluSrcA,
			a->AluSrcB,
			a->AluFunct,
			a->pcSrc,
			a->RegDst,
			a->branch
		);
		free(a);
	}
	return 0;
}
