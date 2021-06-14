#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "assembler_defs.h"

byte_t get_Register (char *string)  {
        assert (*string == 'r');
        return strtol(++string, NULL, 10);
}

mnemonic get_Mnemonic (char *m)  {
	if (strncmp(m, "add", 3) == 0) {
		return (mnemonic) ADD;
	}
	if (strncmp(m, "sub", 3) == 0) {
		return (mnemonic) SUB;
	}
	if (strncmp(m, "rsb", 3) == 0) {
		return (mnemonic) RSB;
	}
	if (strncmp(m, "andeq", 5) == 0) {
		return (mnemonic) ANDEQ;
	}
	if (strncmp(m, "and", 3) == 0) {
		return (mnemonic) AND;
	}
	if (strncmp(m, "eor", 3) == 0) {
		return (mnemonic) EOR;
	}
	if (strncmp(m, "orr", 3) == 0) {
		return (mnemonic) ORR;
	}
	if (strncmp(m, "mov", 3) == 0) {
		return (mnemonic) MOV;
	}
	if (strncmp(m, "tst", 3) == 0) {
		return (mnemonic) TST;
	}
	if (strncmp(m, "teq", 3) == 0) {
		return (mnemonic) TEQ;
	}
	if (strncmp(m, "cmp", 3) == 0) {
		return (mnemonic) CMP;
	}
	if (strncmp(m, "mul", 3) == 0) {
		return (mnemonic) MUL;
	}
	if (strncmp(m, "eor", 3) == 0) {
		return (mnemonic) EOR;
	}
	if (strncmp(m, "orr", 3) == 0) {
		return (mnemonic) ORR;
	}
	if (strncmp(m, "mov", 3) == 0) {
		return (mnemonic) MOV;
	}
	if (strncmp(m, "tst", 3) == 0) {
		return (mnemonic) TST;
	}
	if (strncmp(m, "teq", 3) == 0) {
		return (mnemonic) TEQ;
	}
	if (strncmp(m, "cmp", 3) == 0) {
		return (mnemonic) CMP;
	}
	if (strncmp(m, "mul", 3) == 0) {
		return (mnemonic) MUL;
	}
	if (strncmp(m, "mla", 3) == 0) {
		return (mnemonic) MLA;
	}
	if (strncmp(m, "ldr", 3) == 0) {
		return (mnemonic) LDR;
	}
	if (strncmp(m, "str", 3) == 0) {
		return (mnemonic) STR;
	}
	if (strncmp(m, "beq", 3) == 0) {
		return (mnemonic) BEQ;
	}
	if (strncmp(m, "bne", 3) == 0) {
		return (mnemonic) BNE;
	}
	if (strncmp(m, "bge", 3) == 0) {
		return (mnemonic) BGE;
	}
	if (strncmp(m, "bgt", 3) == 0) {
		return (mnemonic) BGT;
	}
	if (strncmp(m, "ble", 3) == 0) {
		return (mnemonic) BLE;
	}
	if (strncmp(m, "blt", 3) == 0) {
		return (mnemonic) BLT;
	}
	if (strncmp(m, "lsl", 3) == 0) {
		return (mnemonic) LSL;
	}
	if (strncmp(m, "lsr", 3) == 0) {
		return (mnemonic) LSR;
	}
	if (strncmp(m, "asr", 3) == 0) {
		return (mnemonic) ASR;
	}
	if (strncmp(m, "ror", 3) == 0) {
		return (mnemonic) ROR;
	}
	if (strncmp(m, "b", 1) == 0) {
		return (mnemonic) B;
	}
	perror("mnemonic not found");
	exit(EXIT_FAILURE);
}

void write_to_file (
	FILE *file, 
	byte_t firstByte, 
	byte_t secondByte, 
	byte_t thirdByte, 
	byte_t fourthByte) 
{
	fputc(fourthByte, file);
	fputc(thirdByte, file);
	fputc(secondByte, file);
	fputc(firstByte, file);
}	

