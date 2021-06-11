#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../assembler_defs.h"
#include "../../defns.h"
#include "branch.h"

void testcond(bool condition, char *test_name) {
	printf( "T %s: %s\n", test_name, (condition ? "OK" : "FAIL"));
}

void print_byte(byte_t byte) {
	bit_t bits[8];
	for (int i = 1; i <= 8; i++) {
		bits[8 - i] = byte & 1;
		byte >>= 1;
	}
	for (int i = 0; i < 8; i++) {
		printf("%d", bits[i]);
	}
	printf(" ");
}

void print_binary(word_t word) {
	for (int i = 0; i < 4; i++, word >>= 8) {
		print_byte(word & 255);
	}
	printf("\n");
}

// This test case simulates the assembly of a bne loop instruction from p17.
void test1() {

	// Initialising arguments.
	char *mnemonic = "bne";
	char **operand_fields = malloc(sizeof(char *));
	operand_fields[0] = "loop";
	instruction_t instruction = {mnemonic, operand_fields};
	int loop_address = 0x8;
	int current_address = 0x18; // Instruction is at 0x18, offset due to pipeline.

	// Populating symbol table.
	symbol_table_t *table = malloc(sizeof(symbol_table_t));
	symbol_table_init(table);
	add_entry(table, operand_fields[0], loop_address);

	word_t result = 
		assemble_branch(instruction, table, current_address);

	// Prints the result in the same format as on p17 in the spec.
	//print_binary(result);

	testcond(result == 0x1afffffa, "case: bne loop");
	table_destroy(table);
}

int main(void) {
	test1();	
}
