#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../assembler_defs.h"
#include "../../defns.h"
#include "branch.h"
#include "test_utils.h"

void run_test(
	char *test_name,
	char *mnemonic, 
	char *label, 
	char *file_name,
	int label_address, 
	int current_address, 
	word_t expected_result,
	bool is_logging_enabled) 
{

	// Initialising arguments.
	char **operand_fields = (char **) calloc(4, sizeof(char *));
	operand_fields[0] = label;
	instruction_t instruction = {mnemonic, operand_fields};

	// Populating symbol table.
	symbol_table_t *table = malloc(sizeof(symbol_table_t));
	symbol_table_init(table);
	add_entry(table, operand_fields[0], label_address);

	FILE *file;
	file = fopen(file_name, "wb");

	if (file) {
		assemble_branch(instruction, file, table, current_address);
	}

	fclose(file);

	FILE *file_read;
	file_read = fopen(file_name, "rb");

	byte_t buffer[4];
	fread(buffer, sizeof(buffer), 1, file_read);
	word_t result = get_word(buffer);

	fclose(file_read);
	table_destroy(table);
	free(operand_fields);

	testcond(result == expected_result, test_name);

	if (is_logging_enabled) {
		log_output(result);
	}

}

int main(void) {

	// Test: assembly of a "bne loop" instruction from p17.
	run_test(
		"bne loop", 
		"bne", 
		"loop", 
		"test_binaries/test1.bin", 
		0x8, 
		0x18, 
		0x1afffffa, 
		false);

	// Test: assembly of a "b foo" instruction from test suite.
	run_test(
		"b foo", 
		"b", 
		"foo", 
		"test_binaries/test2.bin", 
		0xc, 
		0x4, 
		0xea000000, 
		false);

	// Test: assembly of a "beq foo" instruction from test suite.
	run_test(
		"beq foo",
		"beq", 
		"foo", 
		"test_binaries/test3.bin", 
		0x14, 
		0xc, 
		0xa000000, 
		false);
}
