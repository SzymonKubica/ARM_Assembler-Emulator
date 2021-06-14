#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../../defns.h"
#include "../../assembler_defs.h"
#include "single_data_transfer.h"
#include "data_processing.h"

/*
 * Single Data Transfer Assembler Module: implementation.
 */ 

#define PC 15
#define byte_length 8
#define bytes_in_a_word 4

#define lsl 0 // 00
#define lsr 1 // 01 
#define asr 2 // 10 
#define ror 3 // 11 

static word_t get_sdt_instruction_template(void) {
	return 1 << 26; // Bits 27-26 in sdt instruction are always: 01.
}

static void set_Nth_bit(word_t *word, int n) {
	*word |= (1 << n);
}

static void set_cond(word_t *binary_instruction) {
	// ldr/str instructions don't have a cond in the syntax, cond is always al.
	// al = 1110 (14 in decimal).
	*binary_instruction |= (14 << 28); 
}

/*
 * The following functions "set_*" set appropriate bits in the instruction.
 */ 

static void set_Rd(word_t *binary_instruction, int Rd) {
	*binary_instruction |= (Rd << 12);
}

static void set_Rn(word_t *binary_instruction, int Rn) {
	*binary_instruction |= (Rn << 16);
}

static void set_Rm(word_t *binary_instruction, int Rm) {
	*binary_instruction |= Rm;
}

static void set_offset(word_t *binary_instruction, int offset) {
	*binary_instruction |= abs(offset);
}

static void set_shift_type(word_t *binary_instruction, byte_t type_code) {
	*binary_instruction |= (type_code << 5);
}

static void set_shift_value(word_t *binary_instruction, int value) {
	*binary_instruction |= (value << 7);
}

static void set_I_bit(word_t *binary_instruction) {
	set_Nth_bit(binary_instruction, 25);
}

static void set_P_bit(word_t *binary_instruction) {
	set_Nth_bit(binary_instruction, 24);
}

static void set_U_bit(word_t *binary_instruction) {
	set_Nth_bit(binary_instruction, 23);
}

static void set_L_bit(word_t *binary_instruction) {
	set_Nth_bit(binary_instruction, 20);
}

/*
 * General utility functions.
 */
static void find_char(char ch, char **ptr);

static bool is_hex_string(char *str) {
	char *ptr = str;

	// Tries to find 'x' if succeeded there should be 'x' under *ptr, otherwise
	// there will be a sentinel character '\0' indicating the end of the string.
	find_char('x', &ptr);
	return *ptr == 'x';
}

static bool is_shift_mnemonic(char * str) {
	return (strncmp("lsl", str, 3) == 0) 
		|| (strncmp("lsr", str, 3) == 0)
		|| (strncmp("asr", str, 3) == 0)
		|| (strncmp("ror", str, 3) == 0);
}

// Parses the ldr/str address string given operand fields from instruction_t.
static char * get_address(char **operand_fields) {
	char *address = malloc(20);
	char *address_ptr = address;
	for (int i = 1; i < 4; i++) {
		char *ptr = operand_fields[i];
		while (ptr != 0 && *ptr != '\0') {
			*address_ptr = *ptr; 
			address_ptr++;
			ptr++;
		}
	}
	*address_ptr = '\0';
	return address;
}

// Declarations of bool functions needed in the next section.
static bool is_pre_indexing_address(char *address);
static bool is_zero_offset(char *address);
static bool is_offset_by_expression(char *address);
static bool is_register_subtracted(char *address); 
static bool is_index_register_shifted(char *address);

/*
 * The following functions parse the address to extract parts of it
 */

// Parses the string until it reaches a given char ch. 
static void find_char(char ch, char **ptr) {
	while (**ptr != ch && **ptr != '\0') {
		*ptr = *ptr + 1;
	}
}

