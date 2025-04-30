#ifndef ULA_H
#define ULA_H
#include <stdint.h>
#include <stdbool.h>
typedef struct{
    int8_t result;
    bool zero_flag, overflow;
}ula_signal;
ula_signal* ula(int16_t reg1, int16_t reg2, uint8_t funct, uint8_t pc);
#endif
