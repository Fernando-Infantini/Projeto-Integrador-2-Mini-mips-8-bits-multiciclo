typedef struct{
	uint16_t inst;
	int8_t data[2];
}data;

typedef struct{
	int8_t reg[8];
	data mem[256];
	uint16_t RI;
	int8_t RDM, A, B, aluOut;
	uint8_t pc;
	unsigned int microinstruction;
}mips_instance;

void ler_mem(data* mem_lida, const char* name);
int binario_para_decimal(char binario[], int inicio, int fim, int complemento2);
void decod(data* a);
void asm_code(data* instruction_mem, const char *memo);