static void find_index_register(char **ptr) {
	// First occurrence of 'r' indicates the base register.
	find_char('r', ptr);

	// ptr is adjusted to point to the next character. 
	*ptr = *ptr + 1;

	// Second occurrence of 'r' indicates the index register.
	find_char('r', ptr);
}

static int parse_index_register_number(char *address) {
	// Asserts that the offset is specified by a register (not by expression).
	assert(!is_offset_by_expression(address));
	char *ptr = address;

	find_index_register(&ptr);

	return get_Register(ptr);
}

static byte_t parse_base_register_number(char *address) {
	char *ptr = address;
	// First occurrence of 'r' indicates the base register.
	find_char('r', &ptr);

	return get_Register(ptr);
}


static byte_t parse_shift_type(char *address) {
	// Asserts that the offset is specified by a register (not by expression).
	assert(!is_offset_by_expression(address));
	char *ptr = address;
	while (*ptr != '\0' && !is_shift_mnemonic(ptr)) {
		ptr++;
	}
	// Now ptr points to the first char in the shift mnemonic string.
	assert(is_shift_mnemonic(ptr));
	mnemonic shift_mnemonic = get_Mnemonic(ptr);

	switch (shift_mnemonic) {
		case LSL: return lsl;
		case LSR: return lsr;
		case ASR: return asr;
		case ROR: return ror;
		default:
			perror("Not a shift mnemonic.");
			exit(EXIT_FAILURE);
	}
}

static int parse_shift_value(char *address) {
	assert(is_index_register_shifted(address));
	char *ptr = address;

	// The shift value is preceeded by a '#' character.
	find_char('#', &ptr);

	// The pointer is adjusted to point to the fist digit.
	ptr++;

	// Shift is specified in decimal.
	return atoi(ptr);
}

static int parse_offset_by_expression(char *address) {
	assert(is_offset_by_expression(address));
	char *ptr = address;

	// Offset by expression is preceeded by '#' character.
	find_char('#', &ptr);

	// Adjusting ptr so that it points to the first digit or '-' character.
	ptr++;

	if (is_hex_string(ptr)) {
		// The number is in hexadecimal.
		return strtoul(ptr, NULL, 16);
	}
	// Otherwise the number is in decimal.
	return atoi(ptr);
}

static int parse_argument(char *address) {
	assert(address[0] == '=');
	// Initialising ptr to point to the first digit.
	char *ptr = address + 1;
	if (address[2] == 'x') {
		// Address is in hexadecimal.
		return strtoul(ptr, NULL, 16);
	}
	return atoi(ptr);
}

/*
 * The following bool functions distinguish between respective cases of sdt.
 */ 

static bool is_pre_indexing_address(char *address) {
	return address[0] == '[' && address[strlen(address) - 1] == ']';
}

static bool is_zero_offset(char *address) {
	// If the offset is zero, the address has a form [Rn] which has length 4.
	// Or in the case when the register if higher than 9 we have e.g. [r11]
	// which has length 5.
	int length = strlen(address);
	return length == 4 || length == 5;
}

static bool is_offset_by_expression(char *address) {
	// If offset is specified by an expression, only one 'r' is present.
	char *ptr = address;

	// Finds the 'r' of the base register.
	find_char('r', &ptr);

	// Adjusts the pointer to point to the next character.
	ptr++;

	// The second search should shift the pointer all the way up to '\0'.
	// It means that there is only one r present in the string.
	find_char('r', &ptr);
	return *ptr == '\0';
}

// In case of offset specified by (shifted) register.
static bool is_register_subtracted(char *address) {
	// Asserts that the offset is specified by a register (not by expression).
	assert(!is_offset_by_expression(address));
	char *ptr = address;

	// Adjusts ptr so that it points to the 'r' character of the index register.
	find_index_register(&ptr);

	// If the character preceding 'r' is a minus sign, the offset is subtracted.
	return (*(ptr - 1) == '-');
}

