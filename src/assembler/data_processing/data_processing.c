#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../assembler_defs.h"
#include "data_processing.h"

#define cond (0xe << 4)

static byte_t parse_numb (char *number) {
	return strtol(++number, NULL, 0);
}

static word_t int_to_operand2(word_t val) {
	if(val <= 0xff) {
		return val;
	}
	
	word_t curr = val;
	word_t immediate = 0x0;
	for(int i = 0; i < 16; i++) {
		if(immediate >> 8) {
			printf("invalid operand2:");
			return -1;
		}
		else if(curr == 0) {
			immediate |= i << 8; 
			return immediate;
		}
		immediate = immediate << 2;
		immediate |= curr >> 30;
		curr = curr << 2;
	}
	perror("Error: Invalid Operand Value");
	exit(EXIT_FAILURE);
}

// Return operand2 (12 bits) and set 13th bit of returned word
// to the I value 
static word_t get_Operand2 (char *op2) {
	if(op2[0] == '#') {
		return ((1 << 12) | int_to_operand2(parse_numb(op2)));
	}
	return get_Register(op2);
}


static void write_instruction(FILE *file, byte_t I, byte_t opCode, byte_t S, byte_t Rn, byte_t Rd, word_t operand2) {
	write_to_file(file, cond | (I << 1) | (opCode >> 3), 
			(opCode << 5) | (S << 4) | Rn,
			(Rd << 4) | ((operand2 >> 8) & 0xf),
			operand2);
}

static void mov_instruction (FILE *file, instruction_t instruction, byte_t opCode) {
	byte_t Rd = get_Register(instruction.operand_fields[0]);
	word_t operand2 = get_Operand2(instruction.operand_fields[1]);
	write_instruction(file, operand2 >> 12, opCode, 0x0, 0x0, Rd, operand2); 
}

static void compute_instruction (FILE *file, instruction_t instruction, byte_t opCode) {
	byte_t Rd = get_Register(instruction.operand_fields[0]);
	byte_t Rn = get_Register(instruction.operand_fields[1]);
	word_t operand2 = get_Operand2(instruction.operand_fields[2]);
	write_instruction(file, operand2 >> 12, opCode, 0x0, Rn, Rd, operand2); 
}

static void cpsr_instruction (FILE *file, instruction_t instruction, byte_t opCode) {
	byte_t Rn = get_Register(instruction.operand_fields[0]);
	word_t operand2 = get_Operand2(instruction.operand_fields[1]);
	write_instruction(file, operand2 >> 12, opCode, 0x1, Rn, 0x0, operand2); 	
}

void assemble_data_processing (instruction_t instruction, FILE *file) {
	byte_t m = get_Mnemonic(instruction.mnemonic); 
	switch (m) {
		case MOV:
			mov_instruction(file, instruction, m);
			break;
		case TST:
		case TEQ:
		case CMP:
			cpsr_instruction(file, instruction, m);
			break;
		default:
			compute_instruction(file, instruction, m); 
	}
}
