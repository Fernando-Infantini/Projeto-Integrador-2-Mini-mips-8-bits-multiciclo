typedef struct{
    uint16_t instrucao;
    uint8_t opcode;
    uint8_t rs;
    uint8_t rd;
    uint8_t rt;
    int8_t imm;
    uint8_t funct;
	uint8_t addr;
    char tipo;
}data;

typedef struct multiciclo{
	int8_t mem[256], reg[8];
	int16_t RI, RDM, A, B, aluOut;
}ciclo;

//tem que colocar essas coisas em headers diferentes mas vocês que decidem como.

void ler_mem(data* mem_lida, const char* name);
int binario_para_decimal(char binario[], int inicio, int fim, int complemento2);
void decod(data* a);
void asm_code(data* instruction_mem, const char *memo);
void exec(data instruction, uint8_t* pc, int8_t* reg, int8_t* data_mem);
