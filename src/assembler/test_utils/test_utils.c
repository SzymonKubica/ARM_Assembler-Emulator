#include <stdio.h>
#include "test_utils.h"
/*
 * Test Utilities Module: implementation
 */

void testcond(bool condition, char *test_name) {
	printf( "T %s: %s\n", test_name, (condition ? "OK" : "FAIL"));
}

static void print_byte(byte_t byte) {
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

// Prints binary word in little-Endian 
void print_binary_little_Endian(word_t word) {
	for (int i = 0; i < 4; i++, word >>= 8) {
		print_byte(word & 255 /* 11111111 */);
	}
	printf("\n");
}

// Prints binary word in big-Endian 
void print_binary_big_Endian(word_t word) {
	for (int i = 3; i >= 0; i--, word >>= 8) {
		int shift = (8 * i);
		print_byte(word & ((255 /* 11111111 */ << shift) >> shift));
	}
	printf("\n");
}

// Reads a word from a byte_t buffer that was read from memory.
// The buffer is in little-Endian, word is in big-Endian.
word_t get_word(byte_t buffer[4]) {
	word_t result = 0;
	for (int i = 0; i < 4; i++) {
		result |= buffer[3 - i];
		if (i != 3 ) {
			result <<= 8;
		}
	}
	return result;
}

// Function for logging output to the console: used for debugging.
void log_output(word_t output) {
	printf("Value of output in memory: \n");

	// Prints the result in the same format as on p17 in the spec.
	print_binary_little_Endian(output);

	// Prints the hex value of output for finding expected values.
	printf("Hex value: %08x\n", output);

	printf("Value of output in bit-Endian: \n");
	// Prints the result in big-Endian. 
	print_binary_big_Endian(output);
}
