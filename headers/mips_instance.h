#ifndef MIPS_INSTANCE_H
#define MIPS_INSTANCE_H
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
#endif
