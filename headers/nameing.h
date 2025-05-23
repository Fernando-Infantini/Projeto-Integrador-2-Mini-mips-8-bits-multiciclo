#ifndef NAMEING_H
#define NAMEING_H
void instruction_name_finder(unsigned int inst, unsigned int function, char* name);
void microinstruction_name_finder(unsigned int microinstruction, char* name);
unsigned int name_to_instruction(const char* name);
#endif
