#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H
#include <stdbool.h>
typedef struct{
    bool Mem2Reg;
    bool MemWrite;
    bool branch;
    int AluFunc;
    bool AluSrc;
    bool RegDst;
    bool RegWrite;
    bool jump;
    char name[5];
}control_signal;
void instruction_name_finder(unsigned int a, unsigned int function, char* name);
control_signal* uc(unsigned int inst, unsigned int function);
#endif
