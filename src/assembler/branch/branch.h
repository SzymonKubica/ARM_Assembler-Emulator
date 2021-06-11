#include "symbol_table.h"
#include "../../defns.h"

/*
 * Branch Instructions Assembler module.
 */

word_t assemble_branch(
	instruction_t instruction,
	symbol_table_t *table,
	int current_address);
