#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../assembler_defs.h"
#include "data_processing.h"

#define cond (0xe << 4)

static byte_t parse_numb (char *number) {
	return strtol(number++, NULL, 0);
}

/*static word_t get_Operand2 (char *op2) {

}
*/

static void mov_instruction (FILE *file, instruction_t instruction, byte_t opCode) {
	
	byte_t Rd = get_Register(instruction.operand_fields[0]);
	byte_t Rn = 0;
	
	byte_t S = 0;
	byte_t immediate = 0;

	word_t operand2 = 0;

	if (instruction.operand_fields[1][0] == '#') {
		// constant
		immediate = 1;
		operand2 = parse_numb (instruction.operand_fields[1]);
	} else {
		// register
		operand2 = get_Register(instruction.operand_fields[1]);
	}

	byte_t binary[4] 
		= {cond | (immediate << 1) | (opCode >> 3),
		(opCode << 5) | (S << 4) | Rn,
		(Rd << 4) | operand2 >> 8,
		operand2
	};

	for (int i = 3; i >= 0; i--) {
		fwrite(&binary[i], 1, 1, file);
	} 
}

static void compute_instruction (FILE *file, instruction_t instruction, byte_t opCode) {
}

static void cpsr_instruction (FILE *file, instruction_t instruction, byte_t opCode) {
}

void data_processing (instruction_t instruction, FILE *file) {
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
