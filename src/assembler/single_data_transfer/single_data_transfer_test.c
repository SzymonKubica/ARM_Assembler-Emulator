#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../defns.h"
#include "single_data_transfer.h"
#include "test_utils.h"

void run_test(
	char *test_name,
	char *mnemonic, 
	char *rd,
	char *address,
	char *file_name, 
	int current_address, 
	int end_address,
	char **appended_memory_ptr,
	int *num_appended,
	word_t expected_result,
	bool is_logging_enabled) {

	// Initialising arguments.
	char **operand_fields = (char **) calloc(4, sizeof(char *));
	operand_fields[0] = rd;
	operand_fields[1] = address;

	instruction_t instruction = {mnemonic, operand_fields};

	FILE *file;
	file = fopen(file_name, "wb");
	
	if (file) {
		assemble_single_data_transfer(
			instruction, 
			file, 
			current_address, 
			end_address, 
			appended_memory_ptr, 
			num_appended);
	}
	
	fclose(file);
	free(operand_fields);

	FILE *file_read;
	file_read = fopen(file_name, "rb");

	byte_t buffer[4];
	fread(buffer, sizeof(buffer), 1, file_read);
	word_t result = get_word(buffer);

	fclose(file_read);

	testcond(result == expected_result, test_name);

	if (is_logging_enabled) {
		log_output(result);	
	}

}

/*
void test1() {

	// Initialising arguments.
	char *mnemonic = "str";
	char *register_string = "r2";
	char *address = "[r3]";
	char **operand_fields = (char**) calloc (4, sizeof(char *));
	operand_fields[0] = register_string;
	operand_fields[1] = address;
	instruction_t instruction = {mnemonic, operand_fields};

	FILE *file;
	file = fopen("test_binaries/test1.bin", "wb");

	word_t result;
	
	if (file) {
		result = assemble_single_data_transfer(instruction, file);
	}
	
	fclose(file);
	free(operand_fields);

	log_output_for_debugging(result);

	testcond(result == 0xe5832000, "case: str r2, [r3]");
}

// This test case simulates the assembly of a "str r0, [r1, #28]" instruction from test suite.
void test2() {

	// Initialising arguments.
	char *mnemonic = "str";
	char *token1 = "[r1";
	char *token2 = "#28]";
	char *register_string = "r0";
	char **operand_fields = (char**) calloc (4, sizeof(char *));
	operand_fields[0] = register_string;
	operand_fields[1] = token1;
	operand_fields[2] = token2;
	instruction_t instruction = {mnemonic, operand_fields};

	FILE *file;
	file = fopen("test_binaries/test2.bin", "wb");

	word_t result;

	if (file) {
		result = assemble_single_data_transfer(instruction, file);
	}

	fclose(file);
	free(operand_fields);

	log_output_for_debugging(result);

	testcond(result == 0xe581001c, "case: str r0, [r1, #28]");
}

// This test case simulates the assembly of a "ldr r2, [r1], #5" instruction from test suite.
void test3() {

	// Initialising arguments.
	char *mnemonic = "ldr";
	char *token1 = "[r1]";
	char *token2 = "#5";
	char *register_string = "r2";
	char **operand_fields = (char**) calloc (4, sizeof(char *));
	operand_fields[0] = register_string;
	operand_fields[1] = token1;
	operand_fields[2] = token2;
	instruction_t instruction = {mnemonic, operand_fields};

	FILE *file;
	file = fopen("test_binaries/test2.bin", "wb");

	word_t result;

	if (file) {
		result = assemble_single_data_transfer(instruction, file);
	}

	fclose(file);
	free(operand_fields);

	log_output_for_debugging(result);

	testcond(result == 0xe4912005, "case: ldr r2, [r1] #5");
}
*/

int main(void) {
	char *appended_memory = malloc(4);
	int num_appended = 0;

	// Test: assembly of a "str r2, [r3]" instruction from p17.
	run_test(
	"str r2, [r3]", 
	"str",
	"r2",
	"[r3]",
	"test_binaries/test1.bin",
	0x20,
	0x20,
	&appended_memory,
	&num_appended,
	0xe5832000,
	false);

	// Test: assembly of a "str r0, [r1, #28]" instruction from testsuite.
	run_test(
	"str01.s: str r0, [r1, #28]", 
	"str",
	"r0",
	"[r1, #28]",
	"test_binaries/test2.bin",
	0x4,
	0xc,
	&appended_memory,
	&num_appended,
	0xe581001c,
	false);

	// Test: assembly of a "ldr r2, [r1], #5" instruction from testsuite.
	run_test(
	"opt_ldr11.s: ldr r2, [r1], #5", 
	"ldr",
	"r2",
	"[r1], #5",
	"test_binaries/test3.bin",
	0x4,
	0x8,
	&appended_memory,
	&num_appended,
	0xe4912005,
	false);

	free(appended_memory);
}
