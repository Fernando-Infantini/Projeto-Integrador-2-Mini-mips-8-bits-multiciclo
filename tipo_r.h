#include"ula.h"

void execucaoR(mips_instance* block, control_signal* csignal);
void terminoR(int rd, mips_instance* block, data *mem);
void busca_inst(int pc, mips_instance* block);
void decode(mips_instance* block, int pc);
