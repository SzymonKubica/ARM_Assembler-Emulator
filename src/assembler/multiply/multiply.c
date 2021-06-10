#include <stdio.h>
#include "../../assembler_defs.h"
#include "../../defns.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define firstByte (0xe << 4)

byte_t get_Register (char *string){
	
	assert (*string == 'r');
	return strtol(++string, NULL, 10);
	
}

void assemble_multiply(instruction_t instruction, FILE *file) {

	byte_t Rd = get_Register(instruction.operand_fields[0]);
	byte_t Rm = get_Register(instruction.operand_fields[1]);
	byte_t Rs = get_Register(instruction.operand_fields[2]);
	
	// word_t word = firstByte << 24;
	byte_t secondByte = Rd;
	byte_t thirdByte = Rs;
	byte_t fourthByte = (0x9 << 4) | Rm;	

	if (!strcmp(instruction.mnemonic, "mla")) {
		byte_t Rn = get_Register(instruction.operand_fields[3]);
		secondByte |= (0x2 << 4);
		thirdByte |= (Rn << 4);
	}

	fputc(fourthByte, file);
	fputc(thirdByte, file);
	fputc(secondByte, file);
	fputc(firstByte, file);
	//  (word | (secondByte << 16) | (thirdByte << 8) | fourthByte);
}