static bool is_index_register_shifted(char *address) {
	assert(!is_offset_by_expression(address));
	char *ptr = address;
	while (*ptr != '\0') {
		if (is_shift_mnemonic(ptr)) {
			return true;
		}
		ptr++;
	}
	return false;
}

/*
 * The following functions given a word write it to specific memories.
 */ 

// Returns nth byte in a word instruction, byte indices start at 1.
static byte_t get_Nth_byte(int n, word_t word) {
	return (byte_t) (word >> ((bytes_in_a_word - n) * byte_length));
}

// Writes to the file in little Endian.
static void write_word(word_t word, FILE *file) {
	fputc(get_Nth_byte(4, word), file);
	fputc(get_Nth_byte(3, word), file);
	fputc(get_Nth_byte(2, word), file);
	fputc(get_Nth_byte(1, word), file);
}

static void write_to_appended_memory(word_t word, char *appended_memory_ptr) {
	for (int i = 4; i >= 1; i--) {
		*appended_memory_ptr = get_Nth_byte(i, word);
		appended_memory_ptr++;
	}
}

/*
 * Main function of the module.
 */

void assemble_single_data_transfer(
	instruction_t instruction, 
	FILE *file, 
	int current_address, 
	int end_address,
	char **appended_memory,
	int *num_appended)
{

	char *mnemonic = instruction.mnemonic;
	int Rd = get_Register(instruction.operand_fields[0]);
	char *address = get_address(instruction.operand_fields);

	word_t result = get_sdt_instruction_template();
	set_cond(&result);
	set_Rd(&result, Rd);

	if (get_Mnemonic(mnemonic) == LDR) {
		set_L_bit(&result);

		// A numeric constant of the form: <=expression> (ldr only).
		if (address[0] == '=') {
			word_t argument = parse_argument(address);
			if (argument <= 0xff) {
				// If the arguments is small we use mov instead. 

				// The new address constant is the same number but predeeded by '#'.
				char *altered_address = malloc(strlen(address));
				strncpy(altered_address, address, strlen(address));
				altered_address[0] = '#';

				instruction_t instruction_as_mov = {"mov", instruction.operand_fields};
				// The address is updated.
				instruction_as_mov.operand_fields[1] = altered_address;
				assemble_data_processing(instruction_as_mov, file);
				return;
			} else {
				// The argument doesn't fit, putting the value of <expression> 
				// at the end of the assembled program 
				// According to the spec: always pre-indexed.
				set_P_bit(&result);
				set_U_bit(&result);
				set_Rn(&result, PC);
				set_offset(&result, end_address - current_address - 4);

				write_word(result, file);
				// Appended memory is appended to the end of the output binary once
				// all instructions have been processed.
				write_to_appended_memory(argument, *appended_memory);
				*appended_memory+=4;
				// Keeps track of the number of appended words.
				*num_appended = *num_appended + 1;
				return;
			}
		}
	}

	int Rn = parse_base_register_number(address);
	set_Rn(&result, Rn);

	if (is_pre_indexing_address(address)) {
		set_P_bit(&result);
	}

	if (is_zero_offset(address)) {
		// In the case of zero offset, the Up bit is set as we 'add' zero.
		set_U_bit(&result);
	} else if (is_offset_by_expression(address)) {

		// Parsing the offset by expression starting with '#'.
		int offset = parse_offset_by_expression(address);	
		if (offset > 0) {
			set_U_bit(&result);
		}
		// Offset is an immediate value, I bit not set.
		set_offset(&result, offset);
	} else {
		// Offset by a (shifted) register - I bit is set.
		set_I_bit(&result);
		int Rm = parse_index_register_number(address);
		set_Rm(&result, Rm);
		// If offset is positive, set Up bit
		if (!is_register_subtracted(address)) {
			set_U_bit(&result);
		}
		if (is_index_register_shifted(address)) {
			set_shift_type(&result, parse_shift_type(address));
			set_shift_value(&result, parse_shift_value(address));
		}
	}
	write_word(result, file);
}
