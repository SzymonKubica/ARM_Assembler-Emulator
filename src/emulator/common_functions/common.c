#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../defns.h"


byte_t get_First_Nibble (byte_t byte) {
	return byte >> 4; 
}

byte_t get_Second_Nibble (byte_t byte) {
	return byte & 0xf;
}

word_t shifter (byte_t shiftType, byte_t shiftAmount, word_t word, bit_t *carry) {
	if (shiftAmount == 0) {
		return word;
	}
	switch (shiftType){
		case 0: // logical left
			*carry = ((word << (shiftAmount - 1)) >> 31) & 1; 
			return word << shiftAmount;
		case 1: // logical right
			*carry = ((word >> (shiftAmount - 1))) & 1; 
			return word >> shiftAmount;
		case 2: // arithmetic right
			*carry = ((word >> (shiftAmount - 1))) & 1; 
			return word / (1 << shiftAmount);
		case 3: // rotate right
			*carry = ((word >> (shiftAmount - 1))) & 1; 
			return  (word >> shiftAmount) | (word << (32 - shiftAmount));
		default: // ERROR: Should never be reached
			return -1;
	}
} 


/*
 * binary string module: implementation.
 */

static char * deleteSpaces(char *str);
static int countSpaces(char *str);

/*
 * Takes a string representing a binary number and returns 
 * a byte equal to the given number.
 * Pre: the number is less than or equal 8 bits long.
 */

byte_t readBinary(char *str) {
	byte_t byte = 0x0;
	str = deleteSpaces(str);
	for (int i = strlen(str), j = -1; i >= 0; i--, j++) {
		if (*(str + i) == '1') {
			byte += (1 << j);
		}
	}
	free(str);
	return byte;
}

/*
 * Takes a string representing a binary number and returns 
 * a word equal to the given number.
 * Pre: the number is less than or equal 32 bits long.
 */

word_t readBinaryWord(char *str) {
	word_t word = 0x0;
	str = deleteSpaces(str);
	for (int i = strlen(str), j = -1; i >= 0; i--, j++) {
		if (*(str + i) == '1') {
			word += (1 << j);
		}
	}
	free(str);
	return word;
}

static char * deleteSpaces(char *str) {
	char *str2 = malloc(strlen(str) - countSpaces(str));
	char *ptr = str2;
	for (; *str != '\0'; str++) {
		if (*str != ' ') {
			*ptr = *str;
			ptr++;
		}
	}
	return str2;
}

static int countSpaces(char *str) {
	int counter = 0;
	char *ptr = str;
	for (; *ptr != '\0'; ptr++) {
		if (*ptr == ' ') {
			counter++;
		}
	}
	return counter;
}
