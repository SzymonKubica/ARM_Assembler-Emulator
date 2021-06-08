#include <stdlib.h>
#include <string.h>

// //opcodes
// #define add_opcode (0x0)
// #define eor_opcode (0x1)
// #define sub_opcode (0x2)
// #define rsb_opcode (0x3)

#include <stdio.h>

#include "../../assembler_defs.h"

#define cond (0xe << 4)

byte_t parse_numb (char *number) {
	if (number[1] == '0' && number[2] == 'x') {
		return atoi (&number[3]);
	} else {
		return atoi(&number[1]);
	}
}

byte_t parse_reg (char *reg) {
	return atoi(reg);
}

void add_process (FILE *file, instruction_t instruction) {
	byte_t opcode = 0000;
	byte_t firstByte = 0xe << 4;
	byte_t s = 0;

}

void mov_process (FILE *file, instruction_t instruction) {
	
	byte_t opcode = 0xd;
	
	byte_t Rd = parse_reg (&instruction.operand_fields[0][1]);
	byte_t Rn = 0;
	
	byte_t S = 0;
	byte_t immediate = 0;

	word_t operand2 = 0;

	if (instruction.operand_fields[1][0] = '#') {
		// constant
		immediate = 1;
		operand2 = parse_numb (instruction.operand_fields[1]);
	} else {
		// register
		operand2 = parse_reg(instruction.operand_fields[1]);
	}

	byte_t binary[4] 
		= {cond | (immediate << 1) | (opcode >> 3),
		(opcode << 5) | (S << 4) | Rn,
		(Rd << 4) | operand2 >> 8,
		operand2
	};

	for (int i = 3; i >= 0; i--) {
		fwrite(&binary[i], 1, 1, file);
	} 
}

void data_processing (FILE *file, instruction_t instruction) {
	// switch (instruction.mnemonic) {
	// 	case "add":
	// 		add_process(file, instruction);
	// 		break;
		// case "mov":
		if (!strcmp (instruction.mnemonic, "mov"))
			mov_process(file, instruction);
			// break;
		// case "sub":
			
	// }

}
