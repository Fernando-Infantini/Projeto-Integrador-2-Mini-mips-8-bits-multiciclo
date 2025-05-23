#include <stdlib.h>
#include "ula.h"

ula_signal* ula(int16_t reg1, int16_t reg2, uint8_t funct){

    ula_signal* result=calloc(1,sizeof(ula_signal));
	result->overflow=0;

    switch(funct){
        case 0:
        case 1:
        case 3:
        case 6:
            if(reg1+reg2>127 || reg1+reg2<-128) result->overflow = 1;
            result->result = (int8_t) reg1 + reg2;
        break;

        case 2:
            if(reg1-reg2>127 || reg1-reg2<-128) result->overflow = 1;
            result->result = (int8_t) reg1 - reg2;
        break;

        case 4:
            result->result = (int8_t) reg1 & reg2;
        break;

        case 5:
            result->result = (int8_t) reg1 | reg2;
        break;

        case 7:
            result->result = 0;
        break;
    }
    result->zero_flag = result->result==0;
    return result;
};

