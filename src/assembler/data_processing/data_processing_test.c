#include <stdbool.h>
#include <stdlib.h>

#include "../../defns.h"
#include "../../assembler_defs.h"
#include "data_processing.h"
#include "test_utils.h"

void run_test(
	char *test_name,
	char *mnemonic, 
	char *Rd, 
	char *Rn, 
	char *Operand2, 
	char *file_path,
	word_t expected_result,
	bool is_logging_enabled) 
{
	// Initializing arguments for assemble_data_processing.
	char **operand_fields = (char **) malloc(4 * sizeof(char *));
	operand_fields[0] = Rd;
	operand_fields[1] = Rn;
	operand_fields[2] = Operand2;

	instruction_t instruction = {mnemonic, operand_fields};

	FILE *file;
	file = fopen(file_path, "wb");

	if (file) {
		assemble_data_processing(instruction, file);
	}

	fclose(file);

	FILE *file_read;
	file_read = fopen(file_path, "rb");

	byte_t buffer[4];
	fread(buffer, sizeof(buffer), 1, file_read);
	word_t result = get_word(buffer);

	fclose(file_read);

	testcond(result == expected_result, test_name);
	
	if (is_logging_enabled) {
		log_output(result);
	}
}

int main(void) {
	// Test: add01.s from testsuite.
	run_test(
		"add01.s: add r2,r1,#2", 
		"add",
		"r2",
		"r1",
		"#2",
		"test_binaries/test1.bin",
		0xe2812002,
		false);
}
