#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "single_data_transfer.h"
#include "../../defns.h"

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

void log_output_for_debugging(word_t output) {
	// Prints the result in the same format as on p17 in the spec.
	print_binary(output);
	// Prints the actual value of the result in hexadecimal.
	printf("%x\n", output);
}

// This test case simulates the assembly of a "str r2, [r3]" instruction from p17.
void test1() {

	// Initialising arguments.
	char *mnemonic = "str";
	char *address = "[r3]";
	int Rd = 2;


	word_t result = 
		assemble_single_data_transfer_instruction(mnemonic, Rd, address);
	
	//log_output_for_debugging(result);

	testcond(result == 0xe5832000, "case: str r2, [r3]");
}

// This test case simulates the assembly of a "str r0, [r1, #28]" instruction from test suite.
void test2() {

	// Initialising arguments.
	char *mnemonic = "str";
	char *address = "[r1, #28]";
	int Rd = 0;


	word_t result = 
		assemble_single_data_transfer_instruction(mnemonic, Rd, address);

	//log_output_for_debugging(result);

	testcond(result == 0xe581001c, "case: str r0, [r1, #28]");
}

// This test case simulates the assembly of a "ldr r2, [r1], #5" instruction from test suite.
void test3() {

	// Initialising arguments.
	char *mnemonic = "ldr";
	char *address = "[r1], #5";
	int Rd = 2;


	word_t result = 
		assemble_single_data_transfer_instruction(mnemonic, Rd, address);

	//log_output_for_debugging(result);

	testcond(result == 0xe4912005, "case: ldr r2, [r1] #5");
}

int main(void) {
	test1();	
	test2();
	test3();
}
