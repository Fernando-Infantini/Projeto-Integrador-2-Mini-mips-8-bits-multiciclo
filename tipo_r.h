#include"ula.h"

void execucaoR(ciclo* block, control_signal* csignal);
void terminoR(int rd, ciclo* block, data *mem);
void busca_inst(int pc, ciclo* block);
void decode(ciclo* block, int pc);
