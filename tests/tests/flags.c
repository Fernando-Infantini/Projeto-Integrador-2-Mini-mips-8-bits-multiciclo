#include <stdio.h>
#include <stdlib.h>
#include "control_unit.h"

int main(void){
	for(int i=0;i<11;i++){
		control_signal* a = uc(i,2);
		printf("%i | %i %i %i %i %i %i %i %i %i %i %i %i\n", i,
			a->pcWrite, //1
			a->IorD, //2
			a->MemWrite, //3
			a->irWrite, //4
			a->Mem2Reg, //5
			a->RegWrite, //6
			a->AluSrcA, //7
			a->AluSrcB, //8
			a->AluFunct, //9
			a->pcSrc, //10
			a->RegDst, //11
			a->branch //12
		);
		free(a);
	}
	return 0;
}
