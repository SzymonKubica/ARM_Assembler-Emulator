#ifndef ASSEMBLER_DEFS_H
#define ASSEMBLER_DEFS_H
#include <stdbool.h>
#include "defns.h"

/*
union struct {
	nibble_t reg;
	word_t value;
} field_t;


typedef struct {
	bool type; //register or number
	field_t field;
} operand_t;
*/

typedef struct {
	char *mnemonic;
	char **operand_fields; 
} instruction_t;

#endif